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

// msg points to start of ASN encoded NAS payload

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
                // msg is pointing to NAS payload..NAS payload starts with length at msg[0]
		unsigned char header_type;
		unsigned char sec_type;
		memcpy(&header_type, msg + 1, 1);
		log_msg(LOG_INFO, "%s : header_type = %x \n", __FUNCTION__, header_type);
		sec_type = header_type << 4;
		header_type >>= 4; // Security header type
		log_msg(LOG_INFO, "%s : bit shifting header_type = %d \n", __FUNCTION__, header_type);
		log_msg(LOG_INFO, "%s : bit shifting sec type  = %d \n", __FUNCTION__, sec_type);
		if(0 == header_type) { /*not security header*/
                        // IMSI attach message would land here 

			log_msg(LOG_INFO, "No security header\n");
			memcpy(&(nas->header), msg+1, sizeof(nas_pdu_header));/*copy only till msg type*/
                        offset = 4;
		} else {
			log_msg(LOG_INFO, "Security header\n");
			/*now for esm resp, there is procedure tx identity, why the hell it was not there before.*/
			/*one more donkey logic, do something!!*/
			 #if 0
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
			} else 
                        #endif 
                        {
				unsigned char tmp;
				memcpy(&(tmp), msg+7, 1);/*copy only till msg type*/
				nas->header.security_header_type = tmp;

				memcpy(&(nas->header.message_type), msg+8, 1);/*copy only till msg type*/

				offset = 10; // Now offset is at length  of identity IE
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
		log_msg(LOG_INFO, "Auth Response recvd\n");
		nas->elements_len = 1;
		nas->elements = calloc(sizeof(nas_pdu_elements), 5);
		//if(NULL == nas.elements)...
		memcpy(&(nas->elements[0].auth_resp), msg + 3, sizeof(struct XRES));

		break;

	case NAS_ATTACH_REQUEST:{
		log_msg(LOG_INFO, "NAS Attach Request Rcvd\n");
		nas->elements_len = 6; // Fix this hardcoding
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
//		memcpy(&(nas->elements[0].IMSI), msg+5, BINARY_IMSI_LEN);
//		offset = 5 + BINARY_IMSI_LEN ;
		log_msg(LOG_INFO, "NAS Attach Request Rcvd : offset %d\n",offset);
		log_msg(LOG_INFO, "NAS Attach Request Rcvd content at offset %x\n",msg[offset]);

                // First see if this is IMSI or imei or GUTI and decode it appropriately
                unsigned char id_len = msg[offset];
                offset++;
                bool odd = msg[offset] & 0x08; // if this bit is set then odd number of digits in identity
                if((msg[offset] & 0x07) == 0x01) {
                  // Mobile Identity contains imsi
                  // Support for 14 digit IMSIs is missing 
                 /*Code working with sprirent and Polaris*/
                 memcpy(&(nas->elements[0].IMSI), &msg[offset], BINARY_IMSI_LEN);
                  nas->flags |= NAS_MSG_UE_IE_IMSI;
	 log_msg(LOG_INFO, "Create UE record for IMSI %x %x %x %x %x %x %x %x \n", nas->elements[0].IMSI[0], nas->elements[0].IMSI[1], nas->elements[0].IMSI[2],nas->elements[0].IMSI[3],nas->elements[0].IMSI[4],nas->elements[0].IMSI[5],nas->elements[0].IMSI[6],nas->elements[0].IMSI[7]);
                } else if ((msg[offset] & 0x07) == 0x06) { 
		  log_msg(LOG_INFO, "NAS Attach Request Rcvd ID 1: GUTI\n");
                  // Mobile Identity contains GUTI
                  // MCC+MNC offset = 3
                  // MME Group Id   = 2
                  // MME Code       = 1
                  // MTMSI offset from start of this AVP = 3 + 2 + 1 

                  memcpy(&nas->elements[0].mi_guti.plmn_id.idx, &msg[offset+1], 3);
                  nas->elements[0].mi_guti.mme_grp_id = ntohs(*(short int *)(&msg[offset+4]));

                  nas->elements[0].mi_guti.mme_code = msg[offset+6];

                  nas->elements[0].mi_guti.m_TMSI = ntohl(*((unsigned int *)(&msg[offset+7])));

		  log_msg(LOG_INFO, "NAS Attach Request Rcvd ID: GUTI. PLMN id %d %d %d \n", nas->elements[0].mi_guti.plmn_id.idx[0], nas->elements[0].mi_guti.plmn_id.idx[1], nas->elements[0].mi_guti.plmn_id.idx[2] );
		  log_msg(LOG_INFO, "NAS Attach Request Rcvd ID: GUTI. mme group id = %d, MME code %d  mtmsi = %d\n", nas->elements[0].mi_guti.mme_grp_id, nas->elements[0].mi_guti.mme_code, nas->elements[0].mi_guti.m_TMSI);
                  nas->flags |= NAS_MSG_UE_IE_GUTI;
                } else if ((msg[offset] & 0x07) == 0x03) { 
                  // Mobile Identity contains imei
                }
                offset += id_len;

		/*UE network capacity*/
		nas->elements[1].ue_network.len = msg[offset];
		++offset;
		log_msg(LOG_INFO, "NAS Attach Request Rcvd : offset %d\n",offset);

		memcpy((nas->elements[1].ue_network.capab), msg+offset,
			nas->elements[1].ue_network.len);

		offset += nas->elements[1].ue_network.len;
		log_msg(LOG_INFO, "NAS Attach Request Rcvd : offset %d\n",offset);

		/*ESM msg container*/
		{
		  unsigned short len = 0;  
	          memcpy(&len, msg+offset, 2);
	          len = ntohs(len);
                 // offset += 2;

                  //offset +=1; // skipping reading EBI & PD

		  nas->elements[5].pti = msg[offset+3];
                  //offset +=1;

		  unsigned char val = *(msg+offset+6);
  		  /*ESM message header len is 4: bearer_id_flags(1)+proc_tx_id(1)+msg_id(1)
		   * +pdn_type(1)*/
		  /*element id 13(1101....) = "esm required" flag*/
		  nas->elements[2].esm_info_tx_required = false;
		  if(13 == (val>>4)) {
		  	//nas->elements[2].esm_info_tx_required = true; // seems no need to have this line of code
		  	if(val & 1) {
		  		nas->elements[2].esm_info_tx_required = true;
                                log_msg(LOG_INFO, "NAS Attach Request ESM infor request required 1");
		  	}
                        log_msg(LOG_INFO, "NAS Attach Request ESM infor request required 2");
		  }
		  else 
                  {
                    log_msg(LOG_INFO, "NAS Attach Request ESM infor request not required");
                  } 
		  offset += len + 2;
		  log_msg(LOG_INFO, "NAS Attach Request Rcvd : offset %d\n",offset);
		}

                /*optional AVPs we need to go through to read required things..
                  We cant assume any data there...
                  */
		log_msg(LOG_INFO, "NAS Attach Request. Length %d and offset = %d \n", nas_msg_len, offset);
                while(offset < nas_msg_len)
                {
                  unsigned char iei = msg[offset];
		  log_msg(LOG_INFO, "NAS Attach Request - Current offset %d IEI %d \n", offset, iei);
                  // Old-PTMSI Signature - 			TV  Length -4 , 
                  // additional GUTI. 				TLV Length 13 , 
                  // last visited registered TAI - 		TV  Length 6, Type-3
                  // DRX param - 				TV  Length - 3, 
                  // MS network capability. 			TLV Length - 4-10
                  // old location area identification           TV  Length - 6
                  // TMSI status                                TV  Length - 1
                  // mobile station classmark 2                 TLV Length - 5
                  // mobile station classmasrk 3                TLV Length - 2-34
                  // Supported codecs                           TLV Length - 5-N
                  // additional update type                     TV  Length - 1, Type - F-
                  // voice domain pref and UEs usage setting    TLV Length - 3
                  // Device property                            TV  Length - 1  Type - D-
                  // Old GUTI type                              TV  Length - 1  Type - E-
                  // MS network feature support                 TV  Length - 1  Type - C-
                  // TMSI based NRI container                   TLV Length - 4
                  // T3324 value                                TLV Length - 3
                  // T3412 extended value                       TLV Length - 3
                  // extended DRX parameters                    TLV Length - 3
                  // UE additional security capability          TLV Length - 6 
                  // UE status                                  TLV Length - 3
                  // Additional information requested           TV  Length - 2
                  // N1 UE network capability                   TLV Length - 3-15
                  if(((iei & 0xf0) == 0xf0) || ((iei & 0xf0) == 0xe0)|| ((iei & 0xf0) == 0xd0) || ((iei & 0xf0) == 0xc0)||((iei & 0xf0) == 0x90))
                  {
                    //type-1, TV within 1 byte
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d \n", iei & 0xf0);
                    offset += 1;
                  }
                  else if ( iei == 0x19)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, PTMSI signature \n", iei);
                    offset += 4;
                  } 
                  else if ( iei == 0x50)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, addtional guti \n", iei);
                    unsigned char len = msg[offset+1];
                    offset += len + 1;
                  }                  
                  else if ( iei == 0x52)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, last visited registered tai \n", iei);
                    offset += 6;
                  }
                  else if ( iei == 0x5c)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, DRX param \n", iei);
                    offset += 3;
                  }
                  else if ( iei == 0x31)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, MS network capability \n", iei);
                    unsigned char len=msg[offset+1];
		    nas->elements[4].ms_network.element_id = iei; 
		    nas->elements[4].ms_network.len = len; 
		    memcpy((nas->elements[4].ms_network.capab), msg+offset+2,
			nas->elements[4].ms_network.len);
                    offset += len;
                  }                  
                  else if ( iei == 0x13)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, old location area identification \n", iei);
                    offset += 6;
                  }
                  else if ( iei == 0x11)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, mobile station classmark 2  \n", iei);
                    offset += 5;
                  }
                  else if ( iei == 0x20)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, mobile station classmark 3 \n", iei);
                    unsigned char len=msg[offset+1];
                    offset += len;
                  }
                  else if ( iei == 0x40)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, supported codecs \n", iei);
                    unsigned char len=msg[offset+1];
                    offset += len;
                  }
                  else if ( iei == 0x5D)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, voice domain preference \n", iei);
                    offset += 3;
                  }
                  else if ( iei == 0x10)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, TMSI based NRI container \n", iei);
                    offset += 4;
                  }
                  else if ( iei == 0x6A)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, T3324 timer \n", iei);
                    offset += 3;
                  }
                  else if ( iei == 0x5E)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, T3412 timer \n", iei);
                    offset += 3;
                  }
                  else if ( iei == 0x6E)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, extended DRX parameters \n", iei);
                    offset += 3;
                  }
                  else if ( iei == 0x17)
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - IEI %d, additional info req \n", iei);
                    offset += 2;
                  }
                  else
                  {
		    log_msg(LOG_INFO, "NAS Attach Request - unknown \n");
                    sleep(1000);
                    
                  }
                } 
                #if 0 
		/*DRX parameter*/
		offset += 3; // DRX is just 3 bytes..1 byte type and 2 byte data 

          
		/*MS network capability*/
		nas->elements[4].ms_network.element_id = msg[offset];
		++offset;
		nas->elements[4].ms_network.len = msg[offset];
		++offset;
		memcpy((nas->elements[4].ms_network.capab), msg+offset,
			nas->elements[4].ms_network.len);
                #endif

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

// msg points to length 
int
parse_IEs(char *msg, struct proto_IE *proto_ies, unsigned short proc_code)
{
	unsigned short int no_of_IEs=0;

	short data_size=0;

        // now we are pointing to length
        if((msg[0] & 0x80) == 0x80)
        {
	  memcpy(&data_size, msg, 2);
          msg +=2; // 2 byte length 
          data_size = ntohs(data_size);
        }
        else
        { 
	  memcpy(&data_size, msg, 1);
          msg +=1; // 1 byte length 
        }

        msg +=1; // 1 extension byte 

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
		memcpy(&IE_data_len, msg, sizeof(char));
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
                        // decode_int_val looks hacky...its assuming that length 2 means only 1 byte has data

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
        //extenstion + Proc Code + Criticality 
	parse_IEs(msg+3, &proto_ies, S1AP_INITIAL_UE_MSG_CODE);

	/*Check nas message type*/
	//TODO: check through all proto IEs for which is nas
	//currentlyy hard coding to 2 looking at packets
	log_msg(LOG_INFO, "NAS msg type = %x\n", proto_ies.data[1].nas.header.message_type);
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
