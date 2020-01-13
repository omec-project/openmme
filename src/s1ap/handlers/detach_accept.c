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
#include "detach_stage2_info.h"

/****Globals and externs ***/

/*Making global just to avoid stack passing*/
static char buf[S1AP_DTCHACCEPT_STAGE2_BUF_SIZE];

struct detach_accept_Q_msg *g_acptReqInfo;

static Buffer g_acpt_buffer;
static Buffer g_ctxrel_buffer;

extern int g_enb_fd;

extern ipc_handle ipcHndl_detach_accept;

/****Global and externs end***/
/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((ipcHndl_detach_accept  = open_ipc_channel(
			S1AP_DTCHACCEPT_STAGE2_QUEUE, IPC_READ)) == -1) {
		log_msg(LOG_ERROR, "Error in opening reader for Detach "
				"accept IPC channel : %s\n",
				S1AP_DTCHACCEPT_STAGE2_QUEUE);
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "icsreq reader: Connected.\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_DTCHACCEPT_STAGE2_BUF_SIZE);
	while (bytes_read < S1AP_DTCHACCEPT_STAGE2_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
				ipcHndl_detach_accept, buf,
				S1AP_DTCHACCEPT_STAGE2_BUF_SIZE)) == -1) {
					log_msg(LOG_ERROR, "Error in reading \n");
					/* TODO : Add proper error handling */
				}
		log_msg(LOG_INFO, "Init Ctx Setup Message Received, len: %d", bytes_read);
	}

	return bytes_read;
}

/**
* Get ProtocolIE value for detach accept
*/
static int
get_detach_accept_protoie_value(struct proto_IE *value)
{
	uint8_t ieCnt = 0;

	value->no_of_IEs = DTCH_ACCEPT_NO_OF_IES;

	value->data = (proto_IEs *) malloc(DTCH_ACCEPT_NO_OF_IES *
			sizeof(proto_IEs));

	value->data[ieCnt].val.mme_ue_s1ap_id = g_acptReqInfo->ue_idx;
	ieCnt++;

	value->data[ieCnt].val.enb_ue_s1ap_id = g_acptReqInfo->enb_s1ap_ue_id;
	ieCnt++;

	struct nasPDU *nas = &(value->data[ieCnt].val.nas);
	nas->header.security_header_type = IntegrityProtectedCiphered;
	nas->header.proto_discriminator = EPSMobilityManagementMessages;

	/* placeholder for mac. mac value will be calculated later */
	uint8_t mac[MAC_SIZE] = {0};
	memcpy(nas->header.mac, mac, MAC_SIZE);

	nas->header.seq_no = g_acptReqInfo->dl_seq_no;
	nas->header.message_type = DetachAccept;

	ieCnt++;

	return SUCCESS;
}

