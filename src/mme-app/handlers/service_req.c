/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "mme_app.h"
#include "ue_table.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage6_info.h"
#include "servicereq_info.h"
#include "common_proc_info.h"

/************************************************************************
Current file : Service Request handler.
Service Request-->service_request_handler-> init ctxt setup [Service Accept]
**************************************************************************/

/****Globals and externs ***/


extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_servicereq_fd;
extern int g_Q_mme_to_s1ap_fd;
/*Making global just to avoid stack passing*/
static char buf[S1AP_SERVICEREQ_BUF_SIZE];

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/

static void
init_stage()
{
	log_msg(LOG_INFO, "Service Request Reader - s1ap service_req : waiting\n");

	/*Reading the service request signal from S1AP */
	if (( g_Q_servicereq_fd  = open_ipc_channel(S1AP_SERVICEREQ_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader for S1AP Service Request IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Service Request reader - s1ap service request complete: Connected\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_SERVICEREQ_BUF_SIZE);
	while (bytes_read < S1AP_SERVICEREQ_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_servicereq_fd, buf,
			S1AP_SERVICEREQ_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "**************** Service request Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
service_request_processing()
{
	struct service_req_Q_msg *service_req =
			(struct service_req_Q_msg *) buf;
	struct UE_info *ue_entry = GET_UE_ENTRY(service_req->ue_idx);

    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
	    log_msg(LOG_INFO, "Service request received for invalid UE ");
        return E_FAIL;
    }

	log_msg(LOG_INFO, "Service request received for ue %d\n",
			service_req->ue_idx);

	ue_entry->ue_state = SVC_REQ_WF_INIT_CTXT_RESP;
	ue_entry->s1ap_enb_ue_id = service_req->s1ap_enb_ue_id;

	// TODO: KSI, SeqNum, MAC code val?
	

	/*Post to next processing*/
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	struct s1ap_common_req_Q_msg icr_msg;

	struct service_req_Q_msg *service_req =
				(struct service_req_Q_msg *) buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(service_req->ue_idx);

    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
	{
		log_msg(LOG_INFO, "Failed to retrieve UE context for idx %d\n",
					      service_req->ue_idx);
		return -1;
	}

	log_msg(LOG_INFO, "Post for s1ap processing - service_req_wf_initctxt_resp.\n");

	/* create KeNB key */
	/* TODO: Generate nas_count from ul_seq_no */
	uint32_t nas_count = 0;
	create_kenb_key(ue_entry->aia_sec_info->kasme.val, ue_entry->ue_sec_info.kenb_key, nas_count);
	icr_msg.IE_type = S1AP_INIT_CTXT_SETUP_REQ;
	icr_msg.ue_idx = service_req->ue_idx;
	icr_msg.enb_fd = ue_entry->enb_fd;
	icr_msg.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
	icr_msg.mme_s1ap_ue_id = service_req->ue_idx;
	icr_msg.ueag_max_dl_bitrate = ue_entry->ambr.max_requested_bw_dl;
	icr_msg.ueag_max_ul_bitrate = ue_entry->ambr.max_requested_bw_ul;
	icr_msg.bearer_id = ue_entry->bearer_id;
	memcpy(&(icr_msg.gtp_teid), &(ue_entry->s1u_sgw_u_fteid), sizeof(struct fteid));
	memcpy(&(icr_msg.sec_key), &(ue_entry->ue_sec_info.kenb_key), KENB_SIZE);

	//opened for write by s1 rel thread
	write_ipc_channel(g_Q_mme_to_s1ap_fd, (char *)&(icr_msg), S1AP_COMMON_REQ_BUF_SIZE);

	log_msg(LOG_INFO, "Post for service_req_wf_initctxt_resp processing. SUCCESS\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_servicereq_stage()
{
	close_ipc_channel(g_Q_servicereq_fd);
	log_msg(LOG_INFO, "Shutdown Service Request handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
service_request_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Service Request Handler Ready \n");
	g_mme_hdlr_status |= 1;
	g_mme_hdlr_status <<= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();
		
		service_request_processing();
		
		post_to_next();
		
	}

	return NULL;
}
