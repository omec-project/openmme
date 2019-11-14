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
#include "sec.h"

/************************************************************************
Current file : Stage 6 handler.
ATTACH stages :
	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage3 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage4 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage5 handler]-->create session
-->	Stage 6 : create session resp-->[stage6 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage7 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;
static int g_Q_csresp_fd;
static int g_Q_icsreq_fd;

/*Making global just to avoid stack passing*/
static char buf[S11_CSRESP_STAGE6_BUF_SIZE];
extern uint32_t attach_stage6_counter;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((g_Q_csresp_fd  = open_ipc_channel(S11_CSRESP_STAGE6_QUEUE ,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 6 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 6 reader - s11 Create session resp: Connected\n");

	/*Open destination queue for writing*/
	log_msg(LOG_INFO, "Stage 6 writer  - s1ap Initial ctx setup: waiting\n");
	g_Q_icsreq_fd = open_ipc_channel(S1AP_ICSREQ_STAGE6_QUEUE, IPC_WRITE);
	if (g_Q_icsreq_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:s1ap ICS Request\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 6 writer - s1ap ICS request: Connected\n");
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S11_CSRESP_STAGE6_BUF_SIZE);
	while (bytes_read < S11_CSRESP_STAGE6_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_csresp_fd, buf,
			 S11_CSRESP_STAGE6_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Create session response Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
stage6_processing()
{
	struct csr_Q_msg *csr_info = (struct csr_Q_msg *)buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(csr_info->ue_idx);

	/*Parse and validate  the buffer*/
	//if(csr_info->status) check for status

	/*Collect information for next processing*/
	memcpy(&(ue_entry->s11_sgw_c_fteid),
		&(csr_info->s11_sgw_fteid), sizeof(struct fteid));

	memcpy(&(ue_entry->s5s8_pgw_c_fteid),
		&(csr_info->s5s8_pgwc_fteid), sizeof(struct fteid));

	memcpy(&(ue_entry->s1u_sgw_u_fteid),
		&(csr_info->s1u_sgw_fteid), sizeof(struct fteid));

	memcpy(&(ue_entry->s5s8_pgw_u_fteid),
		&(csr_info->s5s8_pgwu_fteid), sizeof(struct fteid));

	memcpy(&(ue_entry->pdn_addr), &(csr_info->pdn_addr),
		sizeof(struct PAA));

	/*post to next processing*/
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	struct init_ctx_req_Q_msg icr_msg;
	struct csr_Q_msg *csr_info = (struct csr_Q_msg *)buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(csr_info->ue_idx);

	log_msg(LOG_INFO, "Post for s1ap processing - stage 6.\n");

	/* create KeNB key */
	/* TODO: Generate nas_count from ul_seq_no */
	uint32_t nas_count = 0;
	create_kenb_key(ue_entry->aia_sec_info->kasme.val,
			ue_entry->ue_sec_info.kenb_key, nas_count);

	icr_msg.ue_idx = csr_info->ue_idx;
	icr_msg.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
	icr_msg.exg_max_dl_bitrate = ue_entry->ambr.max_requested_bw_dl;
	icr_msg.exg_max_ul_bitrate = ue_entry->ambr.max_requested_bw_ul;
	icr_msg.bearer_id = ue_entry->bearer_id;
	icr_msg.dl_seq_no = ue_entry->dl_seq_no++;
	icr_msg.enb_fd = ue_entry->enb_fd;

	memcpy(&(icr_msg.gtp_teid), &(ue_entry->s1u_sgw_u_fteid), sizeof(struct fteid));

	memcpy(&(icr_msg.tai), &(ue_entry->tai), sizeof(struct TAI));

	/*s1ap handler to use apn name and tai to generate mcc, mcn appended name*/
	memcpy(&(icr_msg.apn), &(ue_entry->apn), sizeof(struct apn_name));
	memcpy(&(icr_msg.pdn_addr), &(ue_entry->pdn_addr), sizeof(struct PAA));
	memcpy(&(icr_msg.int_key), &(ue_entry->ue_sec_info.int_key),
			NAS_INT_KEY_SIZE);
	memcpy(&(icr_msg.sec_key), &(ue_entry->ue_sec_info.kenb_key),
			KENB_SIZE);
	memcpy(&(icr_msg.pti), &(ue_entry->pti), 1);

	write_ipc_channel(g_Q_icsreq_fd, (char *)&(icr_msg), S1AP_ICSREQ_STAGE6_BUF_SIZE);

	/*Call DUMMY MB funcion*/
	//test: send_dummy_mbr();
	attach_stage6_counter++;
	log_msg(LOG_INFO, "Post for s1ap processing - stage 6. SUCCESS\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_stage6()
{
	close_ipc_channel(g_Q_csresp_fd);
	close_ipc_channel(g_Q_icsreq_fd);
	log_msg(LOG_INFO, "Shutdown Stage 6 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
stage6_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Stage 6 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		stage6_processing();

		post_to_next();
	}

	return NULL;
}
