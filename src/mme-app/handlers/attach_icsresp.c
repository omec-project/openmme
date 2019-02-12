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
#include <arpa/inet.h>
#include <unistd.h>

#include "mme_app.h"
#include "ue_table.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage7_info.h"

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

static int g_Q_ics_resp_fd;
static int g_Q_MBreq_fd;

/*Making global just to avoid stack passing*/
static char ics_resp[S1AP_ICSRESP_STAGE7_BUF_SIZE];

extern uint32_t attach_stage7_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "Stage 7 reader - s1ap ICS esponse: waiting\n");
	if ((g_Q_ics_resp_fd = open_ipc_channel(S1AP_ICSRESP_STAGE7_QUEUE ,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 7 S1AP IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 7 reader - s1ap Attach complete: Connected\n");

	/*Open destination queue for writing*/
	log_msg(LOG_INFO, "Stage 7 writer  - s11 MB Request: waiting\n");
	g_Q_MBreq_fd = open_ipc_channel(S11_MBREQ_STAGE7_QUEUE, IPC_WRITE);
	if (g_Q_MBreq_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:MB Request\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 7 writer - s11 MB request: Connected\n");
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(ics_resp, 0, S1AP_ICSRESP_STAGE7_BUF_SIZE);
	while (bytes_read < S1AP_ICSRESP_STAGE7_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_ics_resp_fd, ics_resp,
			 S1AP_ICSRESP_STAGE7_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Init ctx resp received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
stage7_processing()
{
	struct initctx_resp_Q_msg *ics_res =
		(struct initctx_resp_Q_msg *)ics_resp;
	struct UE_info *ue_entry =  GET_UE_ENTRY(ics_res->ue_idx);

	/**validations/checks*/

	ue_entry->eRAB_id = ics_res->eRAB_id;
	/*hard code to ipv4 for now. TODO v6 support from s1ap*/
	ue_entry->s1u_enb_u_fteid.header.v4 = 1;

	ue_entry->s1u_enb_u_fteid.header.teid_gre =
		ics_res->gtp_teid;

	ue_entry->s1u_enb_u_fteid.ip.ipv4 =
		*(struct in_addr*)&ics_res->transp_layer_addr;

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	struct initctx_resp_Q_msg *ics_resp_info =
				(struct initctx_resp_Q_msg *)ics_resp;
	struct UE_info *ue_entry =  GET_UE_ENTRY(ics_resp_info->ue_idx);
	struct MB_Q_msg mb_msg;

	mb_msg.ue_idx = ((struct initctx_resp_Q_msg *)ics_resp_info)->ue_idx;
	memset(mb_msg.indication, 0, S11_MB_INDICATION_FLAG_SIZE); /*TODO : future*/
	mb_msg.bearer_id = ue_entry->bearer_id;

	memcpy(&(mb_msg.s11_sgw_c_fteid), &(ue_entry->s11_sgw_c_fteid),
		sizeof(struct fteid));

	memcpy(&(mb_msg.s1u_enb_fteid), &(ue_entry->s1u_enb_u_fteid),
		sizeof(struct fteid));

	write_ipc_channel(g_Q_MBreq_fd, (char *)&(mb_msg),
			S11_MBREQ_STAGE7_BUF_SIZE);
	log_msg(LOG_INFO, "Send MB data from mme to s11 : stage7\n");

	attach_stage7_counter++;
	return SUCCESS;
}

/*Test function to send dummy MB*/
void
send_dummy_mbr()
{
	struct MB_Q_msg mb_msg;

	log_msg(LOG_INFO, "Sending dummy MB request\n");
	memset(mb_msg.indication, 0, S11_MB_INDICATION_FLAG_SIZE); /*TODO : future*/
	mb_msg.bearer_id = 5;

	mb_msg.s11_sgw_c_fteid.header.v4 =1;
	mb_msg.s11_sgw_c_fteid.header.teid_gre = 0xeeffc000;

	mb_msg.s1u_enb_fteid.header.v4 = 1;
	mb_msg.s1u_enb_fteid.header.teid_gre = 0x5f000000;
	inet_aton("11.1.1.101", &(mb_msg.s1u_enb_fteid.ip.ipv4));

	write_ipc_channel(g_Q_MBreq_fd, (char *)&(mb_msg),
			S11_MBREQ_STAGE7_BUF_SIZE);
}

/**
* Thread exit function for future reference.
*/
void
shutdown_stage7()
{
	close_ipc_channel(g_Q_ics_resp_fd);
	close_ipc_channel(g_Q_MBreq_fd);
	log_msg(LOG_INFO, "Shutdown Stage 7 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
stage7_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Stage 7 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		stage7_processing();

		post_to_next();
	}

	return NULL;
}
