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

#include "log.h"
#include "mme_app.h"
#include "ue_table.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage4_info.h"
#include "stage5_s11_info.h"
#include "stage6_info.h"
#include "common_proc_info.h"

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
extern int g_Q_s1ap_common_reject;
extern pthread_mutex_t s1ap_reject_queue_mutex;
static int g_Q_s1ap_service_reject;

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

	log_msg(LOG_INFO, "MME to S1AP write IPC Connected\n");
	/*Open destination queue for writing. It is AIR, ULR Q in this stage*/
	log_msg(LOG_INFO, "Stage 4 writer  - s1ap ESM info req: waiting\n");
	g_Q_esmreq_fd = open_ipc_channel(S1AP_ESMREQ_STAGE4_QUEUE, IPC_WRITE);
	if (g_Q_esmreq_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S1ap-ESM info req\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 4 writer - s1ap ESM info request: Connected\n");
	g_Q_s1ap_service_reject = open_ipc_channel(S1AP_REQ_REJECT_QUEUE, IPC_WRITE);
	if (g_Q_s1ap_service_reject == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: S1AP Reject Queue \n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "S1AP reject Pipe : Connected\n");
 
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg(char *buf)
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
stage4_processing(char *buf)
{
	/*Parse and validate  the buffer*/
	struct secmode_resp_Q_msg *secmode_resp = (struct secmode_resp_Q_msg*)buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(secmode_resp->ue_idx);

    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
        log_msg(LOG_INFO, "stage4_processing skipped for invalid UE index %d \n", secmode_resp->ue_idx);
        return E_FAIL;
    }

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
        ue_entry->ue_state = STAGE4_FAIL;
		//Do something ue_entry->ue_state = STAGE4_WAITING;
	}

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next(char *buf)
{
	struct esm_req_Q_msg esm_req;
	struct secmode_resp_Q_msg *secmode_resp = (struct secmode_resp_Q_msg*)buf;
	struct UE_info *ue_entry =  GET_UE_ENTRY(secmode_resp->ue_idx);
    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
    {
        log_msg(LOG_ERROR, "post_to_next on invalid UE index %d ", secmode_resp->ue_idx);
        return E_FAIL;
    }
    log_msg(LOG_INFO, "Stiching stage 1 to stage 4 - 1 \n");

    if(SERVICE_REQ_PROC == ue_entry->ue_curr_proc)
    {
        if(STAGE4_FAIL == ue_entry->ue_state)
        {
            log_msg(LOG_DEBUG, "Sec mode cmd failed in service req proc. \
                                    Send service reject and clear context");
            post_svc_reject(secmode_resp->ue_idx);
            post_ctx_rel_and_clr_uectx(secmode_resp->ue_idx);
			return SUCCESS;
        }
        log_msg(LOG_DEBUG, "Security Done after Service Request. \
                                  Send Initial Ctx setup request");
		ue_entry->ue_curr_proc =  UNKNOWN_PROC;
        return send_init_ctx_setup_req(secmode_resp->ue_idx);
    }
    else if ((ATTACH_PROC == ue_entry->ue_curr_proc)
             &&(STAGE4_FAIL == ue_entry->ue_state))
    {
        char imsiStr[16] = {0};
        imsi_bin_to_str(ue_entry->IMSI, imsiStr);
        log_msg(LOG_DEBUG, "Sec mode cmd failed in attach req proc. \
                           Send attach reject and clear context. UE IMSI: %s", 
                           imsiStr);
	    struct s1ap_common_req_Q_msg s1ap_rej = {0};
        s1ap_rej.IE_type = S1AP_ATTACH_REJ;
        s1ap_rej.ue_idx = secmode_resp->ue_idx;
        s1ap_rej.mme_s1ap_ue_id = secmode_resp->ue_idx;
        s1ap_rej.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
        s1ap_rej.enb_fd = ue_entry->enb_fd;
        s1ap_rej.cause.present = s1apCause_PR_misc;
        s1ap_rej.cause.choice.misc = s1apCauseMisc_unknown_PLMN;
		
        pthread_mutex_lock(&s1ap_reject_queue_mutex);
        write_ipc_channel(g_Q_s1ap_common_reject, 
                          (char *)&(s1ap_rej),
				          S1AP_COMMON_REQ_BUF_SIZE);
        pthread_mutex_unlock(&s1ap_reject_queue_mutex);
        post_ctx_rel_and_clr_uectx(secmode_resp->ue_idx);
		ue_entry->ue_curr_proc =  UNKNOWN_PROC;
		return SUCCESS;
    }

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
		struct CS_Q_msg cs_msg = {0} ;

		cs_msg.ue_idx = secmode_resp->ue_idx;
		memcpy(cs_msg.IMSI, ue_entry->IMSI, BINARY_IMSI_LEN);

		// Always use the apn name in hss db for create session request for
		// default bearer.
		memcpy(&(cs_msg.selected_apn), &(ue_entry->selected_apn),
			sizeof(struct apn_name));

		memcpy(&(cs_msg.tai), &(ue_entry->tai),
			sizeof(struct TAI));

		memcpy(&(cs_msg.utran_cgi), &(ue_entry->utran_cgi),
			sizeof(struct CGI));

		cs_msg.max_requested_bw_dl = ue_entry->ambr.max_requested_bw_dl;
		cs_msg.max_requested_bw_ul = ue_entry->ambr.max_requested_bw_ul;
		cs_msg.paa_v4_addr = ue_entry->pdn_addr.ip_type.ipv4.s_addr; /* host order */
		log_msg(LOG_INFO, "Posted Create Session message with PAA %x ", cs_msg.paa_v4_addr);

		memset(cs_msg.MSISDN, 0, 10);
		memcpy(cs_msg.MSISDN,ue_entry->MSISDN,10);
        memcpy(&cs_msg.pco_options[0], &ue_entry->pco_options[0], sizeof(ue_entry->pco_options));
        cs_msg.pco_length = ue_entry->pco_length; 

		log_msg(LOG_INFO, "PCO length %d \n", cs_msg.pco_length);
		write_ipc_channel(g_Q_CSreq_fd, (char *)&(cs_msg),
				S11_CSREQ_STAGE5_BUF_SIZE);

		log_msg(LOG_INFO, "Posted Create Session message to S11-app - stage 5");
		attach_stage5_counter++;
	}
	return SUCCESS;
}

