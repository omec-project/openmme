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
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "options.h"
#include "ipc_api.h"
#include "main.h"
#include "s1ap.h"
#include "s1ap_config.h"
#include "sctp_conn.h"
#include "s1ap_structs.h"
#include "s1ap_msg_codes.h"
#include "s1ap_ie.h"

static void
parse_erab_pdu(char *msg,  int nas_msg_len, struct eRAB_elements *erab)
{
	//struct eRAB_header *header = (struct eRAB*)msg;

	//char *ie = msg + 5; /*ID(2)+crit(1)+len(1)+mistry(1)*/

	/*TODO: write parse_IEs for erab IEs here going ahead*/
	/*For now copying directly as it is single structure*/
	char *ie = msg + 5; /*ID(2)+crit(1)+len(1)*/

	erab->no_of_elements = 1;
	erab->elements = (union eRAB_IE*)calloc(sizeof(union eRAB_IE), 1);
	if(NULL == erab->elements) {
		log_msg(LOG_ERROR, "Memory alloc failed\n");
		exit(-1);
	}

	erab->elements[0].su_res.eRAB_id = *ie;
	++ie;
	++ie; //what is this identify.
	memcpy(&(erab->elements[0].su_res.transp_layer_addr), ie, sizeof(unsigned int));
	erab->elements[0].su_res.transp_layer_addr = ntohl(erab->elements[0].su_res.transp_layer_addr);
	log_msg(LOG_INFO, "eRAB - Transport layer address : %d\n", erab->elements[0].su_res.transp_layer_addr);
	//ntohl ??
	ie+=sizeof(unsigned int);

	memcpy(&(erab->elements[0].su_res.gtp_teid), ie, sizeof(unsigned int));
	erab->elements[0].su_res.gtp_teid = ntohl(erab->elements[0].su_res.gtp_teid);
	log_msg(LOG_INFO, "eRAB - Teid : %d\n", erab->elements[0].su_res.gtp_teid);
	//ntohl ??
}

