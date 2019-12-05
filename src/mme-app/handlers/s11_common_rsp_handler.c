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
#include "stage1_s6a_msg.h"
#include "stage2_info.h"
#include "common_proc_info.h"

/************************************************************************
Current file : detach stage 2 handler.
DEATTACH stages :
	Stage 1 :
-->	Stage 2 :
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_s11_rsp_fd;
static int g_Q_mme_to_s1ap_fd;

/*Making global just to avoid stack passing*/

static char buf[S11_COMM_RES_STAGE_BUF_SIZE];

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "Connecting to  common resp reader .\n");
	if ((g_Q_s11_rsp_fd  = open_ipc_channel(S11_RECV_RSP_STAGE_QUEUE,
			IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening Common S11 resp IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "S11 resp stage: Connected\n");
	/*Writing the detach signal to S11 Queue*/
	if ((g_Q_mme_to_s1ap_fd  = open_ipc_channel(S1AP_MME_TO_S1AP_QUEUE,
						IPC_WRITE)) == -1){
		log_msg(LOG_ERROR, "Error in opening MME to S1AP write IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "MME to S1AP write IPC Connected\n");

	return;
}

static int
process_rabr_resp()
{
	struct s11_resp_Q_msg *rabr_resp = (struct s11_resp_Q_msg *)buf;
	log_msg(LOG_INFO, "RABR resp for UE idx = %d\n", rabr_resp->ue_idx);

	return rabr_resp->ue_idx;
}

static int
read_next_msg()
{
	int bytes_read=0;

    memset(buf, 0, S11_COMM_RES_STAGE_BUF_SIZE);
	while (bytes_read < S11_COMM_RES_STAGE_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_s11_rsp_fd, buf,
			 S11_COMM_RES_STAGE_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "S11 response Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Post message to next handler of the stage
*/
static int
post_ctx_rel_command(int ue_index)
{
	struct UE_info *ue_entry = GET_UE_ENTRY(ue_index);
	struct s1ap_common_req_Q_msg req;

    log_msg(LOG_INFO, "Send UE Ctx Release Command for UE %d\n", ue_index);

    /*Create message to send to S1ap*/

    req.IE_type = S1AP_CTX_REL_CMD;
    req.enb_fd = ue_entry->enb_fd;
    req.mme_s1ap_ue_id = ue_index;
    req.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
    req.cause.present = s1apCause_PR_radioNetwork;
    req.cause.choice.radioNetwork = s1apCauseRadioNetwork_user_inactivity; 
    /*post message to next stage i.e. s1ap auth req*/
    write_ipc_channel(g_Q_mme_to_s1ap_fd, (char *)&(req),
                      S1AP_COMMON_REQ_BUF_SIZE);
    log_msg(LOG_INFO, "Posted message to s1ap - DCtx Rel Command\n");

	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_s11_rsp_common_handler()
{
	close_ipc_channel(g_Q_s11_rsp_fd);
	close_ipc_channel(g_Q_mme_to_s1ap_fd);
	log_msg(LOG_INFO, "Shutdown Stage common rsp handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
s11_rsp_common_mme_handler(void *data)
{
	int ue_index = -1;
	init_stage();
	log_msg(LOG_INFO, "S11 rsp handler ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
        read_next_msg();

	    struct s11_resp_Q_msg *s11_common_resp =
		    	(struct s11_resp_Q_msg *) buf;
        switch(s11_common_resp->IE_type)
        {
            case S11_RABR_RESP:
                log_msg(LOG_DEBUG, "RABR RSP Start");
                ue_index = process_rabr_resp();
                if(ue_index >= 0)
                {
                    post_ctx_rel_command(ue_index);
                }
                else
                {
                    log_msg(LOG_DEBUG, "RABR rsp handling failed");
                }
                break;
            default:
                    log_msg(LOG_DEBUG, "Unknown msg %d\n", s11_common_resp->IE_type);
        }
	}

	return NULL;
}
