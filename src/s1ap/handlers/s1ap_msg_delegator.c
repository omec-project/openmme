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
#include "ProtocolIE-ID.h"
#include "ProtocolIE-Field.h"
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
	log_msg(LOG_INFO, "NAS PDU proc code: %u\n", proc_code);

	unsigned short msg_len = nas_msg_len;
    char* msg_end = msg + nas_msg_len;

	char *buffer = NULL;
	log_msg(LOG_INFO, "NAS PDU msg: %s\n", msg_to_hex_str(msg, msg_len, &buffer));
	log_buffer_free(&buffer);

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
#endif

        nas_pdu_header_sec nas_header_sec;
        nas_pdu_header_short nas_header_short;
        nas_pdu_header_long nas_header_long;

        unsigned char sec_header_type;
        unsigned char protocol_discr;

        sec_header_type = (msg[0] >> 4) & 0x0F;
        protocol_discr = msg[0] & 0x0F;
        unsigned char is_ESM = ((unsigned short)protocol_discr == 0x02);  // see TS 24.007
        log_msg(LOG_INFO, "Security header=%d\n", sec_header_type);
        log_msg(LOG_INFO, "Protocol discriminator=%d\n", protocol_discr);
        log_msg(LOG_INFO, "is_ESM=%d\n", is_ESM);

        if(0 != sec_header_type) { /*security header*/
            log_msg(LOG_INFO, "Security header\n");
            if(SERVICE_REQ_SECURITY_HEADER == sec_header_type)
            {
                log_msg(LOG_INFO, "Recvd security header for Service request.");
                nas->header.security_header_type = sec_header_type;
                nas->header.proto_discriminator = protocol_discr;
                msg += 1;
                nas->header.ksi = msg[0] >> 4;
                nas->header.seq_no = msg[0] & 0x0F;
                msg += 1;
                memcpy(nas->header.short_mac, msg, SHORT_MAC_SIZE);
                nas->header.message_type = NAS_SERVICE_REQUEST;
                return;
            }

            memcpy(&nas_header_sec, msg, sizeof(nas_pdu_header_sec));

            char *buffer = NULL;
            log_msg(LOG_INFO, "mac=%s\n", msg_to_hex_str((char *)nas_header_sec.mac, MAC_SIZE, &buffer));
            log_buffer_free(&buffer);

            log_msg(LOG_INFO, "seq no=%x\n", nas_header_sec.seq_no);
            nas->header.seq_no = nas_header_sec.seq_no; 
            msg += 6;

            sec_header_type = msg[0] >> 4;
            protocol_discr = msg[0] & 0x0F;
            unsigned char is_ESM = ((unsigned short)protocol_discr == 0x02);  // see TS 24.007
            log_msg(LOG_INFO, "Security header=%d\n", sec_header_type);
            log_msg(LOG_INFO, "Protocol discriminator=%d\n", protocol_discr);
            log_msg(LOG_INFO, "is_ESM=%d\n", is_ESM);
            if (is_ESM) {
                log_msg(LOG_INFO, "NAS PDU is ESM\n");
                memcpy(&nas_header_long, msg, sizeof(nas_header_long)); /*copy only till msg type*/
                msg += 3;

                nas->header.security_header_type = nas_header_long.security_header_type;
                nas->header.proto_discriminator = nas_header_long.proto_discriminator;
                nas->header.procedure_trans_identity = nas_header_long.procedure_trans_identity;
                nas->header.message_type = nas_header_long.message_type;
            } else {
                log_msg(LOG_INFO, "NAS PDU is EMM\n");
                memcpy(&nas_header_short, msg, sizeof(nas_header_short)); /*copy only till msg type*/
                msg += 2;

                nas->header.security_header_type = nas_header_short.security_header_type;
                nas->header.proto_discriminator = nas_header_short.proto_discriminator;
                nas->header.message_type = nas_header_short.message_type;
            }
        } else {
            log_msg(LOG_INFO, "No security header\n");
            memcpy(&nas_header_short, msg, sizeof(nas_header_short)); /*copy only till msg type*/
            msg += 2;

            nas->header.security_header_type = nas_header_short.security_header_type;
            nas->header.proto_discriminator = nas_header_short.proto_discriminator;
            nas->header.message_type = nas_header_short.message_type;
        }


	log_msg(LOG_INFO, "Nas msg type: %X\n", nas->header.message_type);

	switch(nas->header.message_type) 
    {
        case NAS_ESM_RESP:{
            log_msg(LOG_INFO, "NAS_ESM_RESP recvd\n");

            unsigned char element_id;
            memcpy(&element_id, msg, 1);
            msg++;
            nas->elements_len +=1;

            nas->elements = calloc(sizeof(nas_pdu_elements), 2);
            //if(NULL == nas.elements)...

            nas->elements[0].msgType = NAS_IE_TYPE_APN; 
            memcpy(&(nas->elements[0].pduElement.apn.len), msg, 1);
            msg++;
            memcpy(nas->elements[0].pduElement.apn.val, msg, nas->elements[0].pduElement.apn.len);
            log_msg(LOG_INFO, "APN name - %s\n", nas->elements[0].pduElement.apn.val);
            break;
        }

        case NAS_SEC_MODE_COMPLETE:
            log_msg(LOG_INFO, "NAS_SEC_MODE_COMPLETE recvd\n");
        break;

        case NAS_AUTH_RESP:
            log_msg(LOG_INFO, "NAS_AUTH_RESP recvd\n");
            nas->elements_len = 1;
            nas->elements = calloc(sizeof(nas_pdu_elements), 5);
            //if(NULL == nas.elements)...
            unsigned short len = get_length(&msg);
            memcpy(&(nas->elements[0].pduElement.auth_resp), msg, sizeof(struct XRES));

        break;
        case NAS_IDENTITY_RESPONSE: {
            log_msg(LOG_INFO, "NAS_IDENTITY_RESPONSE recvd\n");
            nas->elements_len = 1;
            nas->elements = calloc(sizeof(nas_pdu_elements), 1);

            unsigned short imsi_len = get_length(&msg);
            /*EPS mobility identity. TODO : More error checking */
            memcpy(&(nas->elements[0].pduElement.IMSI), msg, imsi_len);
            break;
        }
        case NAS_TAU_REQUEST: {
            // I dont want to know anythng from TAU for now..
            // Important thing from the TAU : 
            //   Current bearers available in the UE. If any missing bearer means
            //   we need to delete those bearers from the core network. 
            break;
        }
        case NAS_AUTH_FAILURE:
        {
            nas->elements_len = 1;
            nas->elements = calloc(sizeof(nas_pdu_elements), 1);
            //if(NULL == nas.elements)...
            char err = *(char*)(msg);
            if(err == AUTH_SYNC_FAILURE)
            {
                log_msg(LOG_INFO, "AUTH Sync Failure. Start Re-Sync");
                nas->elements[0].msgType = NAS_IE_TYPE_AUTH_FAIL_PARAM;
                memcpy(&(nas->elements[0].pduElement.auth_fail_resp), msg + 2, sizeof(struct AUTS));
            }
            else
            {
                log_msg(LOG_ERROR, "Authentication Failure. Mac Failure");
            }

        }break;

        case NAS_ATTACH_REQUEST:{
            log_msg(LOG_INFO, "NAS_ATTACH_REQUEST recvd\n");
            unsigned char tmp = msg[0];
            /* 1 byte is NAS Key set Id + EPS attach Type.. i am confused with following
             * variable names
             */
            nas->header.security_encryption_algo = (tmp & 0xF0) >> 4;
            nas->header.security_integrity_algo = tmp & 0x0F;
            msg++;

            nas->elements_len = 7; // index should never cross  6.. 0 to 6 
            nas->elements = calloc(sizeof(nas_pdu_elements), nas->elements_len);
            int index = 0;

            unsigned short imsi_len = get_length(&msg);
            // TODO : support even number of digits in IMSI
            bool odd = msg[0] & 0x08; // if this bit is set then odd number of digits in identity
            unsigned char eps_identity = msg[0] & 0x07;
            switch(eps_identity) {
                case 0x01: {
                    // Mobile Identity contains imsi
                    nas->flags |= NAS_MSG_UE_IE_IMSI;
                    log_msg(LOG_INFO, "IMSI len=%u - %u\n", imsi_len, BINARY_IMSI_LEN);
                    nas->elements[index].msgType = NAS_IE_TYPE_EPS_MOBILE_ID_IMSI;
                    memcpy(&(nas->elements[index].pduElement.IMSI), msg, imsi_len);
                    break;
                }
                case 0x06: {
                    log_msg(LOG_INFO, "Mobile identity GUTI Rcvd \n");
                    // Mobile Identity contains GUTI
                    // MCC+MNC offset = 3
                    // MME Group Id   = 2
                    // MME Code       = 1
                    // MTMSI offset from start of this AVP = 3 + 2 + 1
                    nas->elements[index].msgType = NAS_IE_TYPE_EPS_MOBILE_ID_IMSI;
                    memcpy(&nas->elements[index].pduElement.mi_guti.plmn_id.idx, &msg[1], 3);
                    nas->elements[index].pduElement.mi_guti.mme_grp_id = ntohs(*(short int *)(&msg[4]));
                    nas->elements[index].pduElement.mi_guti.mme_code = msg[6];
                    nas->elements[index].pduElement.mi_guti.m_TMSI = ntohl(*((unsigned int *)(&msg[7])));
                    log_msg(LOG_INFO, "NAS Attach Request Rcvd ID: GUTI. PLMN id %d %d %d \n", nas->elements[index].pduElement.mi_guti.plmn_id.idx[0], 
                            nas->elements[index].pduElement.mi_guti.plmn_id.idx[1], 
                            nas->elements[index].pduElement.mi_guti.plmn_id.idx[2] );
                    log_msg(LOG_INFO, "NAS Attach Request Rcvd ID: GUTI. mme group id = %d, MME code %d  mtmsi = %d\n", 
                            nas->elements[index].pduElement.mi_guti.mme_grp_id, 
                            nas->elements[index].pduElement.mi_guti.mme_code,
                            nas->elements[index].pduElement.mi_guti.m_TMSI);
                    nas->flags |= NAS_MSG_UE_IE_GUTI;
                    break;
                }
                case 0x03: {
                    // Mobile Identity contains imei
                    break;
                }
            }

            msg += imsi_len;
            char *buffer = NULL;
            log_msg(LOG_INFO, "IMSI=%s [to be read nibble-swapped]\n",
                    msg_to_hex_str((char *)nas->elements[index].pduElement.IMSI, imsi_len, &buffer));
            log_buffer_free(&buffer);

            /*UE network capacity*/
            index++;
            nas->elements[index].msgType = 
                NAS_IE_TYPE_UE_NETWORK_CAPABILITY;
            nas->elements[index].pduElement.ue_network.len = msg[0];
            msg++;
            memcpy(
                   (nas->elements[index].pduElement.ue_network.capab)
                   ,msg,
                   nas->elements[index].pduElement.ue_network.len);
            msg += nas->elements[index].pduElement.ue_network.len;

            index++;
            /*ESM msg container*/
            len = msg[0] << 8 | msg[1];
            msg += 2;
            //now msg points to ESM message contents
            log_msg(LOG_INFO, "len=%x\n", len);
            log_msg(LOG_INFO, "msg[0]=%x\n", msg[0]);
            nas->elements[index].pduElement.pti = msg[1];
            nas->elements[index].msgType = NAS_IE_TYPE_PTI;
            log_msg(LOG_INFO, "pti=%x\n", nas->elements[index].pduElement.pti);
            unsigned short int msg_offset = 4;
            /*ESM message header len is 4: bearer_id_flags(1)+proc_tx_id(1)+msg_id(1)
             * +pdn_type(1)*/
            /*element id 13(1101....) = "esm required" flag*/
            //if tx_flag is absent then it means flag is set to false 
            //nas->elements[index].pduElement.esm_info_tx_required = false;
            while(msg_offset < len)
            {
                unsigned char val = msg[msg_offset];
                log_msg(LOG_INFO, "ESM container AVP val=%x\n", val);
                if(13 == (val>>4))
                {
                    index++;
                    nas->elements[index].msgType = NAS_IE_TYPE_TX_FLAG;
                    // byte 0 - EBI+PD, byte1 - pti, byte2 - message type, byte3 - pdntype+reqtype, byte4 - ESM info transfer flag == Total 5 bytes... msg[0] to msg[4]
                    //nas->elements[2].esm_info_tx_required = true;
                    if(val & 1) {
                        nas->elements[index].pduElement.esm_info_tx_required = true;
                        log_msg(LOG_INFO, "ESM information requested ");
                    }
                    msg_offset++; /* just one byte AVP */
                    continue;

                }
                if(0x27 == val)
                {
                    unsigned short int pco_offset =  msg_offset;
                    unsigned char pco_length = msg[msg_offset+1];
                    // element Id 1 byte and pco length 1 byte 
                    // Copy from - 1 byte header Extension + Configuration Protocol
                    index++;
                    nas->elements[index].msgType = NAS_IE_TYPE_PCO;
                    memcpy(&nas->elements[index].pduElement.pco_opt.pco_options[0], &msg[msg_offset+2], pco_length); 
                    nas->elements[index].pduElement.pco_opt.pco_length = pco_length;
                    msg_offset = pco_length + 2; // msg offset was already at PCO AVP type. Now it should point to next AVP type
                    log_msg(LOG_DEBUG, "PCO length = %d \n", pco_length);
                    continue;
                }
                break; // unhandled ESM AVP...Add support..for now just break out..else we would be in tight loop
            }
            msg += len;

            unsigned char elem_id = msg[0];
            while(msg != msg_end)
            {
                elem_id = msg[0];
                elem_id >>= 4;
                if((NAS_IE_TYPE_GUTI_TYPE == elem_id)
                    || (NAS_IE_TYPE_TMSI_STATUS == elem_id)
                    || (NAS_IE_TYPE_MS_NETWORK_FEATURE_SUPPORT == elem_id))
                {
                    switch(elem_id)
                    {
                        case NAS_IE_TYPE_GUTI_TYPE:
                            {
                                log_msg(LOG_DEBUG, "Old guti type : Skipping.\n");
                                msg++;
                            }break;
                        case NAS_IE_TYPE_TMSI_STATUS:
                            {
                                log_msg(LOG_DEBUG, "TMSI Status : Skipping.\n");
                                msg++;
                            }break;
                        case NAS_IE_TYPE_MS_NETWORK_FEATURE_SUPPORT:
                            {
                                log_msg(LOG_DEBUG, "MS Network feature support : Skipping.\n");
                                msg++;
                            }break;
                        default:
                            log_msg(LOG_WARNING, "Unknown AVP in attach msg. %d \n",elem_id);
                            msg++;
                    }

                    continue;
                }
                else
                {
                    elem_id = msg[0];
                    switch(elem_id)
                    {
                        case NAS_IE_TYPE_DRX_PARAM:
                            {
                                log_msg(LOG_DEBUG, "DRX Param : Skipping.\n");
                                msg += 3;
                            }break;
                        case NAS_IE_TYPE_TAI:
                            {
                                log_msg(LOG_DEBUG, "TAI : Skipping.\n");
                                msg += 6;
                            }break;
                        case NAS_IE_TYPE_MS_CLASSMARK_2:
                            {
                                log_msg(LOG_DEBUG, "MS classmark 2 : Skipping.\n");
                                int len = msg[1];
                                msg += len + 2; //msgid + len field + len;
                            }break;
                        case NAS_IE_TYPE_VOICE_DOMAIN_PREF_UE_USAGE_SETTING:
                            {
                                log_msg(LOG_DEBUG, "Voice domain UE Usage : Skipping.\n");
                                int len = msg[1];
                                msg += len + 2; //msgid + len field + len;
                            }break;
                        case NAS_IE_TYPE_MS_NETWORK_CAPABILITY:
                            {
                                log_msg(LOG_DEBUG, "MS Network capability : Handling.\n");
                                index++;
                                nas->elements[index].msgType = NAS_IE_TYPE_MS_NETWORK_CAPABILITY;
                                nas->elements[index].pduElement.ms_network.pres = true;
                                nas->elements[index].pduElement.ms_network.element_id 
                                    = msg[0];
                                msg++;
                                nas->elements[index].pduElement.ms_network.len = msg[0];
                                msg++;
                                memcpy(
                                       (nas->elements[index].pduElement.ms_network.capab), 
                                       msg, 
                                       nas->elements[index].pduElement.ms_network.len);
                                msg += 
                                    nas->elements[index].pduElement.ms_network.len;
                            }break;
                        default:
                            log_msg(LOG_WARNING, "Unknown AVP in Attach Req  %d \n", elem_id);
                            msg++;
                    }
                
                    continue;
                }
            }
            break;
        }

        case NAS_ATTACH_COMPLETE:
        /*Other than error check there seems no information to pass to mme. Marking TODO for protocol study*/
        break;

        case NAS_DETACH_REQUEST: 
        {
            log_msg(LOG_INFO, "NAS_DETACH_REQUEST recvd\n");
            nas->elements_len = 1;
            nas->elements = calloc(sizeof(nas_pdu_elements), 1);

            /*EPS mobility identity*/
            memcpy(&(nas->elements[0].pduElement.mi_guti), msg + 1, sizeof(guti));
            log_msg(LOG_INFO, "M-TMSI - %d\n", nas->elements[0].pduElement.mi_guti.m_TMSI);
            break;
        }

        default:
        log_msg(LOG_ERROR, "Unknown NAS Message type- 0x%x\n", nas->header.message_type);
        break;

    }
}


