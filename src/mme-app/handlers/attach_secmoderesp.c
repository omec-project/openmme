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

#include "log.h"
#include "mme_app.h"
#include "ue_table.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage4_info.h"
#include "stage5_s11_info.h"

/************************************************************************
Current file : Stage 4 handler.
ATTACH stages :
	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage3 handler]-->Sec mode cmd
-->	Stage 4 : sec mode resp-->[stage4 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage5 handler]-->create session
	Stage 6 : create session resp-->[stage6 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage7 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_secmoderesp_fd;
static int g_Q_esmreq_fd;
extern int g_Q_CSreq_fd;

/*Making global just to avoid stack passing*/
static char buf[S1AP_SECRESP_STAGE4_BUF_SIZE];

extern uint32_t attach_stage4_counter;
extern uint32_t attach_stage5_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((g_Q_secmoderesp_fd  = open_ipc_channel(S1AP_SECRESP_STAGE4_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 4 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 4 reader - s1ap Security mode response : Connected\n");

	/*Open destination queue for writing. It is AIR, ULR Q in this stage*/
	log_msg(LOG_INFO, "Stage 4 writer  - s1ap ESM info req: waiting\n");
	g_Q_esmreq_fd = open_ipc_channel(S1AP_ESMREQ_STAGE4_QUEUE, IPC_WRITE);
	if (g_Q_esmreq_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S1ap-ESM info req\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 4 writer - s1ap ESM info request: Connected\n");
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_SECRESP_STAGE4_BUF_SIZE);
	while (bytes_read < S1AP_SECRESP_STAGE4_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_secmoderesp_fd, buf,
			S1AP_SECRESP_STAGE4_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Security mode response Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
stage4_processing()
{
	/*Parse and validate  the buffer*/
	struct secmode_resp_Q_msg *secmode_resp = (struct secmode_resp_Q_msg*)buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(secmode_resp->ue_idx);

	ue_entry->ul_seq_no = 0;

	/*Check the state*/
	if(SUCCESS == secmode_resp->status) {
		log_msg(LOG_INFO, "Sec mode complete rcv. UE-%dd\n",
			secmode_resp->ue_idx);
		ue_entry->ue_state = STAGE4_WAITING;
	}
	else {
		log_msg(LOG_INFO, "Sec mode failed. UE-%d\n",
			secmode_resp->ue_idx);
		//Do something ue_entry->ue_state = STAGE4_WAITING;
	}

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	struct esm_req_Q_msg esm_req;
	struct secmode_resp_Q_msg *secmode_resp = (struct secmode_resp_Q_msg*)buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(secmode_resp->ue_idx);

	if(ue_entry->esm_info_tx_required) {
		esm_req.enb_fd = ue_entry->enb_fd;
		esm_req.ue_idx = secmode_resp->ue_idx;
		esm_req.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
		esm_req.dl_seq_no = ue_entry->dl_seq_no++;
		memcpy(&(esm_req.int_key), &(ue_entry->ue_sec_info.int_key),
				NAS_INT_KEY_SIZE);
		esm_req.pti = ue_entry->pti;

		write_ipc_channel(g_Q_esmreq_fd, (char *)&(esm_req),
				S1AP_ESMREQ_STAGE4_BUF_SIZE);

		log_msg(LOG_INFO, "ESM msg posted to s1ap Q UE-%d.\n", esm_req.ue_idx);
		attach_stage4_counter++;
	} else {
		struct CS_Q_msg cs_msg;

		cs_msg.ue_idx = secmode_resp->ue_idx;
		memcpy(cs_msg.IMSI, ue_entry->IMSI, BINARY_IMSI_LEN);

		/*Where to get apn_name from? esm_info step is skipped here, which get
		 * apn_name to use at this stage.*/
		memcpy(&(cs_msg.apn), &(ue_entry->apn),
			sizeof(struct apn_name));

		memcpy(&(cs_msg.tai), &(ue_entry->tai),
			sizeof(struct TAI));

		memcpy(&(cs_msg.utran_cgi), &(ue_entry->utran_cgi),
			sizeof(struct CGI));

		cs_msg.max_requested_bw_dl = ue_entry->ambr.max_requested_bw_dl;
		cs_msg.max_requested_bw_ul = ue_entry->ambr.max_requested_bw_ul;

		memset(cs_msg.MSISDN, 0, 10);
		memcpy(cs_msg.MSISDN,ue_entry->MSISDN,10);

		write_ipc_channel(g_Q_CSreq_fd, (char *)&(cs_msg),
				S11_CSREQ_STAGE5_BUF_SIZE);

		log_msg(LOG_INFO, "Posted Create Session message to S11-app - stage 5\n");
		log_msg(LOG_INFO, "Posted Create Session message to S11-app - stage 5.\n");
		attach_stage5_counter++;
	}
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_stage4()
{
	close_ipc_channel(g_Q_secmoderesp_fd);
	close_ipc_channel(g_Q_esmreq_fd);
	log_msg(LOG_INFO, "Shutdown Stage 4 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
stage4_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Stage 4 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		stage4_processing();

		post_to_next();
	}

	return NULL;
}
