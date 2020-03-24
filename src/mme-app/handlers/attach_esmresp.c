/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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
#include "stage5_info.h"
#include "stage5_s11_info.h"

/************************************************************************
Current file : Stage 5 handler.
ATTACH stages :
	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage3 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage4 handler]-->esm infor req
-->	Stage 5 : esm infor resp-->[stage5 handler]-->create session
	Stage 6 : create session resp-->[stage6 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage7 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_esmresp_fd;
int g_Q_CSreq_fd;

/*Making global just to avoid stack passing*/
static char buf[S1AP_ESMRESP_STAGE5_BUF_SIZE];

extern uint32_t attach_stage5_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((g_Q_esmresp_fd  = open_ipc_channel(S1AP_ESMRESP_STAGE5_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 5 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 5 reader - s1ap ESM info resp: Connected\n");

	/*Open destination queue for writing. It is AIR, ULR Q in this stage*/
	log_msg(LOG_INFO, "Stage 5 writer  - s11 Createsession: waiting\n");
	g_Q_CSreq_fd = open_ipc_channel(S11_CSREQ_STAGE5_QUEUE , IPC_WRITE);
	if (g_Q_CSreq_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S11 CS Request\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 5 writer - s11 CS request: Connected\n");
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_ESMRESP_STAGE5_BUF_SIZE );
	while (bytes_read < S1AP_ESMRESP_STAGE5_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_esmresp_fd, buf,
			S1AP_ESMRESP_STAGE5_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "ESM info response Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
stage5_processing()
{
	/*Parse and validate  the buffer*/
	struct esm_resp_Q_msg *esm_resp = (struct esm_resp_Q_msg*)buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(esm_resp->ue_idx);
    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
        log_msg(LOG_ERROR, "Ignore Stage5_processing for invalid UE . Index ", esm_resp->ue_idx);
        return E_FAIL;
    }

	ue_entry->ul_seq_no++;

	/*Check the state*/
	if(SUCCESS == esm_resp->status) {
		log_msg(LOG_INFO, "ESM response complete rcv. UE-%dd\n.",
			esm_resp->ue_idx);
		ue_entry->ue_state = STAGE5_WAITING;
	}
	else {
		log_msg(LOG_INFO, "ESM respfailed. UE-%d\n.",
			esm_resp->ue_idx);
		//Do something g_UE_list[0][secmode_resp->ue_idx].ue_state = STAGE4_WAITING;
	}

	memcpy(&(ue_entry->apn), &(esm_resp->apn), sizeof(struct apn_name));
	log_msg(LOG_INFO, "ESM information  response has APN - %s\n", ue_entry->apn.val);

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	/*Information to pass S11 application for create session*/
	struct esm_resp_Q_msg *esm_resp = (struct esm_resp_Q_msg*)buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(esm_resp->ue_idx);
    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
        log_msg(LOG_ERROR, "Ignore post_to_next for invalid UE . Index ", esm_resp->ue_idx);
        return E_FAIL;
    }
	struct CS_Q_msg cs_msg = {0};

	cs_msg.ue_idx = esm_resp->ue_idx;
	memcpy(cs_msg.IMSI, ue_entry->IMSI, BINARY_IMSI_LEN);

	// The selected apn by mme used for create session.
	memcpy(&(cs_msg.selected_apn), &(ue_entry->selected_apn),
		sizeof(struct apn_name));

	memcpy(&(cs_msg.tai), &(ue_entry->tai),
		sizeof(struct TAI));

	memcpy(&(cs_msg.utran_cgi), &(ue_entry->utran_cgi),
		sizeof(struct CGI));

	cs_msg.max_requested_bw_dl = ue_entry->ambr.max_requested_bw_dl;
	cs_msg.max_requested_bw_ul = ue_entry->ambr.max_requested_bw_ul;
	cs_msg.paa_v4_addr = ue_entry->pdn_addr.ip_type.ipv4.s_addr; /* host order */

	memset(cs_msg.MSISDN, 0, 10);
	memcpy(cs_msg.MSISDN,ue_entry->MSISDN,10);
    memcpy(&cs_msg.pco_options[0], &ue_entry->pco_options[0], sizeof(ue_entry->pco_options));
    cs_msg.pco_length = ue_entry->pco_length;
    log_msg(LOG_INFO, "PCO length %d \n", cs_msg.pco_length);

	write_ipc_channel(g_Q_CSreq_fd, (char *)&(cs_msg), S11_CSREQ_STAGE5_BUF_SIZE);
	log_msg(LOG_INFO, "Posted Create Session message to S11-app - stage 5.\n");
	attach_stage5_counter++;
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_stage5()
{
	close_ipc_channel(g_Q_esmresp_fd);
	close_ipc_channel(g_Q_CSreq_fd);
	log_msg(LOG_INFO, "Shutdown Stage 5 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
stage5_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Stage 5 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		stage5_processing();

		post_to_next();
	}

	return NULL;
}
