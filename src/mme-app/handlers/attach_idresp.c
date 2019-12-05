/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
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
#include "stage3_info.h"
#include "s1ap_mme_msg.h"

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_identityresp_fd;

/*Making global just to avoid stack passing*/
static char buf[S1AP_IDRESP_BUF_SIZE];

/* Add counter */
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((g_Q_identityresp_fd  = open_ipc_channel(S1AP_ID_RSP_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 3 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 3 reader - s1ap Authentication response : Connected\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_IDRESP_BUF_SIZE );
	while (bytes_read < S1AP_IDRESP_BUF_SIZE) {
		if ((bytes_read = read_ipc_channel(
			g_Q_identityresp_fd, buf, S1AP_IDRESP_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Authentication response Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
identity_response_processing()
{
	/*Parse and validate  the buffer*/
	struct identityResp_Q_msg *id_resp = (struct identityResp_Q_msg *)buf;
	struct UE_info *ue_entry = GET_UE_ENTRY(id_resp->ue_idx);

	/*Check the state*/
	if(SUCCESS != id_resp->status) 
    {
	  return E_FAIL; 
	}
	log_msg(LOG_INFO, "Identity response done for UE: %d\n",
		id_resp->ue_idx);

    /* 
     * update the IMSI and continue attach procedure  
     */
    memcpy(ue_entry->IMSI, id_resp->IMSI, BINARY_IMSI_LEN);
	/* Ready post to next processing*/
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	struct identityResp_Q_msg *idresp = (struct identityResp_Q_msg *)buf;
	struct UE_info *ue_entry = GET_UE_ENTRY(idresp->ue_idx);
	log_msg(LOG_INFO, "Stich the fsm and pass this identity response to UE fsm. UE-%d.\n", idresp->ue_idx);
    post_to_hss_stage(ue_entry->ue_index); 
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_idRsp_stage()
{
	close_ipc_channel(g_Q_identityresp_fd);
	log_msg(LOG_INFO, "Shutdown Stage 3 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
identity_rsp_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Stage 3 ready.\n");
    /* TODO :WE need to check these bitmaps */
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		int ret = identity_response_processing();

        if(ret == SUCCESS)
        {
		  post_to_next();
        }
	}

	return NULL;
}