/**
* Stage specific message processing.
*/
static int
detach_accept_processing()
{
	unsigned char tmpStr[4];
	struct s1ap_PDU s1apPDU;
	uint16_t protocolIe_Id;
	uint8_t protocolIe_criticality = CRITICALITY_REJECT;
	uint8_t initiating_msg = 0;
	uint8_t datalen = 0;
	uint8_t s1ap_len_pos;
	uint8_t nas_len_pos;
	uint8_t u8value = 0;
	uint8_t mac_data_pos;

	g_acptReqInfo = (struct detach_accept_Q_msg *) buf;

	s1apPDU.procedurecode = id_downlinkNASTransport;
	s1apPDU.criticality = CRITICALITY_IGNORE;

	get_detach_accept_protoie_value(&s1apPDU.value);

	g_acpt_buffer.pos = 0;

	buffer_copy(&g_acpt_buffer, &initiating_msg,
			sizeof(initiating_msg));

	buffer_copy(&g_acpt_buffer, &s1apPDU.procedurecode,
			sizeof(s1apPDU.procedurecode));

	buffer_copy(&g_acpt_buffer, &s1apPDU.criticality,
				sizeof(s1apPDU.criticality));

	s1ap_len_pos = g_acpt_buffer.pos;

	/* length of Detach Accept */
	u8value = 0;
	buffer_copy(&g_acpt_buffer, &u8value, sizeof(u8value));

	/* TODO remove hardcoded values */
	uint8_t chProtoIENo[3] = {0,0,3};
	buffer_copy(&g_acpt_buffer, chProtoIENo, 3);

	/* id-MME-UE-S1AP-ID */
	protocolIe_Id = id_MME_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_acpt_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_acpt_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	datalen = 2;
	/* TODO need to add proper handling*/
	unsigned char mme_ue_id[3];
	datalen = copyU16(mme_ue_id, s1apPDU.value.data[0].val.mme_ue_s1ap_id);
	buffer_copy(&g_acpt_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_acpt_buffer, mme_ue_id, datalen);

	/* id-eNB-UE-S1AP-ID */
	protocolIe_Id = id_eNB_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_acpt_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_acpt_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	/* TODO needs proper handling*/
	unsigned char enb_ue_id[3];
	datalen = copyU16(enb_ue_id, s1apPDU.value.data[1].val.enb_ue_s1ap_id);
	buffer_copy(&g_acpt_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_acpt_buffer, enb_ue_id, datalen);

	/* NAS PDU start */
	protocolIe_Id = id_NAS_PDU;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_acpt_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_acpt_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));

	nas_len_pos = g_acpt_buffer.pos;

	datalen = 0;
	buffer_copy(&g_acpt_buffer, &datalen, sizeof(datalen));

	buffer_copy(&g_acpt_buffer, &datalen, sizeof(datalen));

	nas_pdu_header *nas_hdr = &(s1apPDU.value.data[2].val.nas.header);

	/* security header and protocol discriminator */
	u8value = (nas_hdr->security_header_type << 4 |
			nas_hdr->proto_discriminator);
	buffer_copy(&g_acpt_buffer, &u8value, sizeof(u8value));

	/* mac */
	/* placeholder for mac. mac value will be calculated later */
	buffer_copy(&g_acpt_buffer, nas_hdr->mac, MAC_SIZE);
	mac_data_pos = g_acpt_buffer.pos;

	/* sequence number */
	buffer_copy(&g_acpt_buffer, &(nas_hdr->seq_no),
			sizeof(nas_hdr->seq_no));

	/* security header and protocol discriminator */
	nas_hdr->security_header_type = Plain;
	u8value = (nas_hdr->security_header_type << 4 |
			nas_hdr->proto_discriminator);
	buffer_copy(&g_acpt_buffer, &u8value, sizeof(u8value));

	/* message type */
	buffer_copy(&g_acpt_buffer, &(nas_hdr->message_type),
			sizeof(nas_hdr->message_type));

	/* NAS PDU end */

	/* Calculate mac */
	uint8_t direction = 1;
	uint8_t bearer = 0;

	calculate_mac(g_acptReqInfo->int_key, nas_hdr->seq_no,
			direction, bearer, &g_acpt_buffer.buf[mac_data_pos],
			g_acpt_buffer.pos - mac_data_pos,
			&g_acpt_buffer.buf[mac_data_pos - MAC_SIZE]);

	/* Copy nas length to nas length field */
	datalen = g_acpt_buffer.pos - nas_len_pos -1;
	memcpy(&(g_acpt_buffer.buf[nas_len_pos]), &datalen, sizeof(datalen));

	/* Copy nas length to nas length field */
	datalen = g_acpt_buffer.pos - nas_len_pos - 2;
	memcpy(&(g_acpt_buffer.buf[nas_len_pos + 1]), &datalen, sizeof(datalen));

	/* Copy length to s1ap length field */
	datalen = g_acpt_buffer.pos - s1ap_len_pos - 1;
	memcpy(g_acpt_buffer.buf + s1ap_len_pos, &datalen, sizeof(datalen));

	/* TODO: temp fix */
	//g_ics_buffer.buf[1] = 0x09;

	return SUCCESS;
}

