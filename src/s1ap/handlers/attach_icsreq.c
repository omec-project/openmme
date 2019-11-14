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
#include "s1ap_config.h"
#include "main.h"
#include "s1ap.h"
#include "stage6_info.h"

/*Making global just to avoid stack passing*/
static char buf[S1AP_ICSREQ_STAGE6_BUF_SIZE];

struct init_ctx_req_Q_msg *g_icsReqInfo;

static Buffer g_ics_buffer;

extern int g_enb_fd;

extern ipc_handle ipcHndl_ics;
extern s1ap_config g_s1ap_cfg;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((ipcHndl_ics  = open_ipc_channel(
			S1AP_ICSREQ_STAGE6_QUEUE, IPC_READ)) == -1) {
		log_msg(LOG_ERROR, "Error in opening reader for authreq IPC"
				"channel : %s\n", S1AP_ICSREQ_STAGE6_QUEUE);
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

	memset(buf, 0, S1AP_ICSREQ_STAGE6_BUF_SIZE);
	while (bytes_read < S1AP_ICSREQ_STAGE6_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
				ipcHndl_ics, buf,
				S1AP_ICSREQ_STAGE6_BUF_SIZE)) == -1) {
					log_msg(LOG_ERROR, "Error in reading \n");
					/* TODO : Add proper error handling */
				}
		log_msg(LOG_INFO, "Init Ctx Setup Message Received, len: %d\n", bytes_read);
	}

	return bytes_read;
}

static void
get_negotiated_qos_value(struct esm_qos *qos)
{
	qos->delay_class = 1;
	qos->reliability_class = 3;
	qos->peak_throughput = 5;
	qos->precedence_class = 2;
	qos->mean_throughput = 31;
	qos->traffic_class = 3;
	qos->delivery_order = 2;
	qos->delivery_err_sdu = 3;
	qos->max_sdu_size = 140;
	qos->mbr_ul = 254;
	qos->mbr_dl = 86;
	qos->residual_ber = 7;
	qos->sdu_err_ratio = 6;
	qos->transfer_delay = 18;
	qos->trffic_prio = 3;
	qos->gbr_ul = 86;
	qos->gbr_dl = 86;
	qos->sig_ind = 0;
	qos->src_stat_desc = 0;
	qos->mbr_dl_ext = 108;
	qos->gbr_dl_ext = 0;
	qos->mbr_ul_ext = 108;
	qos->gbr_ul_ext = 0;

	return;
}

