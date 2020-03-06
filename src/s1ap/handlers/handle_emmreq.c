/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "log.h"
#include "err_codes.h"
#include "s1ap.h"
#include "ipc_api.h"
#include "main.h"
#include "stage2_info.h"
#include "message_queues.h"
#include "sctp_conn.h"
#include "s1ap_emm_message.h"

/*Making global just to avoid stack passing*/
static char buf[UE_EMM_INFO_BUF_SIZE];
extern ipc_handle ipcHndl_emm_inforeq;

static struct ue_emm_info *g_ueEmmInfoMsg;
static struct Buffer g_buffer;
static struct Buffer g_s1ap_buffer;
static struct Buffer g_nas_buffer;

/**
* Stage specific message processing.
*/
static int
emm_info_request_processing()
{
	struct s1ap_PDU s1apPDU;
	g_ueEmmInfoMsg = (struct ue_emm_info *) buf;

	/* Assigning values to s1apPDU */
	s1apPDU.procedurecode = id_downlinkNASTransport;
	s1apPDU.criticality = CRITICALITY_IGNORE;

	/* Copy values to buffer from s1apPDU */

	g_buffer.pos = 0;

	uint8_t initiating_message = 0; 
	buffer_copy(&g_buffer, &initiating_message,
			sizeof(initiating_message));

	buffer_copy(&g_buffer, &s1apPDU.procedurecode,
			sizeof(s1apPDU.procedurecode));

	buffer_copy(&g_buffer, &s1apPDU.criticality,
			sizeof(s1apPDU.criticality));

    g_s1ap_buffer.pos = 0; 

	uint8_t chProtoIENo[3] = {0,0,3};
	buffer_copy(&g_s1ap_buffer, chProtoIENo, 3);

	/* id-MME-UE-S1AP-ID */
	unsigned char tmpStr[4];
	uint16_t protocolIe_Id = id_MME_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_s1ap_buffer, tmpStr, sizeof(protocolIe_Id));
	uint8_t protocolIe_criticality = CRITICALITY_REJECT;
	buffer_copy(&g_s1ap_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	uint8_t datalen = 2;
	/* TODO need to add proper handling*/
	unsigned char mme_ue_id[3];
	datalen = copyU16(mme_ue_id, g_ueEmmInfoMsg->mme_s1ap_ue_id);
	buffer_copy(&g_s1ap_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_s1ap_buffer, mme_ue_id, datalen);

	/* id-eNB-UE-S1AP-ID */
	protocolIe_Id = id_eNB_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_s1ap_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_s1ap_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));

	unsigned char enb_ue_id[3];
	datalen = copyU16(enb_ue_id, g_ueEmmInfoMsg->enb_s1ap_ue_id);
	buffer_copy(&g_s1ap_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_s1ap_buffer, enb_ue_id, datalen);

    /* Lets add NAS AVP header */
	protocolIe_Id = id_NAS_PDU;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_s1ap_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_s1ap_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));

    g_nas_buffer.pos = 0; 

    unsigned char nas_sec_hdr[1] = { 0x27}; 
	buffer_copy(&g_nas_buffer, nas_sec_hdr, 1);

	uint8_t mac_data_pos;
    char mac[4] = { 0x00, 0x00, 0x00, 0x00}; 
	buffer_copy(&g_nas_buffer, mac, 4);
	mac_data_pos = g_nas_buffer.pos;

    unsigned char seq_no = g_ueEmmInfoMsg->dl_seq_no;
	buffer_copy(&g_nas_buffer, &seq_no, sizeof(seq_no));
   
    char nas_plain_hdr[2] = { 0x07, 0x61}; 
	buffer_copy(&g_nas_buffer, nas_plain_hdr, 2);

    /* Add encoding to encode any random alphanumeric string. Current value Aether */
    char fullname[9] = {0x43, 0x07, 0x80, 0xc1, 0x32, 0x1d, 0x5d, 0x96, 0x03};
	buffer_copy(&g_nas_buffer, fullname, 9);

    char shortname[9] = {0x45, 0x07, 0x80, 0xc1, 0x32, 0x1d, 0x5f, 0x96, 0x03 };
	buffer_copy(&g_nas_buffer, shortname, 9);

	/* Calculate mac */
	uint8_t direction = 1;
	uint8_t bearer = 0;

	calculate_mac(g_ueEmmInfoMsg->int_key, seq_no, direction,
			bearer, &g_nas_buffer.buf[mac_data_pos],
			g_nas_buffer.pos - mac_data_pos,
			&g_nas_buffer.buf[mac_data_pos - MAC_SIZE]);

    uint8_t naslen = g_nas_buffer.pos+1;
    buffer_copy(&g_s1ap_buffer, &naslen, 1);

    naslen = g_nas_buffer.pos;
    buffer_copy(&g_s1ap_buffer, &naslen, 1);

    /* Now lets add NAS buffer to s1ap buffer */
    buffer_copy(&g_s1ap_buffer, &g_nas_buffer.buf[0], (g_nas_buffer.pos));

    /* adding length of s1ap message before adding s1ap message */
	uint8_t s1applen = g_s1ap_buffer.pos;
	buffer_copy(&g_buffer, &s1applen, sizeof(s1applen));

    buffer_copy(&g_buffer, &g_s1ap_buffer.buf[0], g_s1ap_buffer.pos);
    /* Now s1ap header + s1ap buffer is attached */

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	log_msg(LOG_INFO, "EMM info request send on fd %d . Buffer size %d g_ueEmmInfoMsg = %p Buf %p \n", g_ueEmmInfoMsg->enb_fd, g_buffer.pos,g_ueEmmInfoMsg, buf);
	int res = send_sctp_msg(g_ueEmmInfoMsg->enb_fd, g_buffer.buf, g_buffer.pos, 1);
	log_msg(LOG_INFO, "EMM info request sctp send return %d \n", res);
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_s1ap_emm_inforeq_pipe()
{
	close_ipc_channel(ipcHndl_emm_inforeq);
	pthread_exit(NULL);
	return;
}

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((ipcHndl_emm_inforeq  = open_ipc_channel(
				EMM_INFOREQ_QUEUE, IPC_READ)) == -1) {
		log_msg(LOG_ERROR, "Error in opening reader for emm info request queue IPC"
				"channel : %s\n", EMM_INFOREQ_QUEUE);
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "EMM info request queue reader: Connected.\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, UE_EMM_INFO_BUF_SIZE);
	while (bytes_read < UE_EMM_INFO_BUF_SIZE) {
		log_msg(LOG_INFO, "S1ap - waiting for EMM message read bytes %d \n",bytes_read);
		if ((bytes_read = read_ipc_channel(
				ipcHndl_emm_inforeq, buf,
				UE_EMM_INFO_BUF_SIZE)) == -1) {
					log_msg(LOG_ERROR, "Error reading EMM information request Q \n");
					/* TODO : Add proper error handling */
				}
		log_msg(LOG_INFO, "S1ap - Sending EMM information message \n");
	}
	log_msg(LOG_INFO, "S1ap - Sending EMM information message return %d \n",bytes_read);
	return bytes_read;
}


/**
* Thread function for stage.
*/
void*
emm_info_req_handler(void *data)
{
	init_stage();

	g_ueEmmInfoMsg = (struct ue_emm_info *) buf;
	while(1){
		read_next_msg();
	   log_msg(LOG_INFO, "fd = %u , enb-id %u mmeid %u EMM \n",g_ueEmmInfoMsg->enb_fd, g_ueEmmInfoMsg->enb_s1ap_ue_id, g_ueEmmInfoMsg->mme_s1ap_ue_id);
     

		emm_info_request_processing();

		post_to_next();
	}

	return NULL;
}