/**
* essage processing for ue context release
*/
static int
ue_ctx_release_processing()
{
	unsigned char tmpStr[4];
	struct s1ap_PDU s1apPDU;
	uint16_t protocolIe_Id;
	uint8_t protocolIe_criticality = CRITICALITY_REJECT;
	uint8_t initiating_msg = 0;
	uint8_t datalen = 0;
	uint8_t s1ap_len_pos;
	uint8_t u8value = 0;

	s1apPDU.procedurecode = id_UEContexRelease;
	s1apPDU.criticality = CRITICALITY_IGNORE;

	g_ctxrel_buffer.pos = 0;

	buffer_copy(&g_ctxrel_buffer, &initiating_msg,
			sizeof(initiating_msg));

	buffer_copy(&g_ctxrel_buffer, &s1apPDU.procedurecode,
			sizeof(s1apPDU.procedurecode));

	buffer_copy(&g_ctxrel_buffer, &s1apPDU.criticality,
				sizeof(s1apPDU.criticality));

	s1ap_len_pos = g_ctxrel_buffer.pos;

	/* length of UE Context Release */
	u8value = 0;
	buffer_copy(&g_ctxrel_buffer, &u8value, sizeof(u8value));

	/* TODO remove hardcoded values */
	uint8_t chProtoIENo[3] = {0,0,2};
	buffer_copy(&g_ctxrel_buffer, chProtoIENo, 3);

	/* id-UE-S1AP-IDs */
	protocolIe_Id = id_UE_S1AP_IDs;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ctxrel_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_ctxrel_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));

	uint8_t mme_ue_id[4];
	uint8_t mme_ue_id_len = copyU16(mme_ue_id,
				s1apPDU.value.data[0].val.mme_ue_s1ap_id);

	if (mme_ue_id[0] == 0x40 || mme_ue_id[0] == 0x80)
		mme_ue_id[0] = ((mme_ue_id[0] & 0x0F)<<4 |
				(mme_ue_id[0] & 0xF0)>>4);

	uint8_t enb_ue_id[4];
	uint8_t enb_ue_id_len = copyU16(enb_ue_id,
				s1apPDU.value.data[1].val.enb_ue_s1ap_id);

	datalen = mme_ue_id_len + enb_ue_id_len;
	buffer_copy(&g_ctxrel_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ctxrel_buffer, mme_ue_id, mme_ue_id_len);
	buffer_copy(&g_ctxrel_buffer, enb_ue_id, enb_ue_id_len);

#if 0
	/* id-MME-UE-S1AP-ID */
	protocolIe_Id = id_MME_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ctxrel_buffer, tmpStr,
	                                sizeof(protocolIe_Id));

	protocolIe_criticality = CRITICALITY_REJECT;
	buffer_copy(&g_ctxrel_buffer, &protocolIe_criticality,
	                                sizeof(protocolIe_criticality));

	datalen = 2;

	/* TODO needs proper handling*/
	unsigned char mme_ue_id[4];
	datalen = copyU16(mme_ue_id, s1apPDU.value.data[0].mme_ue_s1ap_id);
	buffer_copy(&g_ctxrel_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ctxrel_buffer, mme_ue_id, datalen);
#endif

	/* id-Cause */
	protocolIe_Id = id_Cause;
	protocolIe_criticality = CRITICALITY_IGNORE;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ctxrel_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_ctxrel_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	datalen = 1;
	buffer_copy(&g_ctxrel_buffer, &datalen, sizeof(datalen));
	/* TODO : Revisit. cause : nas(2) and value : detach (2), why 0x24 ? */
	u8value = 0x24;
	buffer_copy(&g_ctxrel_buffer, &u8value, sizeof(u8value));

	/* Copy length to s1ap length field */
	datalen = g_ctxrel_buffer.pos - s1ap_len_pos - 1;
	memcpy(g_ctxrel_buffer.buf + s1ap_len_pos, &datalen, sizeof(datalen));

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	send_sctp_msg(g_acptReqInfo->enb_fd, g_acpt_buffer.buf, g_acpt_buffer.pos, 1);
	send_sctp_msg(g_acptReqInfo->enb_fd, g_ctxrel_buffer.buf, g_ctxrel_buffer.pos, 1);
	log_msg(LOG_INFO, "buffer size is %d\n", g_acpt_buffer.pos);
	log_msg(LOG_INFO, "\n-----Detach Stage2 completed.---\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_detach_accept_stage()
{
	close_ipc_channel(ipcHndl_detach_accept);
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
detach_accept_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "detach accept handler ready.\n");

	while(1){
		read_next_msg();

		detach_accept_processing();
		ue_ctx_release_processing();

		post_to_next();
	}

	return NULL;
}