/**
* Get ProtocolIE value for ICS Request sent by mme-app
*/
static int
get_icsreq_protoie_value(struct proto_IE *value)
{
	uint8_t ieCnt = 0;
	uint8_t nasIeCnt = 0;

	value->no_of_IEs = ICS_REQ_NO_OF_IES;

	value->data = (proto_IEs *) malloc(ICS_REQ_NO_OF_IES *
			sizeof(proto_IEs));

	value->data[ieCnt].val.mme_ue_s1ap_id = g_icsReqInfo->ue_idx;
	ieCnt++;

	value->data[ieCnt].val.enb_ue_s1ap_id = g_icsReqInfo->enb_s1ap_ue_id;
	ieCnt++;

	value->data[ieCnt].val.ue_aggrt_max_bit_rate.uEaggregateMaxBitRateDL =
			g_icsReqInfo->exg_max_dl_bitrate;
	value->data[ieCnt].val.ue_aggrt_max_bit_rate.uEaggregateMaxBitRateUL =
				g_icsReqInfo->exg_max_ul_bitrate;
	ieCnt++;

	/* E-RABToBeSetupItemCtxtSUReq start */
	ERABSetup *e_rab = &(value->data[ieCnt].val.E_RABToBeSetupItemCtxtSUReq);
	/* TODO: Remove hardcoded values. */
	e_rab->e_RAB_ID = 1;
	e_rab->e_RAB_QoS_Params.qci = 9;
	e_rab->e_RAB_QoS_Params.arPrio.prioLevel = 15;
	e_rab->e_RAB_QoS_Params.arPrio.preEmptionCapab = 1;
	e_rab->e_RAB_QoS_Params.arPrio.preEmptionVulnebility = 1;

	/*S1u information : transport layer addr and teid*/
	e_rab->transportLayerAddress = htonl(g_icsReqInfo->gtp_teid.ip.ipv4.s_addr);
	//e_rab->gtp_teid = htonl(g_icsReqInfo->gtp_teid.header.teid_gre);
	{
		char *dst = (char *)&(e_rab->gtp_teid);
		char *src = (char *)&(g_icsReqInfo->gtp_teid.header.teid_gre);
		memcpy(dst, src+3, 1);
		memcpy(dst+1, src+2, 1);
		memcpy(dst+2, src+1, 1);
		memcpy(dst+3, src, 1);
	}

	/* NAS PDU values start */
	e_rab->nas.header.security_header_type =
				IntegrityProtectedCiphered;
	e_rab->nas.header.proto_discriminator =
			EPSMobilityManagementMessages;

	/* placeholder for mac. mac value will be calculated later */
	uint8_t mac[MAC_SIZE] = {0};
	memcpy(e_rab->nas.header.mac, mac, MAC_SIZE);

	e_rab->nas.header.seq_no = g_icsReqInfo->dl_seq_no;
	e_rab->nas.header.message_type = AttachAccept;
	/* TODO: Remove hardcoded value */
	e_rab->nas.header.eps_bearer_identity = 0;
	e_rab->nas.header.procedure_trans_identity = 1;

	e_rab->nas.elements_len = ICS_REQ_NO_OF_NAS_IES;
	e_rab->nas.elements = (nas_pdu_elements *)
			malloc(ICS_REQ_NO_OF_NAS_IES * sizeof(nas_pdu_elements));

	nas_pdu_elements *nasIEs = e_rab->nas.elements;
	nasIEs[nasIeCnt].attach_res = 1; /* EPS Only */
	nasIeCnt++;

	nasIEs[nasIeCnt].t3412 = 16;
	nasIeCnt++;

	nasIEs[nasIeCnt].tailist.type = 1;
	nasIEs[nasIeCnt].tailist.num_of_elements = 0;
	memcpy(&(nasIEs[nasIeCnt].tailist.partial_list[0]),
			&(g_icsReqInfo->tai), sizeof(g_icsReqInfo->tai));
	nasIeCnt++;

	nasIEs[nasIeCnt].esm_msg.eps_bearer_id = 5; /* TODO: revisit */
	nasIEs[nasIeCnt].esm_msg.proto_discriminator = 2;
	memcpy(&(nasIEs[nasIeCnt].esm_msg.procedure_trans_identity), &(g_icsReqInfo->pti), 1);
	nasIEs[nasIeCnt].esm_msg.session_management_msgs =
			ESM_MSG_ACTV_DEF_BEAR__CTX_REQ;
	nasIEs[nasIeCnt].esm_msg.eps_qos = 9;

	/* TODO: Remove hardcoded value */
	/*char apnname[4] = "apn1";
	memcpy(&(nasIEs[nasIeCnt].esm_msg.apn.val), apnname, 4);
	nasIEs[nasIeCnt].esm_msg.apn.len =  4;
	*/
	nasIEs[nasIeCnt].esm_msg.apn.len = g_icsReqInfo->apn.len;
	memcpy(nasIEs[nasIeCnt].esm_msg.apn.val,
			g_icsReqInfo->apn.val, g_icsReqInfo->apn.len);


	nasIEs[nasIeCnt].esm_msg.pdn_addr.type = 1;
	nasIEs[nasIeCnt].esm_msg.pdn_addr.ipv4 =
			g_icsReqInfo->pdn_addr.ip_type.ipv4.s_addr;
	nasIEs[nasIeCnt].esm_msg.linked_ti.flag = 0;
	nasIEs[nasIeCnt].esm_msg.linked_ti.val = 0;
	get_negotiated_qos_value(&nasIEs[nasIeCnt].esm_msg.negotiated_qos);
	nasIeCnt++;

	nasIEs[nasIeCnt].mi_guti.odd_even_indication = 0;
	nasIEs[nasIeCnt].mi_guti.id_type = 6;
	memcpy(&(nasIEs[nasIeCnt].mi_guti.plmn_id),
			&(g_icsReqInfo->tai.plmn_id), sizeof(struct PLMN));
	nasIEs[nasIeCnt].mi_guti.mme_grp_id = htons(g_s1ap_cfg.mme_group_id);
	nasIEs[nasIeCnt].mi_guti.mme_code = g_s1ap_cfg.mme_code;
	/* TODO : Revisit, temp fix for handling detach request retransmit.
	 * M-TMSI should come from MME */
	nasIEs[nasIeCnt].mi_guti.m_TMSI = htonl(g_icsReqInfo->ue_idx);
	nasIeCnt++;

	ieCnt++;
	/* NAS PDU values end */
	/* E-RABToBeSetupItemCtxtSUReq values end */


	/* TODO Get value of ue_sec_capabilities
	 *
	 * value->data[ieCnt].ue_sec_capabilities = ??
	 *
	 * */


	ieCnt++;

	/* TODO: remove hard coded value */
	/*char sec_key[32] = "abcdefghijklmnopqrstuvwxyz012345";
	memcpy(value->data[ieCnt].sec_key, sec_key,
			SECURITY_KEY_SIZE);
	*/

	memcpy(value->data[ieCnt].val.sec_key, g_icsReqInfo->sec_key,
			SECURITY_KEY_SIZE);

	ieCnt++;

	return SUCCESS;
}