int send_init_ctx_setup_req(int ue_index)
{
    log_msg(LOG_DEBUG,"create and send Init ctx setup request");
    struct s1ap_common_req_Q_msg icr_msg;

	struct UE_info *ue_entry =  GET_UE_ENTRY(ue_index);

    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
	{
		log_msg(LOG_INFO, "Failed to retrieve UE context for idx %d\n",
					      ue_index);
		return -1;
	}

	log_msg(LOG_INFO, "Post for s1ap processing - service_req_wf_initctxt_resp.\n");

	/* create KeNB key */
	/* TODO: Generate nas_count from ul_seq_no */
	uint32_t nas_count = 0;
	create_kenb_key(ue_entry->aia_sec_info->kasme.val, ue_entry->ue_sec_info.kenb_key, nas_count);
	icr_msg.IE_type = S1AP_INIT_CTXT_SETUP_REQ;
	icr_msg.ue_idx = ue_index;
	icr_msg.enb_fd = ue_entry->enb_fd;
	icr_msg.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
	icr_msg.mme_s1ap_ue_id = ue_index;
	icr_msg.ueag_max_dl_bitrate = ue_entry->ambr.max_requested_bw_dl;
	icr_msg.ueag_max_ul_bitrate = ue_entry->ambr.max_requested_bw_ul;
	icr_msg.bearer_id = ue_entry->bearer_id;
	memcpy(&(icr_msg.gtp_teid), &(ue_entry->s1u_sgw_u_fteid), sizeof(struct fteid));
	memcpy(&(icr_msg.sec_key), &(ue_entry->ue_sec_info.kenb_key), KENB_SIZE);
	ue_entry->ue_state = SVC_REQ_WF_INIT_CTXT_RESP;

	//opened for write by s1 rel thread
    pthread_mutex_lock(&s1ap_reject_queue_mutex);
	write_ipc_channel(g_Q_s1ap_common_reject, (char *)&(icr_msg), S1AP_COMMON_REQ_BUF_SIZE);
    pthread_mutex_unlock(&s1ap_reject_queue_mutex);

	log_msg(LOG_INFO, "Post for service_req_wf_initctxt_resp processing. SUCCESS\n");
    return SUCCESS;
}