int
parse_IEs(char *msg, struct proto_IE *proto_ies, unsigned short proc_code)
{
	unsigned short int no_of_IEs=0;

	//short data_size=0;
	//msg +=1;
	//memcpy(&data_size, msg, 1);

	//msg +=2;
	memcpy(&no_of_IEs, msg, 2);
	//no_of_IEs=msg[0];
	no_of_IEs = ntohs(no_of_IEs);

	/*Dumb logic....protocol or is creepy. Len sometimes comes in 3 bytes. How to know that??*/
	if(0 == no_of_IEs) {
		++msg;
		memcpy(&no_of_IEs, msg, 2);
		no_of_IEs = ntohs(no_of_IEs);
	}

	log_msg(LOG_INFO, "No. of IEs = %d\n", no_of_IEs);
	proto_ies->no_of_IEs = no_of_IEs;
	proto_ies->data = calloc(sizeof(struct proto_IE_data), no_of_IEs);
	//alloc fail chk
	msg+=2;

	for(int i=0; i < no_of_IEs; ++i) {
		struct proto_IE_data *ie = &(proto_ies->data[i]);
		unsigned short IE_type, IE_data_len = 0;

		memcpy(&IE_type, msg, sizeof(short int));
		IE_type = ntohs(IE_type);
		ie->IE_type = IE_type;
		msg +=2;//next to ie type
		msg +=1;//next to criticality

		IE_data_len = get_length(&msg);
		log_msg(LOG_INFO, "IE [%d]: type = %d\n", i, IE_type);
		log_msg(LOG_INFO, "IE [%d]: data len= %x - %u\n", i, IE_data_len, IE_data_len);

		char *buffer = NULL;
		log_msg(LOG_INFO, "IE [%d]: value= %s\n", i, msg_to_hex_str(msg, IE_data_len, &buffer));
	    log_buffer_free(&buffer);

		/*Based on IE_Type call the parser to read IE info*/
		/*TODO: optimize with function ptr etc.*/
		switch(IE_type) {
		case S1AP_IE_GLOBAL_ENB_ID:
			log_msg(LOG_INFO, "IE [%d]: parse global eNB ID\n", i);
			ie_parse_global_enb_id(msg+6, IE_data_len);
			break;

		case S1AP_IE_ENB_NAME:
			log_msg(LOG_INFO, "IE [%d]: parse global eNB name\n", i);
			ie_parse_enb_name(msg, IE_data_len);
			break;

		case S1AP_IE_SUPPORTED_TAS:
			break;

		case S1AP_IE_DEF_PAGING_DRX:
			break;

		case S1AP_IE_MME_UE_ID:{
			ie->val.mme_ue_s1ap_id = decode_int_val((unsigned char *)msg,
					IE_data_len);
			log_msg(LOG_INFO, "IE [%d]: parse MME_UE_S1AP_ID - %d\n", i,
					ie->val.mme_ue_s1ap_id);
			break;
			}

		case S1AP_IE_ENB_UE_ID:{
			ie->val.enb_ue_s1ap_id = decode_int_val((unsigned char *)msg,
					IE_data_len);
			log_msg(LOG_INFO, "IE [%d]: parse ENB_UE_S1AP_ID - %d\n", i,
					ie->val.enb_ue_s1ap_id);
			break;
			}

		case S1AP_IE_TAI:{
			log_msg(LOG_INFO, "IE [%d]: TAI parse\n", i);
			memcpy(&(ie->val.tai), msg+1, sizeof(struct TAI));
			log_msg(LOG_INFO, "IE [%d]: plmn-%x %x %x, tac-%d\n", i,
					ie->val.tai.plmn_id.idx[0],
					ie->val.tai.plmn_id.idx[1], ie->val.tai.plmn_id.idx[2],
					ie->val.tai.tac);
			break;
			}

		case S1AP_IE_UTRAN_CGI:{
			log_msg(LOG_INFO, "IE [%d]: EUTRAN CGI\n", i);
			memset(&(ie->val.utran_cgi), 0, sizeof(struct CGI));
			memcpy(&(ie->val.utran_cgi), msg+1, sizeof(struct CGI));
			log_msg(LOG_INFO, "IE [%d]: plmn-%x %x %x, cell-%d\n", i,
					ie->val.utran_cgi.plmn_id.idx[0],
					ie->val.utran_cgi.plmn_id.idx[1], ie->val.utran_cgi.plmn_id.idx[2],
					ie->val.utran_cgi.cell_id);
			break;
			}

		case S1AP_IE_NAS_PDU: {
	        log_msg(LOG_INFO, "IE [%d]: NAS msg type parsed = %x\n", i,
                            ie->val.nas.header.message_type);
			parse_nas_pdu(msg, IE_data_len, &ie->val.nas, proc_code);
			break;
			}

		case S1AP_IE_RRC_EST_CAUSE: {
			log_msg(LOG_INFO, "IE [%d]: parse RRC establishment code - %d\n", i, 
                     ie->val.rrc_est_cause);
			break;
			}

		case S1AP_ERAB_SETUP_CTX_SUR:
			log_msg(LOG_INFO, "IE [%d]: parse S1AP_ERAB_SETUP_CTX_SUR parse_erab_pdu \n", i);
			parse_erab_pdu(msg, IE_data_len, &ie->val.erab);
			break;

		default:
			log_msg(LOG_INFO, "IE [%d]: Check IE type %d\n", i, IE_type);
			break;
		}

		msg += (IE_data_len);
		if(128 == IE_data_len) ++msg;//TODO: byte size issue. chk thi.
	}
	return 0;
}

int convertToInitUeProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies)
{
    proto_ies->procedureCode = msg->procedureCode;
    proto_ies->criticality = msg->criticality;

    if(msg->value.present == InitiatingMessage__value_PR_InitialUEMessage)
    {
        ProtocolIE_Container_129P32_t* protocolIes = &msg->value.choice.InitialUEMessage.protocolIEs;
        proto_ies->no_of_IEs = protocolIes->list.count;

        log_msg(LOG_INFO, "No of IEs = %d\n", proto_ies->no_of_IEs);
        proto_ies->data = calloc(sizeof(struct proto_IE_data), proto_ies->no_of_IEs);
        if(proto_ies->data == NULL) {
            log_msg(LOG_ERROR,"Calloc failed for protocol IE.");
            return -1;
        }
		for (int i = 0; i < protocolIes->list.count; i++) {
			InitialUEMessage_IEs_t *ie_p;
			ie_p = protocolIes->list.array[i];
			switch(ie_p->id) {
				case ProtocolIE_ID_id_eNB_UE_S1AP_ID:
					{
                        ENB_UE_S1AP_ID_t *s1apENBUES1APID_p = NULL;
                        if(InitialUEMessage_IEs__value_PR_ENB_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apENBUES1APID_p = &ie_p->value.choice.ENB_UE_S1AP_ID;
                        }
						
                        if (s1apENBUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE eNB_UE_S1AP_ID failed\n");
							return -1;
						}

                        log_msg(LOG_DEBUG, "ENB UE S1ap ID decode Success\n");
                        proto_ies->data[i].IE_type = S1AP_IE_ENB_UE_ID; 
						memcpy(&proto_ies->data[i].val.enb_ue_s1ap_id, s1apENBUES1APID_p, sizeof(ENB_UE_S1AP_ID_t));
						s1apENBUES1APID_p = NULL;
					} break;
				case ProtocolIE_ID_id_NAS_PDU:
					{
                        NAS_PDU_t *s1apNASPDU_p = NULL;
                        if(InitialUEMessage_IEs__value_PR_NAS_PDU == ie_p->value.present)
                        {
						    s1apNASPDU_p = &ie_p->value.choice.NAS_PDU;
                        }
						
                        if (s1apNASPDU_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE NAS PDU failed\n");
							return -1;
						}

                        log_msg(LOG_DEBUG, "NAS PDU decode Success\n");
                        proto_ies->data[i].IE_type = S1AP_IE_NAS_PDU; 
                        parse_nas_pdu((char*)s1apNASPDU_p->buf, s1apNASPDU_p->size, 
                                       &proto_ies->data[i].val.nas, msg->procedureCode);
						s1apNASPDU_p = NULL;
					} break;
				case ProtocolIE_ID_id_TAI:
					{
                        TAI_t *s1apTAI_p = NULL;
                        if(InitialUEMessage_IEs__value_PR_TAI == ie_p->value.present)
                        {
						    s1apTAI_p = &ie_p->value.choice.TAI;
                        }
						
                        if (s1apTAI_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE TAI failed\n");
							return -1;
						}

                        log_msg(LOG_DEBUG, "TAI decode Success\n");
                        proto_ies->data[i].IE_type = S1AP_IE_TAI; 
						memcpy(&proto_ies->data[i].val.tai.tac, s1apTAI_p->tAC.buf, s1apTAI_p->tAC.size);
						memcpy(proto_ies->data[i].val.tai.plmn_id.idx, 
                                s1apTAI_p->pLMNidentity.buf, s1apTAI_p->pLMNidentity.size);
						s1apTAI_p = NULL;
					} break;
				case ProtocolIE_ID_id_EUTRAN_CGI:
					{
			            EUTRAN_CGI_t*	 s1apCGI_p = NULL;;
                        if(InitialUEMessage_IEs__value_PR_EUTRAN_CGI == ie_p->value.present)
                        {
						    s1apCGI_p = &ie_p->value.choice.EUTRAN_CGI;
                        }
						
                        if (s1apCGI_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE CGI failed\n");
							return -1;
						}

                        log_msg(LOG_DEBUG, "CGI decode Success\n");
                        proto_ies->data[i].IE_type = S1AP_IE_UTRAN_CGI; 
						memcpy(&proto_ies->data[i].val.utran_cgi.cell_id, 
                               s1apCGI_p->cell_ID.buf, s1apCGI_p->cell_ID.size);
						memcpy(proto_ies->data[i].val.utran_cgi.plmn_id.idx, 
                                s1apCGI_p->pLMNidentity.buf, s1apCGI_p->pLMNidentity.size);
						s1apCGI_p = NULL;
					} break;
				case ProtocolIE_ID_id_RRC_Establishment_Cause:
					{
			            RRC_Establishment_Cause_t	 *s1apRRCEstCause_p;
                        if(InitialUEMessage_IEs__value_PR_RRC_Establishment_Cause == ie_p->value.present)
                        {
						    s1apRRCEstCause_p = &ie_p->value.choice.RRC_Establishment_Cause;
                        }
						
                        if (s1apRRCEstCause_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE RRC Cause failed\n");
							return -1;
						}

                        log_msg(LOG_DEBUG, "RRC Cause decode Success\n");
                        proto_ies->data[i].IE_type = S1AP_IE_RRC_EST_CAUSE; 
						proto_ies->data[i].val.rrc_est_cause = (enum ie_RRC_est_cause) *s1apRRCEstCause_p;
						s1apRRCEstCause_p = NULL;
					} break;
				case ProtocolIE_ID_id_S_TMSI:
					{
			            S_TMSI_t*	 s1apStmsi_p = NULL;;
                        if(InitialUEMessage_IEs__value_PR_S_TMSI == ie_p->value.present)
                        {
						    s1apStmsi_p = &ie_p->value.choice.S_TMSI;
                        }
						
                        if (s1apStmsi_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE STMSI failed\n");
							return -1;
						}

                        //struct STMSI     s_tmsi
                        proto_ies->data[i].IE_type = S1AP_IE_S_TMSI; 
						memcpy(&proto_ies->data[i].val.s_tmsi.mme_code, 
                               s1apStmsi_p->mMEC.buf, sizeof(uint8_t));
						memcpy(&proto_ies->data[i].val.s_tmsi.m_TMSI, 
                                s1apStmsi_p->m_TMSI.buf, sizeof(uint32_t));
						s1apStmsi_p = NULL;
					} break;
                default:
                    {
                        log_msg(LOG_WARNING, "Unhandled IE %d in initial UE message ", ie_p->id);
                    }
			}
		}
     }

    return 0;
}