void
parse_nas_pdu(char *msg,  int nas_msg_len, struct nasPDU *nas,
		unsigned short proc_code)
{
	unsigned char offset = 0;

#if 0
	if(S1AP_UL_NAS_TX_MSG_CODE == proc_code) {
		/*check whether there is security header*/
		unsigned char header_type;
		memcpy(&header_type, msg+1, 1);
		header_type >>= 4;
		if(0 == header_type) { /*not security header*/
			log_msg(LOG_INFO, "No security header\n");
			memcpy(&(nas->header), msg+1, 2);/*copy only till msg type*/
		} else {
			log_msg(LOG_INFO, "Security header\n");
			/*now for esm resp, there is procedure tx identity, why the hell it was not there before.*/
			/*one more donkey logic, do something!!*/
			if(4 == header_type || ((7 == (*(msg+7) & 7)))) {
				memcpy(&(nas->header), msg+7, 2);/*copy only till msg type*/
				offset = 9;
			} else {
				unsigned char tmp;
				memcpy(&(nas->header.message_type), msg+9, 1);/*copy only till msg type*/
				memcpy(&(tmp), msg+7, 1);/*copy only till msg type*/
				nas->header.security_header_type = tmp;
				offset = 10;
			}
		}
	} else {
		memcpy(&(nas->header), msg+2, sizeof(nas_pdu_header));
	}
#endif

	if(S1AP_UL_NAS_TX_MSG_CODE == proc_code) {
		/*check whether there is security header*/
		unsigned char header_type = 0;

		memcpy(&header_type, msg+1, 1);
		header_type >>= 4;
		if(0 == header_type) { /*not security header*/
			log_msg(LOG_INFO, "No security header\n");
			memcpy(&(nas->header), msg+1, 2);/*copy only till msg type*/
		} else {
			log_msg(LOG_INFO, "Security header\n");
			/*now for esm resp, there is procedure tx identity, why the hell it was not there before.*/
			/*one more donkey logic, do something!!*/
			if(4 == header_type || ((7 == (*(msg+7) & 7)))) {
				log_msg(LOG_INFO, "header == 4 || 7\n");
				if(header_type == 4 || header_type == 2) {
				log_msg(LOG_INFO, "security - cihpered\n");
				 memcpy(&(nas->header), msg+7, 2);/*copy only till msg type*/
				 offset = 9;
				}
				else {
				log_msg(LOG_INFO, "security - noned\n");
				memcpy(&(nas->header), msg+1, 2);/*copy only till msg type*/
				offset = 3;
				}
			} else {
				unsigned char tmp;
				memcpy(&(nas->header.message_type), msg+9, 1);/*copy only till msg type*/
				memcpy(&(tmp), msg+7, 1);/*copy only till msg type*/
				nas->header.security_header_type = tmp;
				offset = 10;
			}
		}
	} else if (S1AP_INITIAL_UE_MSG_CODE == proc_code ) {

		unsigned char header_type;
		unsigned char sec_type;
		memcpy(&header_type, msg + 2, 1);
		sec_type = header_type << 4;
		header_type >>= 4;
		if(0 == header_type) { /*not security header*/
			log_msg(LOG_INFO, "No security header\n");
			memcpy(&(nas->header), msg+2, sizeof(nas_pdu_header));/*copy only till msg type*/
		} else {
			log_msg(LOG_INFO, "Security header\n");
			/*now for esm resp, there is procedure tx identity, why the hell it was not there before.*/
			/*one more donkey logic, do something!!*/
			if(4 == header_type || ((7 == (*(msg+7) & 7)))) {
				log_msg(LOG_INFO, "4 == header_type\n");
				if(sec_type == 4) {
				log_msg(LOG_INFO, "security - cihpered\n");
				 memcpy(&(nas->header), msg+7, 2);/*copy only till msg type*/
				 offset = 9;
				}
				else {
				log_msg(LOG_INFO, "security - noned\n");
				memcpy(&(nas->header), msg+1, 2);/*copy only till msg type*/
				offset = 3;
				}
			} else {
				unsigned char tmp;
				memcpy(&(nas->header.message_type), msg+9, 1);/*copy only till msg type*/
				memcpy(&(tmp), msg+7, 1);/*copy only till msg type*/
				nas->header.security_header_type = tmp;
				offset = 10;
			}
		}

	} else {
		memcpy(&(nas->header), msg+2, sizeof(nas_pdu_header));
	}

	log_msg(LOG_INFO, "Nas msg type: %X\n", nas->header.message_type);

	switch(nas->header.message_type) {
	case NAS_ESM_RESP:{
		unsigned char element_id;

		log_msg(LOG_INFO, "ESM response recvd\n");
		memcpy(&element_id, msg + offset, 1);
		++offset;
		nas->elements_len +=1;

		nas->elements = calloc(sizeof(nas_pdu_elements), 2);
		//if(NULL == nas.elements)...

		memcpy(&(nas->elements[0].apn.len), msg + (offset++), 1);
		memcpy(nas->elements[0].apn.val, msg + offset, nas->elements[0].apn.len);
		log_msg(LOG_INFO, "APN name - %s\n", nas->elements[0].apn.val);
		break;
		}

	case NAS_SEC_MODE_COMPLETE:
		log_msg(LOG_INFO, "Sec mode complete recvd\n");
		break;

	case NAS_AUTH_RESP:
		nas->elements_len = 1;
		nas->elements = calloc(sizeof(nas_pdu_elements), 5);
		//if(NULL == nas.elements)...
		memcpy(&(nas->elements[0].auth_resp), msg + 3, sizeof(struct XRES));

		break;

	case NAS_ATTACH_REQUEST:{
		short offset = 0;
		nas->elements_len = 6;
		nas->elements = calloc(sizeof(nas_pdu_elements), 6);
		//if(NULL == nas.elements)...

		/*EPS mobility identity*/
		//memcpy(&(nas->elements[0].IMSI), msg+6, BINARY_IMSI_LEN);
		/*TODO: This encoding/decoding has issue with sprirent and ng40. IMSI
		 * is packed differently.*/
		/*Code working with ng40
		memcpy(&(nas->elements[0].IMSI), msg+6, BINARY_IMSI_LEN);
		offset = 6 + BINARY_IMSI_LEN ;
		*/

		/*Code working with sprirent and Polaris*/
		memcpy(&(nas->elements[0].IMSI), msg+5, BINARY_IMSI_LEN);
		offset = 5 + BINARY_IMSI_LEN ;

		/*UE network capacity*/
		nas->elements[1].ue_network.len = msg[offset];
		++offset;
		memcpy((nas->elements[1].ue_network.capab), msg+offset,
			nas->elements[1].ue_network.len);
		offset += nas->elements[1].ue_network.len + 1;

		/*ESM msg container*/
		{
		short len = msg[offset];
		nas->elements[5].pti = msg[offset + 2];
		unsigned char val = *(msg+offset+5);
		/*ESM message header len is 4: bearer_id_flags(1)+proc_tx_id(1)+msg_id(1)
		 * +pdn_type(1)*/
		/*element id 13(1101....) = "esm required" flag*/
		nas->elements[2].esm_info_tx_required = false;
		if(13 == (val>>4)) {
			nas->elements[2].esm_info_tx_required = true;
			if(val & 1) {
				nas->elements[2].esm_info_tx_required = true;
			}
		}
		offset += len;
		}

		/*DRX parameter*/
		offset += 4;

		/*MS network capability*/
		nas->elements[4].ms_network.element_id = msg[offset];
		++offset;
		nas->elements[4].ms_network.len = msg[offset];
		++offset;
		memcpy((nas->elements[4].ms_network.capab), msg+offset,
			nas->elements[4].ms_network.len);

		break;
		}

	case NAS_ATTACH_COMPLETE:
		/*Other than error check there seems no information to pass to mme. Marking TODO for protocol study*/
		break;

	case NAS_DETACH_REQUEST: {
		nas->elements_len = 1;
		nas->elements = calloc(sizeof(nas_pdu_elements), 1);

		/*EPS mobility identity*/
		memcpy(&(nas->elements[0].mi_guti), msg + 11, sizeof(guti));
		log_msg(LOG_INFO, "M-TMSI - %d\n", nas->elements[0].mi_guti.m_TMSI);
		break;
	}

	default:
		log_msg(LOG_ERROR, "Unknown NAS IE type- 0x%x\n", nas->header.message_type);
		break;

	}
}

