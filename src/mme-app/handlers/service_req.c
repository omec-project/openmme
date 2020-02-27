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
#include "stage1_info.h"
#include "stage2_info.h"
#include "servicereq_info.h"
#include "common_proc_info.h"

/************************************************************************
Current file : Service Request handler.
Service Request-->service_request_handler-> init ctxt setup [Service Accept]
**************************************************************************/

/****Globals and externs ***/


extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;
extern int g_tmsi_allocation_array[];
extern pthread_mutex_t s1ap_reject_queue_mutex;
static int g_Q_s1ap_service_reject;

static int g_Q_servicereq_fd;
static int g_Q_authreq_fd;
extern int g_Q_s1ap_common_reject;
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

    /*Open destination queue for writing s1ap service req failure */
	g_Q_s1ap_service_reject = open_ipc_channel(S1AP_REQ_REJECT_QUEUE, IPC_WRITE);
	if (g_Q_s1ap_service_reject == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: S1AP Reject Queue \n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage1 writer - S1AP reject Pipe : Connected\n");
 
	
    log_msg(LOG_INFO, "Stage 2 writer  - s1ap Auth request: waiting\n");
	g_Q_authreq_fd = open_ipc_channel(S1AP_AUTHREQ_STAGE2_QUEUE, IPC_WRITE);

	if (g_Q_authreq_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: s1ap Auth req\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage2 writer - s1ap Auth request: Connected\n");
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
    if(service_req->ue_idx >= 10000)
    {
        log_msg(LOG_INFO, "TMSI out of range %d ", service_req->ue_idx); 
        return E_MAPPING_FAILED;
    }
    
    unsigned int ue_index = g_tmsi_allocation_array[service_req->ue_idx];
    if(ue_index == -1 )
    {
        log_msg(LOG_INFO, "TMSI not found %d ", service_req->ue_idx); 
        return E_MAPPING_FAILED;
    }

    service_req->ue_idx = ue_index;
    struct UE_info *ue_entry = GET_UE_ENTRY(service_req->ue_idx);

    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
	    log_msg(LOG_INFO, "Service request received for invalid UE ");
        return E_FAIL;
    }

	log_msg(LOG_INFO, "Service request received for ue %d\n",
			service_req->ue_idx);

	ue_entry->ue_state = SVC_REQ_WF_INIT_CTXT_RESP;
    ue_entry->ue_curr_proc = SERVICE_REQ_PROC;
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
    log_msg(LOG_DEBUG, "Authentication for Service Req");
    struct authreq_info authreq;
	struct service_req_Q_msg *service_req =
				(struct service_req_Q_msg *) buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(service_req->ue_idx);

    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
	{
		log_msg(LOG_INFO, "Failed to retrieve UE context for idx %d\n",
					      service_req->ue_idx);
		return -1;
	}
    create_integrity_key(ue_entry->aia_sec_info->kasme.val,
                         ue_entry->ue_sec_info.int_key);

    ue_entry->dl_seq_no = 0;

    log_msg(LOG_INFO, "UE index  %d\n", service_req->ue_idx);


    /*Create message to send to S1ap*/
    authreq.enb_fd = ue_entry->enb_fd;
    authreq.ue_idx = service_req->ue_idx;
    authreq.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
    memcpy(&(authreq.rand), &(ue_entry->aia_sec_info->rand.val),
           NAS_RAND_SIZE);
    memcpy(&(authreq.autn), &(ue_entry->aia_sec_info->autn.val),
           NAS_AUTN_SIZE);

    /*post message to next stage i.e. s1ap auth req*/
    write_ipc_channel(g_Q_authreq_fd, (char *)&(authreq),
                      S1AP_AUTHREQ_STAGE2_BUF_SIZE);
    log_msg(LOG_INFO, "Stage 2. Posted message to s1ap - Auth req\n");
    return SUCCESS;
}

/*
* Post message to s1ap handler about the failure of this stage 
*/
static int
post_service_reject()
{
    struct service_req_Q_msg *service_req =
        (struct service_req_Q_msg *) buf;
    log_msg(LOG_INFO, "Sending Service Rej for MTMSI %d\n",
              service_req->ue_idx);
    struct s1ap_common_req_Q_msg s1ap_rej = {0};
    s1ap_rej.IE_type = S1AP_SERVICE_REJ;
    s1ap_rej.ue_idx = 0;
    s1ap_rej.mme_s1ap_ue_id = 0;
    s1ap_rej.enb_s1ap_ue_id = service_req->s1ap_enb_ue_id;
    s1ap_rej.enb_fd = service_req->enb_fd;
    s1ap_rej.emm_cause = emmCause_ue_id_not_derived_by_network;

    pthread_mutex_lock(&s1ap_reject_queue_mutex);
    write_ipc_channel(g_Q_s1ap_common_reject, 
                      (char *)&(s1ap_rej),
                      S1AP_COMMON_REQ_BUF_SIZE);
    pthread_mutex_unlock(&s1ap_reject_queue_mutex);
    return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_servicereq_stage()
{
	close_ipc_channel(g_Q_servicereq_fd);
	close_ipc_channel(g_Q_s1ap_service_reject);
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
		
		if(SUCCESS == service_request_processing())
        {
		
		    post_to_next();
        }
        else
        {
            post_service_reject();
        }
		
	}

	return NULL;
}