/*
* Post message to s1ap handler about the failure of this stage 
*/
int
post_svc_reject(int ue_index)
{
	struct UE_info *ue_entry =  GET_UE_ENTRY(ue_index);
    struct s1ap_common_req_Q_msg s1ap_rej = {0};
    
    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
	{
		log_msg(LOG_INFO, "Failed to retrieve UE context for idx %d\n",
					      ue_index);
		return -1;
	}
    
    log_msg(LOG_INFO, "Sending Service Rej after Sec mod failure\n");
    s1ap_rej.IE_type = S1AP_SERVICE_REJ;
    s1ap_rej.ue_idx = ue_index;
    s1ap_rej.mme_s1ap_ue_id = ue_index;
    s1ap_rej.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
    s1ap_rej.enb_fd = ue_entry->enb_fd;
    s1ap_rej.emm_cause = emmCause_ue_id_not_derived_by_network;

    pthread_mutex_lock(&s1ap_reject_queue_mutex);
    write_ipc_channel(g_Q_s1ap_common_reject, 
                      (char *)&(s1ap_rej),
                      S1AP_COMMON_REQ_BUF_SIZE);
    pthread_mutex_unlock(&s1ap_reject_queue_mutex);
    return SUCCESS;
}

int
post_ctx_rel_and_clr_uectx(int ue_index)
{
	struct s1ap_common_req_Q_msg ctx_rel = {0};
	log_msg(LOG_INFO, "Sending ctx release \n");
	struct UE_info *ue_entry =  GET_UE_ENTRY(ue_index);

    if((ue_entry == NULL) || (!IS_VALID_UE_INFO(ue_entry)))
	{
		log_msg(LOG_INFO, "Failed to retrieve UE context for idx %d\n",
					      ue_index);
		return -1;
    }
    
    ctx_rel.IE_type = S1AP_CTX_REL_CMD;
    ctx_rel.enb_fd = ue_entry->enb_fd;
    ctx_rel.mme_s1ap_ue_id = ue_index;
    ctx_rel.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
    ctx_rel.cause.present = s1apCause_PR_nas;
    ctx_rel.cause.choice.nas = s1apCauseNas_normal_release; 
    pthread_mutex_lock(&s1ap_reject_queue_mutex);
    write_ipc_channel(g_Q_s1ap_common_reject, (char *)(&ctx_rel), 
                      S1AP_COMMON_REQ_BUF_SIZE );
    
    pthread_mutex_unlock(&s1ap_reject_queue_mutex);
    release_ue_entry(ue_entry); 
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
	close_ipc_channel(g_Q_s1ap_service_reject);
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
        static char buf[S1AP_SECRESP_STAGE4_BUF_SIZE];
	init_stage();
	log_msg(LOG_INFO, "Stage 4 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg(buf);

		stage4_processing(buf);

		post_to_next(buf);
	}

	return NULL;
}

/* Initial Attach Stage1 might want to jump to stage 5 if GUTI attach... 
 */
void 
guti_attach_post_to_next(int ue_index )
{
  static char buf[S1AP_SECRESP_STAGE4_BUF_SIZE];
  memset(buf, 0, S1AP_SECRESP_STAGE4_BUF_SIZE);
  struct secmode_resp_Q_msg *secmode_resp = (struct secmode_resp_Q_msg*)(&buf[0]);
  secmode_resp->ue_idx = ue_index;
  secmode_resp->status =  SUCCESS;
  log_msg(LOG_INFO, "Stiching stage 1 to stage 4 \n");
  post_to_next(buf);
  return;
}