static int
init_ue_msg_handler(InitiatingMessage_t *msg, int enb_fd)
{
	//TODO: use static instead of dynamic for perf.
	struct proto_IE proto_ies;
	
	log_msg(LOG_INFO, "S1AP_INITIAL_UE_MSG msg: \n");

    /* TODO : Error handling. Bad message will lead crash. 
     * Preferably reject the message, increment stats.
     */
	int decode_result = convertToInitUeProtoIe(msg, &proto_ies);
    if(decode_result < 0 )
    {
	  log_msg(LOG_ERROR, "S1ap message decode failed. Dropping message");
      return E_FAIL;
    }

	/*Check nas message type*/
	//TODO: check through all proto IEs for which is nas
	//currentlyy hard coding to 2 looking at packets
	log_msg(LOG_INFO, "NAS msg type parsed = %x\n", proto_ies.data[1].val.nas.header.message_type);
	switch(proto_ies.data[1].val.nas.header.message_type) {
	case NAS_ATTACH_REQUEST:
		s1_init_ue_handler(&proto_ies, enb_fd);
		break;

	case NAS_SERVICE_REQUEST:
		s1_init_ue_service_req_handler(&proto_ies, enb_fd);
		break;

	case NAS_DETACH_REQUEST:
		detach_stage1_handler(&proto_ies, true);
		break;
    case NAS_TAU_REQUEST:
        s1_tau_request_handler(&proto_ies, enb_fd);
        break;
	}

	free(proto_ies.data);
	//TODO: free IEs
	return SUCCESS;
}

