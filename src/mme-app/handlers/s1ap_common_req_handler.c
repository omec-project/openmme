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
#include "common_proc_info.h"


/************************************************************************
Current file : Common S1ap Msg Handler..
DETACH stages :

**************************************************************************/

/****Globals and externs ***/


extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_s1apread_fd;
static int g_Q_S11_write_fd;

static char s1ap_comm_req[S1AP_COMMON_REQ_BUF_SIZE];

struct s11_req_Q_msg g_rabr_msg;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/

static void
init_stage()
{
	log_msg(LOG_INFO, "S1ap generic msg open ipc channel\n");

	/*Reading for the detach signal from S1Ap */
	if (( g_Q_s1apread_fd  = open_ipc_channel(S1AP_MME_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader  S1AP IPC channel.\n");
		pthread_exit(NULL);
	}

	log_msg(LOG_INFO, "s11  write response: waiting\n");

	/*Writing the detach signal to S11 Queue*/
	if ((g_Q_S11_write_fd  = open_ipc_channel(S11_SEND_REQ_STAGE_QUEUE,
						IPC_WRITE)) == -1){
		log_msg(LOG_ERROR, "Error in opening MME to S11 send msgIPC channel.\n");
		pthread_exit(NULL);
	}

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(s1ap_comm_req, 0, S1AP_COMMON_REQ_BUF_SIZE);
	while (bytes_read < S1AP_COMMON_REQ_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_s1apread_fd, s1ap_comm_req,
			S1AP_COMMON_REQ_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "**************** S1ap request Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
ctx_rel_req_processing()
{
	struct s1ap_common_req_Q_msg *ctxRelreq =
			(struct s1ap_common_req_Q_msg *) s1ap_comm_req;
	struct UE_info *ue_entry = GET_UE_ENTRY(ctxRelreq->ue_idx);

	log_msg(LOG_INFO, "Ctx Release request received for ue %d\n",
			ctxRelreq->ue_idx);

	ue_entry->ul_seq_no++;

    g_rabr_msg.IE_type = S11_RABR_REQ;
	memcpy(&(g_rabr_msg.s11_sgw_c_fteid),
			&(ue_entry->s11_sgw_c_fteid),
			sizeof(ue_entry->s11_sgw_c_fteid));

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	/* Post to s11-app */
	write_ipc_channel(g_Q_S11_write_fd, (char *)&(g_rabr_msg),
			S11_COMM_REQ_STAGE_BUF_SIZE);
	log_msg(LOG_INFO, "Posted msg to s11-app.\n");

	return SUCCESS;
}


/* Thread exit function */
void
shutdown_common_stage()
{
	close_ipc_channel(g_Q_s1apread_fd);
	close_ipc_channel(g_Q_S11_write_fd);
	log_msg(LOG_INFO, "Shutdown Stage handler \n");
	pthread_exit(NULL);
	return;
}


/**
* Thread function for stage.
*/
void*
s1ap_req_common_mme_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Stage  Ready \n");

	while(1){
		read_next_msg();

	    struct s1ap_common_req_Q_msg *s1ap_common_req =
		    	(struct s1ap_common_req_Q_msg *) s1ap_comm_req;
        switch(s1ap_common_req->IE_type)
        {
            case S1AP_CTX_REL_REQ:
                log_msg(LOG_DEBUG, "S1ap Ctx Release req handling Start");
		        if (ctx_rel_req_processing() == SUCCESS)
                {
			        post_to_next();
                }
                else
                {
                    log_msg(LOG_ERROR, "S1ap Ctx Release req handling failed");
                }
                break;
            default:
                    log_msg(LOG_ERROR, "Unknown msg %d\n", s1ap_common_req->IE_type);
        }
	}

	return NULL;
}
