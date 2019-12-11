/*
 * Copyright 2019-present Open Networking Foundation
 *
 * SPDX-License-Identifier: Apache-2.0
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
#include "detach_stage1_info.h"
#include "s1ap_mme_msg.h"


/************************************************************************
Current file : Stage 1  Dettach handler.
DETACH stages :

**************************************************************************/

/****Globals and externs ***/


extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_tauReq_fd;
static int g_Q_tauRsp_fd;

/*Making global just to avoid stack passing*/

static char tauReq[S1AP_TAUREQ_BUF_SIZE];
/* static char detach_resp[S11_DETACHRESP_STAGE2_BUF_SIZE]; * */

struct tauResp_Q_msg g_tau_rsp_msg;
extern uint32_t tau_req_counter;
extern uint32_t tau_response_accept_counter;
extern uint32_t tau_response_reject_counter;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/

static void
init_stage()
{
	log_msg(LOG_INFO, "TAU Request Reader - : waiting\n");

	/*Reading for the detach signal from S1Ap */
	if (( g_Q_tauReq_fd  = open_ipc_channel(S1AP_TAUREQ_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening TAU Request reader IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "TAU Rewquest Reader : Connected\n");

	log_msg(LOG_INFO, "TAU Response writer starting\n");
	/*Writing the detach signal to S11 Queue*/
	if ((g_Q_tauRsp_fd  = open_ipc_channel(S1AP_TAURSP_QUEUE,
						IPC_WRITE)) == -1){
		log_msg(LOG_ERROR, "Error in opening TAU Response writer IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "TAU Response writer started\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(tauReq, 0, S1AP_TAUREQ_BUF_SIZE);
	while (bytes_read < S1AP_TAUREQ_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_tauReq_fd, tauReq,
			S1AP_TAUREQ_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "**************** TAU request Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static void
tau_request_processing()
{
	struct tauReq_Q_msg *tau_req =
			(struct tauReq_Q_msg *) tauReq;
	log_msg(LOG_INFO, "TAU request received for ue %d\n",
			tau_req->ue_idx);
    tau_req_counter++;

	g_tau_rsp_msg.s1ap_enb_ue_id = tau_req->s1ap_enb_ue_id;
	g_tau_rsp_msg.ue_idx = tau_req->ue_idx;

	struct UE_info *ue_entry = GET_UE_ENTRY(tau_req->ue_idx);
    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
	    tau_response_reject_counter++;
        g_tau_rsp_msg.status = 1; /* TODO : Take the value from SPEC */ 
        return; 
    }
	tau_response_accept_counter++;
	ue_entry->ul_seq_no++;
	ue_entry->s1ap_enb_ue_id = tau_req->s1ap_enb_ue_id;
    g_tau_rsp_msg.enb_fd = ue_entry->enb_fd;
    g_tau_rsp_msg.dl_seq_no = tau_req->seq_num;
    memcpy(&(g_tau_rsp_msg.int_key), &(ue_entry->ue_sec_info.int_key),
          NAS_INT_KEY_SIZE);
	memcpy(&(g_tau_rsp_msg.tai), &(ue_entry->tai), sizeof(struct TAI));
	log_msg(LOG_INFO, "TAU response with NAS sequence number %d \n", tau_req->seq_num);

	return ;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	/* Post to s11-app */
	write_ipc_channel(g_Q_tauRsp_fd, (char *)&(g_tau_rsp_msg),
			S1AP_TAURESP_BUF_SIZE);
	log_msg(LOG_INFO, "Posted TAU Response message to s1-app.\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_tau_stage()
{
	close_ipc_channel(g_Q_tauReq_fd);
	close_ipc_channel(g_Q_tauRsp_fd);
	log_msg(LOG_INFO, "Shutdown TAU handling stage\n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
tau_request_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "TAU Request stage Ready to handle messages \n");
	g_mme_hdlr_status |= 1;
	g_mme_hdlr_status <<= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();
		tau_request_processing(); 
		post_to_next();
	}

	return NULL;
}