static int
UL_NAS_msg_handler(InitiatingMessage_t *msg, int enb_fd)
{
	//TODO: use static instead of synamic for perf.
	struct proto_IE proto_ies;

	log_msg(LOG_INFO, "S1AP_UL_NAS_TX_MSG msg \n");

    convertUplinkNasToProtoIe(msg, &proto_ies);

	/*Check nas message type*/
	//TODO: check through all proto IEs for which is nas
	//currentlyy hard coding to 2 looking at packets
	log_msg(LOG_INFO, "NAS msg type = %x\n", proto_ies.data[2].val.nas.header.message_type);
	switch(proto_ies.data[2].val.nas.header.message_type) {
	case NAS_AUTH_RESP:
		s1_auth_resp_handler(&proto_ies);
		break;

	case NAS_AUTH_FAILURE:
		s1_auth_fail_handler(&proto_ies);
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

    case NAS_IDENTITY_RESPONSE:
        s1_identity_resp_handler(&proto_ies);
        break;
    case NAS_TAU_REQUEST:
        s1_tau_request_handler(&proto_ies, enb_fd);
        break;
	}

	//TODO: free IEs
	free(proto_ies.data);
	return SUCCESS;
}

/* Make Sure msg is freed at the end of the message procesing. 
 */
void
handle_s1ap_message(void *msg)
{
    log_msg(LOG_INFO, "Inside handle_s1ap_message.\n");
    /*convert message from network to host*/

    /*Call handler for the procedure code. TBD: Tasks pool for handlers*/

    int enb_fd = 0;
    int msg_size = 0;
    memcpy(&enb_fd, msg, sizeof(int));
    memcpy(&msg_size, msg + sizeof(int), sizeof(int));
    char *message = ((char *) msg) + 2*sizeof(int);
    S1AP_PDU_t                              pdu = {(S1AP_PDU_PR_NOTHING)};
    S1AP_PDU_t                             *pdu_p = &pdu;
    asn_dec_rval_t                          dec_ret = {(RC_OK)};
    memset ((void *)pdu_p, 0, sizeof (S1AP_PDU_t));
    dec_ret = aper_decode (NULL, &asn_DEF_S1AP_PDU, (void **)&pdu_p, message, msg_size, 0, 0);

    if (dec_ret.code != RC_OK) {
            log_msg(LOG_ERROR, "ASN Decode PDU Failed\n");
            free(msg);
            return;
    }

    switch (pdu_p->present) {
            case S1AP_PDU_PR_initiatingMessage:
                    s1ap_mme_decode_initiating (pdu_p->choice.initiatingMessage, enb_fd);
                    break;
            case S1AP_PDU_PR_successfulOutcome:
                    s1ap_mme_decode_successfull_outcome (pdu_p->choice.successfulOutcome);
                    break;
            case S1AP_PDU_PR_unsuccessfulOutcome:
                    s1ap_mme_decode_unsuccessfull_outcome (pdu_p->choice.unsuccessfulOutcome);
                    break;
            default:
                    log_msg(LOG_WARNING, "Unknown message outcome (%d) or not implemented", (int)pdu_p->present);
                    break;
    }
    free(msg);
    return;
}