/**
* Stage specific message processing.
*/
static int
icsreq_processing()
{
	unsigned char tmpStr[4];
	struct s1ap_PDU s1apPDU;
	uint16_t protocolIe_Id;
	uint8_t protocolIe_criticality;
	uint8_t initiating_msg = 0;
	uint8_t datalen = 0;
	uint8_t s1ap_len_pos;
	uint8_t erab_len_pos;
	uint8_t erab_item_len_pos;
	uint8_t nas_len_pos;
	uint16_t esm_len_pos;
	uint8_t u8value = 0;
	uint8_t mac_data_pos;

	g_icsReqInfo = (struct init_ctx_req_Q_msg *) buf;

	s1apPDU.procedurecode = id_InitialContextSetup;
	s1apPDU.criticality = CRITICALITY_REJECT;

	get_icsreq_protoie_value(&s1apPDU.value);

	g_ics_buffer.pos = 0;

	buffer_copy(&g_ics_buffer, &initiating_msg,
			sizeof(initiating_msg));

	buffer_copy(&g_ics_buffer, &s1apPDU.procedurecode,
			sizeof(s1apPDU.procedurecode));

	buffer_copy(&g_ics_buffer, &s1apPDU.criticality,
				sizeof(s1apPDU.criticality));

	/* TODO: revisit , why 128 (0x80) required */
	u8value = 128;
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));

	s1ap_len_pos = g_ics_buffer.pos;

	/* length of InitialContextSetup */
	u8value = 0;
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));

	/* TODO remove hardcoded values */
	uint8_t chProtoIENo[3] = {0,0,6};
	buffer_copy(&g_ics_buffer, chProtoIENo, 3);

	/* id-MME-UE-S1AP-ID */
	protocolIe_Id = id_MME_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ics_buffer, tmpStr, sizeof(protocolIe_Id));
	protocolIe_criticality = CRITICALITY_REJECT;
	buffer_copy(&g_ics_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	datalen = 2;
	/* TODO need to add proper handling*/
	unsigned char mme_ue_id[3];
	datalen = copyU16(mme_ue_id, s1apPDU.value.data[0].val.mme_ue_s1ap_id);
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, mme_ue_id, datalen);

	/* id-eNB-UE-S1AP-ID */
	protocolIe_Id = id_eNB_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ics_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_ics_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	/* TODO needs proper handling*/
	unsigned char enb_ue_id[3];
	datalen = copyU16(enb_ue_id, s1apPDU.value.data[1].val.enb_ue_s1ap_id);
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, enb_ue_id, datalen);

	protocolIe_Id = id_uEaggregatedMaximumBitrate;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ics_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_ics_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	datalen = 10;

	uint8_t maximum_bit_rate_dl = 0x18;
	uint8_t maximum_bit_rate_ul = 0x60;

	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));

	buffer_copy(&g_ics_buffer, &maximum_bit_rate_dl, sizeof(maximum_bit_rate_dl));

	uint32_t temp_bitrate = htonl(g_icsReqInfo->exg_max_dl_bitrate);
	memset(tmpStr, 0, sizeof(tmpStr));
	memcpy(tmpStr, &temp_bitrate, sizeof(temp_bitrate));

	buffer_copy(&g_ics_buffer, tmpStr,
			sizeof(tmpStr));

	temp_bitrate = 0;
	temp_bitrate = htonl(g_icsReqInfo->exg_max_ul_bitrate);
	memset(tmpStr, 0, sizeof(tmpStr));
	memcpy(tmpStr, &temp_bitrate, sizeof(temp_bitrate));

	buffer_copy(&g_ics_buffer, &maximum_bit_rate_ul,
			sizeof(maximum_bit_rate_ul));
	buffer_copy(&g_ics_buffer, tmpStr,
			sizeof(tmpStr));


	/* id-E-RABToBeSetupListCtxtSUReq */
	ERABSetup *erab = &(s1apPDU.value.data[3].val.E_RABToBeSetupItemCtxtSUReq);
	protocolIe_Id = id_ERABToBeSetupListCtxtSUReq;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ics_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_ics_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	erab_len_pos = g_ics_buffer.pos;
	datalen = 0;
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));

	/*TODO: Revisit why it requires 0 before item1 */
	buffer_copy(&g_ics_buffer, &initiating_msg,
			sizeof(initiating_msg));

	protocolIe_Id = id_ERABToBeSetupItemCtxtSUReq;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ics_buffer, tmpStr, sizeof(protocolIe_Id));
	buffer_copy(&g_ics_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	erab_item_len_pos = g_ics_buffer.pos;
	datalen = 0;
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));

	/*
	buffer_copy(&g_ics_buffer, &(erab->e_RAB_ID),
			sizeof(erab->e_RAB_ID));
	*/
	/* TODO : Remove hardcoded value of erab id */
	u8value =69; // 0x45 //1;
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	/* TODO: Need to revisit why add 00 before qci value? */
	u8value = 0;
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	buffer_copy(&g_ics_buffer, &(erab->e_RAB_QoS_Params.qci),
			sizeof(erab->e_RAB_QoS_Params.qci));
	buffer_copy(&g_ics_buffer, &(erab->e_RAB_QoS_Params.arPrio),
			sizeof(erab->e_RAB_QoS_Params.arPrio));

	/* TODO: Revisit why we need to add 0f 80 before transport add? */

	u8value = 15;
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	u8value = 128;
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));

	buffer_copy(&g_ics_buffer, &(erab->transportLayerAddress),
				sizeof(erab->transportLayerAddress));

	buffer_copy(&g_ics_buffer, &(erab->gtp_teid),
				sizeof(erab->gtp_teid));


	/* E_RABToBeSetupListCtxtSUReq NAS PDU start */
	nas_len_pos = g_ics_buffer.pos;

	datalen = 0;
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));

	nas_pdu_header *nas_hdr = &(erab->nas.header);

	/* security header and protocol discriminator */
	u8value = (nas_hdr->security_header_type << 4 |
			nas_hdr->proto_discriminator);
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));

	/* mac */
	/* placeholder for mac. mac value will be calculated later */
	buffer_copy(&g_ics_buffer, nas_hdr->mac, MAC_SIZE);
	mac_data_pos = g_ics_buffer.pos;

	/* sequence number */
	buffer_copy(&g_ics_buffer, &(nas_hdr->seq_no),
			sizeof(nas_hdr->seq_no));

	/* security header and protocol discriminator */
	nas_hdr->security_header_type = Plain;
	u8value = (nas_hdr->security_header_type << 4 |
			nas_hdr->proto_discriminator);
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));

	/* message type */
	buffer_copy(&g_ics_buffer, &(nas_hdr->message_type),
			sizeof(nas_hdr->message_type));

	nas_pdu_elements *ies = erab->nas.elements;

	/* eps attach result */
	buffer_copy(&g_ics_buffer, &(ies[0].attach_res), sizeof(u8value));

	/* GPRS timer */
	buffer_copy(&g_ics_buffer, &(ies[1].t3412), sizeof(ies[1].t3412));

	/* TAI list */
	u8value = 6;
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	u8value = 32; /* TODO: use value from tai list */
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	buffer_copy(&g_ics_buffer, &(ies[2].tailist.partial_list[0].plmn_id.idx), 3);
	buffer_copy(&g_ics_buffer, &(ies[2].tailist.partial_list[0].tac), 2);

	esm_len_pos = g_ics_buffer.pos;

	/* esm message container length */
	char tmplen[2] = {0, 0};
	buffer_copy(&g_ics_buffer, tmplen, 2);

	/* ESM message container start */

	/* esm message bearer id and protocol discriminator */
	u8value = (ies[3].esm_msg.eps_bearer_id << 4 |
			ies[3].esm_msg.proto_discriminator);
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));

	/* esm message procedure identity */
	buffer_copy(&g_ics_buffer, &(ies[3].esm_msg.procedure_trans_identity),
			sizeof(ies[3].esm_msg.procedure_trans_identity));

	/* esm message session management message */
	buffer_copy(&g_ics_buffer, &(ies[3].esm_msg.session_management_msgs),
			sizeof(ies[3].esm_msg.session_management_msgs));

	/* eps qos */
	datalen = 1;
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, &(ies[3].esm_msg.eps_qos),
			sizeof(ies[3].esm_msg.eps_qos));

	/* apn */
	char apn_name[25]={};
	strncpy(apn_name, (char *)ies[3].esm_msg.apn.val, ies[3].esm_msg.apn.len);
	datalen = ies[3].esm_msg.apn.len;
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, (char *)ies[3].esm_msg.apn.val, datalen);
	
	/* pdn address */
	//datalen = sizeof(ies[3].esm_msg.pdn_addr);
	datalen = 5; //sizeof(ies[3].esm_msg.pdn_addr);
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	u8value = 1;
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	//buffer_copy(&g_ics_buffer, &(ies[3].esm_msg.pdn_addr.pdn_type), 1);
	buffer_copy(&g_ics_buffer, &(ies[3].esm_msg.pdn_addr.ipv4), datalen-1);

	/* linked ti */
	u8value = 0x5d; /* element id TODO: define macro or enum */
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	datalen = 1;//sizeof(ies[3].esm_msg.linked_ti);
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, &(ies[3].esm_msg.linked_ti), datalen);

	/* negotiated qos */
	u8value = 0x30; /* element id TODO: define macro or enum */
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	datalen = 16;//sizeof(ies[3].esm_msg.negotiated_qos);
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, &(ies[3].esm_msg.negotiated_qos), datalen);

	/* apn ambr */