int
parse_IEs(char *msg, struct proto_IE *proto_ies, unsigned short proc_code)
{
	unsigned short int no_of_IEs=0;

	short data_size=0;
	msg +=1;
	memcpy(&data_size, msg, 1);

	msg +=2;
	memcpy(&no_of_IEs, msg, 2);
	//no_of_IEs=msg[0];
	no_of_IEs = ntohs(no_of_IEs);

	/*Dumb logic....protocol or is creepy. Len sometimes comes in 3 bytes. How to know that??*/
	if(0 == no_of_IEs) {
		++msg;
		memcpy(&no_of_IEs, msg, 2);
		no_of_IEs = ntohs(no_of_IEs);
	}

	log_msg(LOG_INFO, "No of IEs = %d\n", no_of_IEs);
	proto_ies->no_of_IEs = no_of_IEs;
	proto_ies->data = calloc(sizeof(union proto_IE_data), no_of_IEs);
	//alloc fail chk
	msg+=2;

	for(int i=0; i < no_of_IEs; ++i) {
		union proto_IE_data *ie = &(proto_ies->data[i]);
		unsigned short IE_type, IE_data_len = 0;

		memcpy(&IE_type, msg, sizeof(short int));
		IE_type = ntohs(IE_type);
		ie->IE_type = IE_type;
		msg +=2;//next to ie type
		msg +=1;//next to criticality
        /*parse length according to PER rules*/
        char val = msg[0] & 0x10111111;
        val = val >> 6;
        if(val == 0x02)
        {
		    log_msg(LOG_INFO, "length more than 128");
            unsigned short first = msg[0] & 0x00111111;
            msg += 1;
            unsigned short second = msg[0];
            unsigned short ie_len = second & (first << 8);
            IE_data_len = ie_len;
        }
        else
        {
		    log_msg(LOG_INFO, "length less than 128");
		    memcpy(&IE_data_len, msg, sizeof(char));
        }

		msg+=1;//next to len
		//IE_data_len = (IE_data_len);
		log_msg(LOG_INFO, "IE type = %d\n", IE_type);
		log_msg(LOG_INFO, "IE data len= %ud\n", IE_data_len);

		/*Based on IE_Type call the parser to read IE info*/
		/*TODO: optimize with function ptr etc.*/
		switch(IE_type) {
		case S1AP_IE_GLOBAL_ENB_ID:
			log_msg(LOG_INFO, "parse global eNB ID\n");
			ie_parse_global_enb_id(msg+6, IE_data_len);
			break;

		case S1AP_IE_ENB_NAME:
			log_msg(LOG_INFO, "parse global eNB name\n");
			break;

		case S1AP_IE_SUPPORTED_TAS:
			break;

		case S1AP_IE_DEF_PAGING_DRX:
			break;

		case S1AP_IE_MME_UE_ID:{
			ie->mme_ue_s1ap_id = decode_int_val((unsigned char *)msg,
					IE_data_len);
			log_msg(LOG_ERROR, "parse MME_UE_S1AP_ID - %d\n",
					ie->mme_ue_s1ap_id);
			break;
			}

		case S1AP_IE_ENB_UE_ID:{
			ie->enb_ue_s1ap_id = decode_int_val((unsigned char *)msg,
					IE_data_len);
			log_msg(LOG_INFO, "parse ENB_UE_S1AP_ID - %d\n",
					ie->enb_ue_s1ap_id);
			break;
			}

		case S1AP_IE_TAI:{
			log_msg(LOG_INFO, "TAI parse\n");
			memcpy(&(ie->tai), msg+1, sizeof(struct TAI));
			log_msg(LOG_INFO, "plmn-%x %x %x, tac-%d\n",ie->tai.plmn_id.idx[0],
					ie->tai.plmn_id.idx[1], ie->tai.plmn_id.idx[2],
					ie->tai.tac);
			break;
			}

		case S1AP_IE_UTRAN_CGI:{
			log_msg(LOG_INFO, "EUTRAN CGI\n");
			memset(&(ie->utran_cgi), 0, sizeof(struct CGI));
			memcpy(&(ie->utran_cgi), msg+1, sizeof(struct CGI));
			log_msg(LOG_INFO, "plmn-%x %x %x, cell-%d\n",
					ie->utran_cgi.plmn_id.idx[0],
					ie->utran_cgi.plmn_id.idx[1], ie->utran_cgi.plmn_id.idx[2],
					ie->utran_cgi.cell_id);
			break;
			}

		case S1AP_IE_NAS_PDU: {
			log_msg(LOG_INFO, "parse NAS_PDU\n");
			parse_nas_pdu(msg, IE_data_len, &ie->nas, proc_code);
			break;
			}

		case S1AP_IE_RRC_EST_CAUSE: {
			log_msg(LOG_INFO, "parse RRC establishment code - %d\n", ie->rrc_est_cause);
			break;
			}

		case S1AP_ERAB_SETUP_CTX_SUR:
			parse_erab_pdu(msg, IE_data_len, &ie->erab);
			break;

		default:
			log_msg(LOG_INFO, "Check IE type %d\n", IE_type);
			break;
		}

		msg += (IE_data_len);
		if(128 == IE_data_len) ++msg;//TODO: byte size issue. chk thi.
	}
	return 0;
}