int
s1ap_mme_decode_successfull_outcome (SuccessfulOutcome_t* msg)
{
    log_msg(LOG_DEBUG,"successful outcome decode :");
    log_msg(LOG_INFO, "proc code %d\n", msg->procedureCode);
    switch (msg->procedureCode) {

	case S1AP_INITIAL_CTX_RESP_CODE:
		s1_init_ctx_resp_handler(msg);
		break;
	case S1AP_UE_CTX_RELEASE_CODE:
		s1_ctx_release_resp_handler(msg);
		break;
	default:
		log_msg(LOG_ERROR, "Unknown procedure code - %d\n",
		         msg->procedureCode & 0x00FF);
		break;
	}
	
	return 0;
}

int
s1ap_mme_decode_unsuccessfull_outcome (UnsuccessfulOutcome_t *msg)
{
    log_msg(LOG_DEBUG,"unsuccessful outcome decode : TBD");
    return 0;
}

int
s1ap_mme_decode_initiating (InitiatingMessage_t *initiating_p, int enb_fd) 
{
  log_msg(LOG_INFO, "proc code %d\n", initiating_p->procedureCode);
  switch (initiating_p->procedureCode) {

	case S1AP_SETUP_REQUEST_CODE:
		s1_setup_handler(initiating_p, enb_fd);
		break;

	case S1AP_INITIAL_UE_MSG_CODE:
		init_ue_msg_handler(initiating_p, enb_fd);
		break;

	case S1AP_UL_NAS_TX_MSG_CODE:
		UL_NAS_msg_handler(initiating_p, enb_fd);
		break;

	case S1AP_UE_CTX_RELEASE_REQ_CODE:
		s1_ctx_release_req_handler(initiating_p);
		break;

	default:
		log_msg(LOG_ERROR, "Unknown procedure code - %d\n",
			initiating_p->procedureCode & 0x00FF);
		break;
	}
	
  //free(msg);
	return 0;

}

int convertUplinkNasToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies)
{
    proto_ies->procedureCode = msg->procedureCode;
    proto_ies->criticality = msg->criticality;
	int no_of_IEs = 0;

    if(msg->value.present == InitiatingMessage__value_PR_UplinkNASTransport)
    {
        ProtocolIE_Container_129P33_t* protocolIes = &msg->value.choice.UplinkNASTransport.protocolIEs;
        no_of_IEs = protocolIes->list.count;
        proto_ies->no_of_IEs = no_of_IEs;

        log_msg(LOG_INFO, "No of IEs = %d\n", no_of_IEs);
        proto_ies->data = calloc(sizeof(struct proto_IE_data), no_of_IEs);
        if(proto_ies->data == NULL)
        {
            log_msg(LOG_ERROR,"Malloc failed for protocol IE.");
            return -1;
        }
		for (int i = 0; i < protocolIes->list.count; i++) {
			UplinkNASTransport_IEs_t *ie_p;
			ie_p = protocolIes->list.array[i];
			switch(ie_p->id) {
				case ProtocolIE_ID_id_eNB_UE_S1AP_ID:
					{
                        ENB_UE_S1AP_ID_t *s1apENBUES1APID_p = NULL;
                        if(UplinkNASTransport_IEs__value_PR_ENB_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apENBUES1APID_p = &ie_p->value.choice.ENB_UE_S1AP_ID;
                        }
						
                        if (s1apENBUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE eNB_UE_S1AP_ID failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_ENB_UE_ID; 
						memcpy(&proto_ies->data[i].val.enb_ue_s1ap_id, s1apENBUES1APID_p, sizeof(ENB_UE_S1AP_ID_t));
					} break;
				case ProtocolIE_ID_id_MME_UE_S1AP_ID:
					{
                        MME_UE_S1AP_ID_t *s1apMMEUES1APID_p = NULL;
                        if(UplinkNASTransport_IEs__value_PR_MME_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apMMEUES1APID_p = &ie_p->value.choice.MME_UE_S1AP_ID;
                        }
						
                        if (s1apMMEUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE MME_UE_S1AP_ID failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_MME_UE_ID; 
						memcpy(&proto_ies->data[i].val.mme_ue_s1ap_id, s1apMMEUES1APID_p, sizeof(MME_UE_S1AP_ID_t));
					} break;
				case ProtocolIE_ID_id_NAS_PDU:
					{
                        NAS_PDU_t *s1apNASPDU_p = NULL;
                        if(UplinkNASTransport_IEs__value_PR_NAS_PDU == ie_p->value.present)
                        {
						    s1apNASPDU_p = &ie_p->value.choice.NAS_PDU;
                        }
						
                        if (s1apNASPDU_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE NAS PDU failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_NAS_PDU; 
                        parse_nas_pdu((char*)s1apNASPDU_p->buf, s1apNASPDU_p->size, 
                                       &proto_ies->data[i].val.nas, msg->procedureCode);
					} break;
				case ProtocolIE_ID_id_TAI:
					{
                        TAI_t *s1apTAI_p = NULL;
                        if(UplinkNASTransport_IEs__value_PR_TAI == ie_p->value.present)
                        {
						    s1apTAI_p = &ie_p->value.choice.TAI;
                        }
						
                        if (s1apTAI_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE TAI failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_TAI; 
						memcpy(&proto_ies->data[i].val.tai.tac, s1apTAI_p->tAC.buf, s1apTAI_p->tAC.size);
						memcpy(proto_ies->data[i].val.tai.plmn_id.idx, 
                                s1apTAI_p->pLMNidentity.buf, s1apTAI_p->pLMNidentity.size);
					} break;
				case ProtocolIE_ID_id_EUTRAN_CGI:
					{
			            EUTRAN_CGI_t*	 s1apCGI_p = NULL;;
                        if(UplinkNASTransport_IEs__value_PR_EUTRAN_CGI == ie_p->value.present)
                        {
						    s1apCGI_p = &ie_p->value.choice.EUTRAN_CGI;
                        }
						
                        if (s1apCGI_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE CGI failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_UTRAN_CGI; 
						memcpy(&proto_ies->data[i].val.utran_cgi.cell_id, 
                               s1apCGI_p->cell_ID.buf, s1apCGI_p->cell_ID.size);
						memcpy(proto_ies->data[i].val.utran_cgi.plmn_id.idx, 
                                s1apCGI_p->pLMNidentity.buf, s1apCGI_p->pLMNidentity.size);
					} break;
                default:
                    {
                        log_msg(LOG_WARNING, "Unhandled IE %d", ie_p->id);
                    }
			}
		}
     }

    return 0;
}

int convertInitCtxRspToProtoIe(SuccessfulOutcome_t *msg, struct proto_IE* proto_ies)
{
    proto_ies->procedureCode = msg->procedureCode;
    proto_ies->criticality = msg->criticality;
    int no_of_IEs = 0;

    if(msg->value.present == SuccessfulOutcome__value_PR_InitialContextSetupResponse)
    {
        ProtocolIE_Container_129P20_t* protocolIes 
            = &msg->value.choice.InitialContextSetupResponse.protocolIEs;
        no_of_IEs = protocolIes->list.count;
        proto_ies->no_of_IEs = no_of_IEs;

        log_msg(LOG_INFO, "No of IEs = %d\n", no_of_IEs);
        proto_ies->data = calloc(sizeof(struct proto_IE_data), no_of_IEs);
        if(proto_ies->data == NULL)
        {
            log_msg(LOG_ERROR,"Malloc failed for protocol IE.");
            return -1;
        }
		for (int i = 0; i < protocolIes->list.count; i++) {
			InitialContextSetupResponseIEs_t *ie_p;
			ie_p = protocolIes->list.array[i];
			switch(ie_p->id) {
				case ProtocolIE_ID_id_eNB_UE_S1AP_ID:
					{
                        ENB_UE_S1AP_ID_t *s1apENBUES1APID_p = NULL;
                        if(InitialContextSetupResponseIEs__value_PR_ENB_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apENBUES1APID_p = &ie_p->value.choice.ENB_UE_S1AP_ID;
                        }
						
                        if (s1apENBUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE eNB_UE_S1AP_ID failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_ENB_UE_ID; 
						memcpy(&proto_ies->data[i].val.enb_ue_s1ap_id, s1apENBUES1APID_p, sizeof(ENB_UE_S1AP_ID_t));
						s1apENBUES1APID_p = NULL;
					} break;
				case ProtocolIE_ID_id_MME_UE_S1AP_ID:
					{
                        MME_UE_S1AP_ID_t *s1apMMEUES1APID_p = NULL;
                        if(InitialContextSetupResponseIEs__value_PR_MME_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apMMEUES1APID_p = &ie_p->value.choice.MME_UE_S1AP_ID;
                        }
						
                        if (s1apMMEUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE MME_UE_S1AP_ID failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_MME_UE_ID; 
						memcpy(&proto_ies->data[i].val.mme_ue_s1ap_id, s1apMMEUES1APID_p, sizeof(MME_UE_S1AP_ID_t));
						s1apMMEUES1APID_p = NULL;
					} break;
				case ProtocolIE_ID_id_E_RABSetupListCtxtSURes:
					{
                        E_RABSetupListCtxtSURes_t *s1apErabSetupList_p = NULL;
                        if(InitialContextSetupResponseIEs__value_PR_E_RABSetupListCtxtSURes == ie_p->value.present)
                        {
						    s1apErabSetupList_p = &ie_p->value.choice.E_RABSetupListCtxtSURes;
                        }
						
                        if (s1apErabSetupList_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE s1apErabSetupList failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_ERAB_SETUP_CTX_SUR;
                        proto_ies->data[i].val.erab.no_of_elements = s1apErabSetupList_p->list.count;
                        proto_ies->data[i].val.erab.elements = calloc(sizeof(union eRAB_IE), 
                                                                    s1apErabSetupList_p->list.count);
                        if(proto_ies->data[i].val.erab.elements == NULL)
                        {
                            log_msg(LOG_ERROR,"Malloc failed for protocol IE: Erab elements.");
                            break;;
                        }
                        for (int j = 0; 
                             j < s1apErabSetupList_p->list.count; j++) 
                        {
                            E_RABSetupItemCtxtSUResIEs_t *ie_p;
                            ie_p = (E_RABSetupItemCtxtSUResIEs_t*)s1apErabSetupList_p->list.array[j];
                            switch(ie_p->id) {
                                case ProtocolIE_ID_id_E_RABSetupItemCtxtSURes:
                                    {
                                        E_RABSetupItemCtxtSURes_t* s1apErabSetupItem_p = NULL;
                                        if(E_RABSetupItemCtxtSUResIEs__value_PR_E_RABSetupItemCtxtSURes == ie_p->value.present)
                                        {
                                            s1apErabSetupItem_p = &ie_p->value.choice.E_RABSetupItemCtxtSURes;
                                        }

                                        if (s1apErabSetupItem_p == NULL) {
                                            log_msg (LOG_ERROR, "Decoding of IE s1apErabSetupItem failed\n");
                                            return -1;
                                        }

                                        proto_ies->data[i].val.erab.elements[j].su_res.eRAB_id 
                                                 = (unsigned short)s1apErabSetupItem_p->e_RAB_ID;
                                        memcpy(
                                            &(proto_ies->data[i].val.erab.elements[j].su_res.gtp_teid),
                                            s1apErabSetupItem_p->gTP_TEID.buf,
                                            s1apErabSetupItem_p->gTP_TEID.size);
                                        proto_ies->data[i].val.erab.elements[j].su_res.gtp_teid
                                            = ntohl(proto_ies->data[i].val.erab.elements[j].su_res.gtp_teid);

                                        memcpy(
                                           &(proto_ies->data[i].val.erab.elements[j].su_res.transp_layer_addr),
                                            s1apErabSetupItem_p->transportLayerAddress.buf,
                                            s1apErabSetupItem_p->transportLayerAddress.size);
                                        proto_ies->data[i].val.erab.elements[j].su_res.transp_layer_addr
                                            = ntohl(proto_ies->data[i].val.erab.elements[j].su_res.transp_layer_addr);
                                        s1apErabSetupItem_p = NULL;
                                    }break;
                                default:
                                    {
                                        log_msg(LOG_WARNING, "Unhandled List item %d", ie_p->id);
                                    }
                            }
                        }

						s1apErabSetupList_p = NULL;
					} break;
                default:
                    {
                        log_msg(LOG_WARNING, "Unhandled IE %d", ie_p->id);
                    }
			}
		}
     }

    return 0;
}

int convertUeCtxRelComplToProtoIe(SuccessfulOutcome_t *msg, struct proto_IE* proto_ies)
{
    proto_ies->procedureCode = msg->procedureCode;
    proto_ies->criticality = msg->criticality;
	int no_of_IEs = 0;

    if(msg->value.present == SuccessfulOutcome__value_PR_UEContextReleaseComplete)
    {
        ProtocolIE_Container_129P25_t* protocolIes 
            = &msg->value.choice.UEContextReleaseComplete.protocolIEs;
        no_of_IEs = protocolIes->list.count;
        proto_ies->no_of_IEs = no_of_IEs;

        log_msg(LOG_INFO, "No of IEs = %d\n", no_of_IEs);
        proto_ies->data = calloc(sizeof(struct proto_IE_data), no_of_IEs);
        if(proto_ies->data == NULL)
        {
            log_msg(LOG_ERROR,"Malloc failed for protocol IE.");
            return -1;
        }
		for (int i = 0; i < protocolIes->list.count; i++) {
			UEContextReleaseComplete_IEs_t *ie_p;
			ie_p = protocolIes->list.array[i];
			switch(ie_p->id) {
				case ProtocolIE_ID_id_eNB_UE_S1AP_ID:
					{
                        ENB_UE_S1AP_ID_t *s1apENBUES1APID_p = NULL;
                        if(UEContextReleaseComplete_IEs__value_PR_ENB_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apENBUES1APID_p = &ie_p->value.choice.ENB_UE_S1AP_ID;
                        }
						
                        if (s1apENBUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE eNB_UE_S1AP_ID failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_ENB_UE_ID; 
						memcpy(&proto_ies->data[i].val.enb_ue_s1ap_id, s1apENBUES1APID_p, sizeof(ENB_UE_S1AP_ID_t));
						s1apENBUES1APID_p = NULL;
					} break;
				case ProtocolIE_ID_id_MME_UE_S1AP_ID:
					{
                        MME_UE_S1AP_ID_t *s1apMMEUES1APID_p = NULL;
                        if(UEContextReleaseComplete_IEs__value_PR_MME_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apMMEUES1APID_p = &ie_p->value.choice.MME_UE_S1AP_ID;
                        }
						
                        if (s1apMMEUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE MME_UE_S1AP_ID failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_MME_UE_ID; 
						memcpy(&proto_ies->data[i].val.mme_ue_s1ap_id, s1apMMEUES1APID_p, sizeof(MME_UE_S1AP_ID_t));
						s1apMMEUES1APID_p = NULL;
					} break;
                default:
                    {
                        log_msg(LOG_WARNING, "Unhandled IE %d\n", ie_p->id);
                    }
			}
		}
     }

    return 0;
}

int convertUeCtxRelReqToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies)
{
    proto_ies->procedureCode = msg->procedureCode;
    proto_ies->criticality = msg->criticality;
	int no_of_IEs = 0;

    if(msg->value.present == InitiatingMessage__value_PR_UEContextReleaseRequest)
    {
        ProtocolIE_Container_129P23_t* protocolIes 
            = &msg->value.choice.UEContextReleaseRequest.protocolIEs;
        no_of_IEs = protocolIes->list.count;
        proto_ies->no_of_IEs = no_of_IEs;

        log_msg(LOG_INFO, "No of IEs = %d\n", no_of_IEs);
        proto_ies->data = calloc(sizeof(struct proto_IE_data), no_of_IEs);
        if(proto_ies->data == NULL)
        {
            log_msg(LOG_ERROR,"Malloc failed for protocol IE.");
            return -1;
        }
		for (int i = 0; i < protocolIes->list.count; i++) {
			UEContextReleaseRequest_IEs_t *ie_p;
			ie_p = protocolIes->list.array[i];
			switch(ie_p->id) {
				case ProtocolIE_ID_id_eNB_UE_S1AP_ID:
					{
                        ENB_UE_S1AP_ID_t *s1apENBUES1APID_p = NULL;
                        if(UEContextReleaseRequest_IEs__value_PR_ENB_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apENBUES1APID_p = &ie_p->value.choice.ENB_UE_S1AP_ID;
                        }
						
                        if (s1apENBUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE eNB_UE_S1AP_ID failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_ENB_UE_ID; 
						memcpy(&proto_ies->data[i].val.enb_ue_s1ap_id, s1apENBUES1APID_p, sizeof(ENB_UE_S1AP_ID_t));
						s1apENBUES1APID_p = NULL;
					} break;
				case ProtocolIE_ID_id_MME_UE_S1AP_ID:
					{
                        MME_UE_S1AP_ID_t *s1apMMEUES1APID_p = NULL;
                        if(UEContextReleaseRequest_IEs__value_PR_MME_UE_S1AP_ID == ie_p->value.present)
                        {
						    s1apMMEUES1APID_p = &ie_p->value.choice.MME_UE_S1AP_ID;
                        }
						
                        if (s1apMMEUES1APID_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE MME_UE_S1AP_ID failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_MME_UE_ID; 
						memcpy(&proto_ies->data[i].val.mme_ue_s1ap_id, s1apMMEUES1APID_p, sizeof(MME_UE_S1AP_ID_t));
						s1apMMEUES1APID_p = NULL;
					} break;
				case ProtocolIE_ID_id_Cause:
					{
                        Cause_t *s1apCause_p = NULL;
                        if(UEContextReleaseRequest_IEs__value_PR_Cause == ie_p->value.present)
                        {
						    s1apCause_p = &ie_p->value.choice.Cause;
                        }
						
                        if (s1apCause_p == NULL) {
							log_msg (LOG_ERROR, "Decoding of IE Cause failed\n");
							return -1;
						}

                        proto_ies->data[i].IE_type = S1AP_IE_CAUSE;
                        proto_ies->data[i].val.cause.present = s1apCause_p->present;
                        switch(s1apCause_p->present)
                        {
                            case Cause_PR_radioNetwork:
							    log_msg (LOG_DEBUG, "RadioNetwork case : %d\n",
                                          s1apCause_p->choice.radioNetwork);
                                proto_ies->data[i].val.cause.choice.radioNetwork
                                    = s1apCause_p->choice.radioNetwork;
                                break;
                            case Cause_PR_transport:
							    log_msg (LOG_DEBUG, "Transport case : %d\n",
                                          s1apCause_p->choice.transport);
                                proto_ies->data[i].val.cause.choice.transport
                                    = s1apCause_p->choice.transport;
                                break;
                            case Cause_PR_nas:
							    log_msg (LOG_DEBUG, "Nas case : %d\n",
                                          s1apCause_p->choice.nas);
                                proto_ies->data[i].val.cause.choice.nas
                                    = s1apCause_p->choice.nas;
                                break;
                            case Cause_PR_protocol:
							    log_msg (LOG_DEBUG, "Protocol case : %d\n",
                                          s1apCause_p->choice.protocol);
                                proto_ies->data[i].val.cause.choice.protocol
                                    = s1apCause_p->choice.protocol;
                                break;
                            case Cause_PR_misc:
							    log_msg (LOG_DEBUG, "Misc case : %d\n",
                                          s1apCause_p->choice.misc);
                                proto_ies->data[i].val.cause.choice.misc
                                    = s1apCause_p->choice.misc;
                                break;
                            case Cause_PR_NOTHING:
                            default:
                                log_msg(LOG_WARNING, "Unknown cause %d\n", s1apCause_p->present);

                        }
						s1apCause_p = NULL;
					} break;
                default:
                    {
                        log_msg(LOG_WARNING, "Unhandled IE %d\n", ie_p->id);
                    }
			}
		}
     }

    return 0;
}
