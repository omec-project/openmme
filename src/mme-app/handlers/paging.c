/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
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
#include "paging_info.h"
#include "common_proc_info.h"
#include "ddn_info.h"
#include "gtpv2c_ie.h"

/************************************************************************
Paging handler.
Flow : 36.413 - release 15 - Section 8.5
		DDN Request : SGW-->MME 
--->		Paging MME --> eNB
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_ddn_fd;
static int g_Q_ddn_ack_fd;
static int g_Q_paging_fd;

/*Making global just to avoid stack passing*/
static char DDN_buf[S11_DDN_BUF_SIZE];
static struct ddn_ack_Q_msg ddn_ack_msg;

extern uint32_t paging_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "DDN reader complete: waiting\n");
	if ((g_Q_ddn_fd  = open_ipc_channel(
					S11_DDN_QUEUE, IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader - DDN"
				"S11 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "DDN reader complete: Connected\n");
	g_Q_paging_fd = open_ipc_channel(S1AP_PAGING_QUEUE, IPC_WRITE);
	if (g_Q_paging_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:s1ap Paging\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "s1ap Paging writer: Connected\n");

	/*Open destination queue for writing*/
	log_msg(LOG_INFO, "Ddn writer  - s11 Downlink data Notification Acknowledge: waiting\n");
	g_Q_ddn_ack_fd = open_ipc_channel(S11_DDN_ACK_QUEUE, IPC_WRITE);
	if (g_Q_ddn_ack_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:s11 ddn Acknowledge\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Ddn writer - s11 DDN Acknowledge: Connected\n");
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(DDN_buf, 0, S11_DDN_BUF_SIZE);
	while (bytes_read < S11_DDN_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
						g_Q_ddn_fd,
						DDN_buf,
						S11_DDN_BUF_SIZE)) == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "DDN Msg Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
DDN_processing()
{
	struct ddn_Q_msg *ddn_info = (struct ddn_Q_msg *)DDN_buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(ddn_info->ue_idx);

	if (ue_entry == NULL || !IS_VALID_UE_INFO(ue_entry)) {
		ddn_ack_msg.cause = GTPV2C_CAUSE_CONTEXT_NOT_FOUND;
        log_msg(LOG_ERROR, "Invalid UE. Send Context not found in DDN Ack ");
        return -1;
	} else {
		ddn_ack_msg.cause = GTPV2C_CAUSE_REQUEST_ACCEPTED;
		// populate page msg struct

		//set UE State
		ue_entry->ue_state = PAGING_WF_SVC_REQ;
	}

	/*post to next processing*/
	return ddn_info->ue_idx;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next(int ue_idx)
{
	struct UE_info *ue_entry =  GET_UE_ENTRY(ue_idx);
    if(NULL == ue_entry || !IS_VALID_UE_INFO(ue_entry))
    {
        log_msg(LOG_ERROR,"UE entry not found %d.\n", ue_idx);
        return -1;
    }
    log_msg(LOG_DEBUG, "Found valid UE with index : %d.\n",ue_idx);

    write_ipc_channel(g_Q_ddn_ack_fd, 
			  (char *)(&ddn_ack_msg),
			  S11_DDN_ACK_BUF_SIZE);

	log_msg(LOG_INFO, "Posted Downlink data Notification acknowledge message to s11-app.\n");

	struct s1ap_common_req_Q_msg req;

    log_msg(LOG_INFO, "Send Paging request for UE %d\n", ue_idx);

    /*Create message to send to S1ap*/

    req.IE_type = S1AP_PAGING_REQ;
    req.enb_fd = ue_entry->enb_fd;
    req.ue_idx = ue_idx;
    req.cn_domain = CN_DOMAIN_PS;
    memcpy(req.imsi, ue_entry->IMSI, BINARY_IMSI_LEN);
    memcpy(&req.tai, &ue_entry->tai, sizeof(struct TAI));

	write_ipc_channel(g_Q_paging_fd, (char *)&(req), S1AP_COMMON_REQ_BUF_SIZE);

	log_msg(LOG_INFO, "Post for paging processing. SUCCESS\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_paging()
{
	close_ipc_channel(g_Q_ddn_fd);
	close_ipc_channel(g_Q_ddn_ack_fd);
	close_ipc_channel(g_Q_paging_fd);
	log_msg(LOG_INFO, "Shutdown DDN/Paging handlers. \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
DDN_handler(void *data)
{
    int ue_index = -1;
	init_stage();
	log_msg(LOG_INFO, "DDN stage ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		ue_index = DDN_processing();

		post_to_next(ue_index);
		paging_counter++;
        ue_index = -1;
	}

	return NULL;
}