static int
init_ue_msg_handler(char *msg, int enb_fd)
{
	//TODO: use static instead of synamic for perf.
	struct proto_IE proto_ies;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "--------------------- %d --------------", msg[3]);
	if (msg[3] == 0x80)
		parse_IEs(msg+3, &proto_ies, S1AP_INITIAL_UE_MSG_CODE);
	else
		parse_IEs(msg+2, &proto_ies, S1AP_INITIAL_UE_MSG_CODE);

	/*Check nas message type*/
	//TODO: check through all proto IEs for which is nas
	//currentlyy hard coding to 2 looking at packets
	log_msg(LOG_INFO, "NAS msg type = %x\n", proto_ies.data[2].nas.header.message_type);
	switch(proto_ies.data[1].nas.header.message_type) {
	case NAS_ATTACH_REQUEST:
		s1_init_ue_handler(&proto_ies, enb_fd);
		break;

	case NAS_DETACH_REQUEST:
		detach_stage1_handler(&proto_ies, true);
		break;
	}

	free(proto_ies.data);
	//TODO: free IEs
	return SUCCESS;
}

static int
UL_NAS_msg_handler(char *msg, int enb_fd)
{
	//TODO: use static instead of synamic for perf.
	struct proto_IE proto_ies;

	/*****Message structure***
	*/
	parse_IEs(msg+2, &proto_ies, S1AP_UL_NAS_TX_MSG_CODE);

	/*Check nas message type*/
	//TODO: check through all proto IEs for which is nas
	//currentlyy hard coding to 2 looking at packets
	log_msg(LOG_INFO, "NAS msg type = %x\n", proto_ies.data[2].nas.header.message_type);
	switch(proto_ies.data[2].nas.header.message_type) {
	case NAS_AUTH_RESP:
		s1_auth_resp_handler(&proto_ies);
		break;

	case NAS_ATTACH_REQUEST:
		s1_init_ue_handler(&proto_ies, enb_fd);
		break;

	case NAS_SEC_MODE_COMPLETE:
		s1_secmode_resp_handler(&proto_ies);
		break;

	case NAS_ESM_RESP:
		s1_esm_resp_handler(&proto_ies);
		break;

	case NAS_ATTACH_COMPLETE:
		s1_attach_complete_handler(&proto_ies);
		break;

	case NAS_DETACH_REQUEST:
		detach_stage1_handler(&proto_ies, false);
		break;
	}

	//TODO: free IEs
	free(proto_ies.data);
	return SUCCESS;
}