#if 0
	u8value = 0x5e; /* element id TODO: define macro or enum */
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	datalen = sizeof(ies[3].esm_msg.apn_ambr);
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, &(ies[3].esm_msg.apn_ambr), datalen);
#endif
	/* TODO: remove hardcoded values of apn ambr */
	char apn_ambr[8] = {0x5e, 0x06, 0x80, 0x00, 0x04, 0x05, 0x06, 0x07};
	buffer_copy(&g_ics_buffer, apn_ambr, 8);

	/* ESM message container end */

	/* Copy esm container length to esm container length field */
	uint16_t esm_datalen = g_ics_buffer.pos - esm_len_pos - 2;
	unsigned char esm_len[2];
	copyU16(esm_len, esm_datalen);
	/* memcpy(&g_ics_buffer.buf[esm_len_pos], tmplen, sizeof(esm_datalen)); */
	/*TODO: needs proper handling */
	g_ics_buffer.buf[esm_len_pos] = esm_len[0];
	g_ics_buffer.buf[esm_len_pos + 1] = esm_len[1];

	/* EPS mobile identity GUTI */
#if 0
	u8value = 0x50; /* element id TODO: define macro or enum */
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	datalen = sizeof(ies[4].mi_guti);
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, &(ies[4].mi_guti), datalen);
#endif

	u8value = 0x50; /* element id TODO: define macro or enum */
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	datalen = 11;
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	u8value = 246; /* TODO: remove hard coding */
	buffer_copy(&g_ics_buffer, &u8value, sizeof(u8value));
	buffer_copy(&g_ics_buffer, &(ies[4].mi_guti.plmn_id.idx), 3);
	buffer_copy(&g_ics_buffer, &(ies[4].mi_guti.mme_grp_id),
			sizeof(ies[4].mi_guti.mme_grp_id));
	buffer_copy(&g_ics_buffer, &(ies[4].mi_guti.mme_code),
			sizeof(ies[4].mi_guti.mme_code));
	buffer_copy(&g_ics_buffer, &(ies[4].mi_guti.m_TMSI),
			sizeof(ies[4].mi_guti.m_TMSI));

	/* E_RABToBeSetupListCtxtSUReq NAS PDU end */

	/* Calculate mac */
	uint8_t direction = 1;
	uint8_t bearer = 0;

	calculate_mac(g_icsReqInfo->int_key, nas_hdr->seq_no,
			direction, bearer, &g_ics_buffer.buf[mac_data_pos],
			g_ics_buffer.pos - mac_data_pos,
			&g_ics_buffer.buf[mac_data_pos - MAC_SIZE]);

	/* Copy nas length to nas length field */
	datalen = g_ics_buffer.pos - nas_len_pos - 1;
	memcpy(&(g_ics_buffer.buf[nas_len_pos]), &datalen, sizeof(datalen));

	/* Copy erab item length to erab item length field */
	datalen = g_ics_buffer.pos - erab_item_len_pos - 1;
	memcpy(&(g_ics_buffer.buf[erab_item_len_pos]), &datalen, sizeof(datalen));

	/* Copy erab length to erab length field */
	datalen = g_ics_buffer.pos - erab_len_pos -1;
	memcpy(&(g_ics_buffer.buf[erab_len_pos]), &datalen, sizeof(datalen));

	/* id-UESecurityCapabilities */
	char ue_sec_capab[5] = {0x1c, 0x00, 0x0c, 0x00, 0x00};
	protocolIe_Id = id_UESecurityCapabilities;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ics_buffer, tmpStr, sizeof(protocolIe_Id));
	protocolIe_criticality = CRITICALITY_REJECT;
	buffer_copy(&g_ics_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	datalen = 5;
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, ue_sec_capab, 5);

	protocolIe_Id = id_SecurityKey;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_ics_buffer, tmpStr, sizeof(protocolIe_Id));
	protocolIe_criticality = CRITICALITY_REJECT;
	buffer_copy(&g_ics_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));
	datalen = SECURITY_KEY_SIZE;
	buffer_copy(&g_ics_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_ics_buffer, s1apPDU.value.data[5].val.sec_key,
					SECURITY_KEY_SIZE);


	/* Copy length to s1ap length field */
	datalen = g_ics_buffer.pos - s1ap_len_pos - 1;
	memcpy(g_ics_buffer.buf + s1ap_len_pos, &datalen, sizeof(datalen));

	/* TODO: temp fix */
	g_ics_buffer.buf[1] = 0x09;

	free(s1apPDU.value.data[3].val.E_RABToBeSetupItemCtxtSUReq.nas.elements);
	free(s1apPDU.value.data);
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	send_sctp_msg(g_icsReqInfo->enb_fd, g_ics_buffer.buf, g_ics_buffer.pos, 1);
	log_msg(LOG_INFO, "buffer size is %d\n", g_ics_buffer.pos);
	log_msg(LOG_INFO, "\n-----Stage6 completed.---\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_icsreqstage()
{
	close_ipc_channel(ipcHndl_ics);
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
icsreq_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "icsreq handler ready.\n");

	while(1){
		read_next_msg();

		icsreq_processing();

		post_to_next();
	}

	return NULL;
}
