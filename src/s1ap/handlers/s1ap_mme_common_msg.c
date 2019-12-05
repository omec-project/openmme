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
#include <unistd.h>
#include <stdint.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "s1ap.h"
#include "s1ap_config.h"
#include "main.h"
#include "common_proc_info.h"

/****Globals and externs ***/

/*Making global just to avoid stack passing*/
static char s1ap_common_req[S1AP_COMMON_REQ_BUF_SIZE];

struct s1ap_common_req_Q_msg *g_mmeS1apInfo;

static Buffer g_ctxrel_buffer;

extern int g_enb_fd;

extern ipc_handle ipcHndl_mme_to_s1ap_msg;

/****Global and externs end***/
/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((ipcHndl_mme_to_s1ap_msg  = open_ipc_channel(
			S1AP_MME_TO_S1AP_QUEUE, IPC_READ)) == -1) {
		log_msg(LOG_ERROR, "Error in opening reader for MME to S1AP msgs  %s\n",
				S1AP_MME_TO_S1AP_QUEUE);
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "MME to S1AP msgs reader: Connected.\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(s1ap_common_req, 0, S1AP_COMMON_REQ_BUF_SIZE);
	while (bytes_read < S1AP_COMMON_REQ_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
				ipcHndl_mme_to_s1ap_msg, s1ap_common_req,
				S1AP_COMMON_REQ_BUF_SIZE)) == -1) {
					log_msg(LOG_ERROR, "Error in reading \n");
					/* TODO : Add proper error handling */
				}
		log_msg(LOG_INFO, "Mme to S1ap Message Received, len: %d", bytes_read);
	}

	return bytes_read;
}

/**
* message processing for ue context release
*/
static int
process_ctx_rel_cmd()
{
    log_msg(LOG_DEBUG,"Process Ctx rel cmd.");
	uint32_t length = 0;
    uint8_t *buffer = NULL;

    int ret = s1ap_mme_encode_initiating(g_mmeS1apInfo, &buffer, &length);
    if(ret == -1)
    {
        log_msg(LOG_ERROR, "Encoding ctx rel cmd failed.\n");
        return E_FAIL;
    }

	buffer_copy(&g_ctxrel_buffer, buffer, length);

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_ctx_rel_command()
{
	send_sctp_msg(g_mmeS1apInfo->enb_fd, g_ctxrel_buffer.buf, g_ctxrel_buffer.pos, 1);
	log_msg(LOG_INFO, "buffer size is %d\n", g_ctxrel_buffer.pos);
	log_msg(LOG_INFO, "\n-----Message handlingcompleted.---\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_mme_to_s1ap_msg_stage()
{
	close_ipc_channel(ipcHndl_mme_to_s1ap_msg);
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
mme_to_s1ap_msg_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "mme to s1ap msg handler ready.\n");

	while(1){
        read_next_msg();

	    g_mmeS1apInfo =
		    	(struct s1ap_common_req_Q_msg *) s1ap_common_req;
        switch(g_mmeS1apInfo->IE_type)
        {
            case S1AP_CTX_REL_CMD:
                log_msg(LOG_DEBUG, "S1AP Ctx Release Cmd Start");
                process_ctx_rel_cmd();
                post_ctx_rel_command();
                break;
            default:
                    log_msg(LOG_DEBUG, "Unknown msg %d\n", g_mmeS1apInfo->IE_type);
        }
	}

	return NULL;
}