void
handle_s1ap_message(void *msg)
{
	log_msg(LOG_INFO, "Inside handle_s1ap_message.\n");
	/*convert message from network to host*/

	/*Call handler for the procedure code. TBD: Tasks pool for handlers*/

	int enb_fd = 0;
	memcpy(&enb_fd, msg, sizeof(enb_fd));
	char *message = ((char *) msg) + sizeof(enb_fd);

	struct s1ap_header *header = (struct s1ap_header*)(message);
	header->procedure_code = ntohs(header->procedure_code);
	header->criticality= ntohs(header->criticality);
	log_msg(LOG_INFO, "proc code %d\n", header->procedure_code & 0x00FF);

	switch(header->procedure_code & 0x00FF){
	case S1AP_SETUP_REQUEST_CODE:
		s1_setup_handler(message, enb_fd);
		break;

	case S1AP_INITIAL_UE_MSG_CODE:
		init_ue_msg_handler(message, enb_fd);
		break;

	case S1AP_UL_NAS_TX_MSG_CODE:
		UL_NAS_msg_handler(message, enb_fd);
		break;

	case S1AP_INITIAL_CTX_RESP_CODE:
		s1_init_ctx_resp_handler(message);
		break;

	case S1AP_UE_CTX_RELEASE_CODE:
		s1_ctx_release_resp_handler(message);
		break;

	default:
		log_msg(LOG_ERROR, "Unknown procedure code - %d\n",
			header->procedure_code & 0x00FF);
		break;
	}
	free(msg);
	return;
}
