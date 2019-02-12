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
#include "detach_stage3_info.h"

/************************************************************************
Current file : Stage 7 handler.
ATTACH stages :
	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage3 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage4 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage5 handler]-->create session
	Stage 6 : create session resp-->[stage6 handler]-->init ctx setup
-->	Stage 7 : attach complete-->[stage7 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_ctx_release_complete_fd;

/*Making global just to avoid stack passing*/
static char ctx_release_complete[S1AP_CTXRELRESP_STAGE3_BUF_SIZE];

extern uint32_t detach_stage3_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "Detach Stage 3 reader - Ctx release"
			"complete: waiting\n");
	if ((g_Q_ctx_release_complete_fd  = open_ipc_channel(
					S1AP_CTXRELRESP_STAGE3_QUEUE, IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader Detach stage 3"
				"S1AP IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Detach Stage 3 reader - s1ap Ctx release"
			"complete: Connected\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(ctx_release_complete, 0, S1AP_CTXRELRESP_STAGE3_BUF_SIZE);
	while (bytes_read < S1AP_CTXRELRESP_STAGE3_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
						g_Q_ctx_release_complete_fd,
						ctx_release_complete,
						S1AP_CTXRELRESP_STAGE3_BUF_SIZE)) == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Ctx release response Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
detach_stage3_processing()
{
	/*Parse and validate  the buffer*/
	/*Find the UE*/
	/*Check the state*/
	/*Collect information for next processing*/
	/*post to next processing*/
	/*
	struct ctx_release_complete_Q_msg * resp =
		(struct ctx_release_complete_Q_msg *)ctx_release_complete;


	log_msg(LOG_INFO, "Ctx release response received for ue: %d \n",
			resp->ue_idx);
	*/

	/* TODO: remove entry from UE hash */
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_detach_stage3()
{
	close_ipc_channel(g_Q_ctx_release_complete_fd);
	log_msg(LOG_INFO, "Shutdown Detach Stage 3 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
detach_stage3_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Detach Stage 3 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		detach_stage3_processing();

		detach_stage3_counter++;
		/* post_to_next(); */
	}

	return NULL;
}
