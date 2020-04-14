/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "err_codes.h"
#include "options.h"
#include "ipc_api.h"
#include "main.h"
#include "s1ap.h"
#include "s1ap_config.h"
#include "sctp_conn.h"
#include "s1ap_structs.h"
#include "s1ap_msg_codes.h"
#include "ProtocolIE-ID.h"
#include "ProtocolIE-Field.h"
#include "SupportedTAs-Item.h"
#include "TAC.h"
#include "structs.h"
#include "s1apContextWrapper_c.h"

extern int g_enb_fd;
static struct Buffer resp_buf;

static int
create_s1setup_response(/*enb info,*/unsigned char **s1_setup_resp, struct PLMN *plmn)
{
	unsigned char data_len = 0;
	unsigned char msg[50];
	struct Buffer proto_ies;
	struct Buffer gummies;
	uint16_t proto_ie_id;
	unsigned char tmp_str[4];
	uint8_t criticality;
	s1ap_config_t *s1ap_cfg = get_s1ap_config();

	proto_ies.pos = 0;
	gummies.pos = 0;
	/*Leave a byte to fill length*/
	resp_buf.pos = 0;
	/*Only in case of s1setup resp, first byte is 0x20, not for any other
	s1ap message. Nothing found in specs, please check.*/
	/**procedureCode: id-S1Setup (17)**/
	msg[0] = 0x20;
	msg[1] = S1AP_SETUP_REQUEST_CODE;
	msg[2] = CRITICALITY_REJECT;
	buffer_copy(&resp_buf, msg, 3);

	/**IE1*/
	/**Item 0: id-MMEname*/
	proto_ie_id = S1AP_IE_MMENAME;
	copyU16(tmp_str, proto_ie_id);
	buffer_copy(&proto_ies, tmp_str, sizeof(proto_ie_id));
	criticality = CRITICALITY_IGNORE;
	buffer_copy(&proto_ies, &criticality, sizeof(criticality));

	data_len = strlen(s1ap_cfg->mme_name);
	data_len = copyU16(tmp_str, data_len);
	tmp_str[1] = tmp_str[1]+2;
	buffer_copy(&proto_ies, &tmp_str[1], 1);
	proto_ies.buf[proto_ies.pos++] = 0x06;/*quest: what is this in encoding?*/
	proto_ies.buf[proto_ies.pos++] = 0x80;
	buffer_copy(&proto_ies, s1ap_cfg->mme_name, strlen(s1ap_cfg->mme_name));

	/*IE2*/
	/**Item 1: id-ServedGUMMEIs*/
	proto_ie_id = S1AP_IE_SERVED_GUMMEIES;
	copyU16(tmp_str, proto_ie_id);
	buffer_copy(&proto_ies, tmp_str, sizeof(proto_ie_id));
	criticality = CRITICALITY_REJECT;
	buffer_copy(&proto_ies, &criticality, sizeof(criticality));

	//msg[i++] = 0x0b;//len
	gummies.buf[0]=0x0;
	gummies.buf[1]=0x0;
	gummies.pos = 2;

	/**Item 1: id-ServedGUMMEIs
	 *       servedPLMNs: 1 item*/
	struct PLMN local_plmn_id = {0};

	local_plmn_id.idx[0] = plmn->idx[0];
	local_plmn_id.idx[1] = plmn->idx[1];
	local_plmn_id.idx[2] = plmn->idx[2];
	
    buffer_copy(&gummies, &local_plmn_id, 3); // sizeof(struct PLMN)); plmn struct has some more fields
	gummies.buf[gummies.pos++]=0x0;
	gummies.buf[gummies.pos++]=0x0;

	/**Item 1: id-ServedGUMMEIs
	 *       servedGroupIDs: 1 item*/
	data_len = copyU16(tmp_str, s1ap_cfg->mme_group_id);
	buffer_copy(&gummies, tmp_str, data_len);

	/**Item 1: id-ServedGUMMEIs
	 *       servedMMECs: 1 item*/
	gummies.buf[gummies.pos++]=0x0;
	gummies.buf[gummies.pos++] = s1ap_cfg->mme_code;

	data_len = copyU16(tmp_str, gummies.pos);
	buffer_copy(&proto_ies, &(tmp_str[1]), 1);
	buffer_copy(&proto_ies, &gummies.buf, gummies.pos);

	/*IE3*/
	/**id: id-RelativeMMECapacity (87)*/
	proto_ie_id = S1AP_IE_REL_MME_CAPACITY;
	copyU16(tmp_str, proto_ie_id);
	buffer_copy(&proto_ies, tmp_str, sizeof(proto_ie_id));
	criticality = CRITICALITY_IGNORE;
	buffer_copy(&proto_ies, &criticality, sizeof(criticality));
	data_len = 1;
	buffer_copy(&proto_ies, &(data_len), 1);
	s1ap_cfg->rel_cap = 1;
	buffer_copy(&proto_ies, &(s1ap_cfg->rel_cap), 1);

	/*number of proto IEs = 3*/
	data_len = copyU16(tmp_str, 3);

	data_len = data_len + proto_ies.pos + 1;
	buffer_copy(&resp_buf, &data_len, 1);

	resp_buf.buf[resp_buf.pos++] = 0;/*quest: packed value should be 2 bytes...
									   here it needs 3 bytes*/
	buffer_copy(&resp_buf, tmp_str, 2);

	buffer_copy(&resp_buf, &proto_ies, proto_ies.pos);
	*s1_setup_resp = resp_buf.buf;

	return resp_buf.pos;
}

/******************************************************
  S1_SETUP_RESPONSE handling
******************************************************/
int
s1_setup_response(int enb_fd, struct PLMN *plmn)
{
    log_msg(LOG_DEBUG,"Process S1 Setup response.");
	uint32_t length = 0;
    uint8_t *buffer = NULL;
	s1ap_config_t *s1ap_cfg = get_s1ap_config();
    struct s1ap_common_req_Q_msg rsp_msg = {0};
    rsp_msg.IE_type = S1AP_SETUP_RESPONSE;

    memcpy(rsp_msg.mme_name, s1ap_cfg->mme_name, strlen(s1ap_cfg->mme_name));
    rsp_msg.mme_code = s1ap_cfg->mme_code;
	rsp_msg.mme_group_id = (s1ap_cfg->mme_group_id);
    
    struct PLMN local_plmn_id = {0};

	local_plmn_id.idx[0] = plmn->idx[0];
	local_plmn_id.idx[1] = plmn->idx[1];
	local_plmn_id.idx[2] = plmn->idx[2];
	log_msg(LOG_DEBUG,"Number of mnc digits %d \n", plmn->mnc_digits);
    memcpy(&rsp_msg.mme_plmn_id, &local_plmn_id, sizeof(struct PLMN));
    rsp_msg.rel_cap = s1ap_cfg->rel_cap;

    int ret = s1ap_mme_encode_outcome(&rsp_msg, &buffer, &length);
    if(ret == -1)
    {
        log_msg(LOG_ERROR, "Encoding S1 setup response failed.\n");
        return E_FAIL;
    }

    send_sctp_msg_with_fd(enb_fd, buffer, length, 0);
	log_msg(LOG_INFO, "buffer size is %d\n", length);
    if(buffer)
    {
        free(buffer);
        buffer = NULL;
        length = 0;
    }

	log_msg(LOG_INFO, "\n-----Message handlingcompleted.---\n");

	return SUCCESS;
}

/******************************************************
  S1_SETUP_FAILURE handling
******************************************************/
int
s1_setup_failure(struct s1ap_common_req_Q_msg* s1ap_setup_failure)
{
    log_msg(LOG_DEBUG,"Process S1 Setup failure.");
	uint32_t length = 0;
    uint8_t *buffer = NULL;
    int enb_fd = s1ap_setup_failure->enb_fd;

    int ret = s1ap_mme_encode_outcome(s1ap_setup_failure, &buffer, &length);
    if(ret == -1)
    {
        log_msg(LOG_ERROR, "Encoding S1 setup failure failed.\n");
        return E_FAIL;
    }

    send_sctp_msg_with_fd(enb_fd, buffer, length, 0);
	log_msg(LOG_INFO, "buffer size is %d\n", length);
    if(buffer)
    {
        free(buffer);
        buffer = NULL;
        length = 0;
    }

	log_msg(LOG_INFO, "\n-----Message handlingcompleted.---\n");

	return SUCCESS;
}

int
s1_setup_handler(InitiatingMessage_t *msg, int enb_fd)
{
	unsigned char *resp_msg = NULL;
	int resp_len = 0;
	s1ap_config_t *s1ap_cfg = get_s1ap_config();
    struct EnbStruct enbStruct = {0};
    enbStruct.enbFd_m = enb_fd;
    bool match_found = false;
    uint32_t cbIndex = 0;
    struct PLMN matched_plmn = {0};

	/*Validate all eNB info*/
	if(msg->value.present == InitiatingMessage__value_PR_S1SetupRequest)
	{
		ProtocolIE_Container_129P40_t *protocolIes = &msg->value.choice.S1SetupRequest.protocolIEs;
		for(int i=0; i < protocolIes->list.count; i++ )
		{
			S1SetupRequestIEs_t *ie_p;
			ie_p = protocolIes->list.array[i];
			log_msg(LOG_INFO, "s1setup %d \n", ie_p->id);
			switch(ie_p->id)
			{
				case ProtocolIE_ID_id_Global_ENB_ID:
				{
					Global_ENB_ID_t *geNb = &ie_p->value.choice.Global_ENB_ID;
					if(geNb->eNB_ID.present == ENB_ID_PR_macroENB_ID) 
					{
						log_msg(LOG_DEBUG, "macro eNB id size %d \n", geNb->eNB_ID.choice.macroENB_ID.size);
                        // Home eNB ID = 28 bits
                        uint8_t *enb_id_buf = geNb->eNB_ID.choice.homeENB_ID.buf;
                        /*enbStruct.enbId_m = 
                            (enb_id_buf[0] << 20) + 
                            (enb_id_buf[1] << 12) + 
                            (enb_id_buf[2] << 4) + 
                            ((enb_id_buf[3] & 0xf0) >> 4);*/
                        enbStruct.enbId_m = 
                            (enb_id_buf[0] << 12) + 
                            (enb_id_buf[1] << 4) + ((enb_id_buf[2] & 0xf0) >> 4);
					}
					break;
				}
				case ProtocolIE_ID_id_eNBname:
				{
					ENBname_t *eNbName = &ie_p->value.choice.ENBname;
					log_msg(LOG_DEBUG, "S1 Setup Message with eNB name %s \n", eNbName->buf);
					break;
				}
				
				case ProtocolIE_ID_id_SupportedTAs:
				{
					SupportedTAs_t *val = &ie_p->value.choice.SupportedTAs;
					for(int supTAs=0; supTAs<val->list.count; supTAs++)
					{
						SupportedTAs_Item_t *tac = val->list.array[supTAs];
						uint16_t tac_i=0;
						for(int t=0; t< tac->tAC.size; t++) 
						{
							tac_i = 10*tac_i + tac->tAC.buf[t]; 
						}

						log_msg(LOG_INFO, "S1setup Supported Tac %d %d size %d ..Final tac %d \n", tac->tAC.buf[0], tac->tAC.buf[1] , tac->tAC.size, tac_i);
						BPLMNs_t *plmns = &tac->broadcastPLMNs; 
						log_msg(LOG_INFO, "S1setup Supported PLMNS %d \n", plmns->list.count);
						for(int p=0; p<plmns->list.count; p++)
						{
							PLMNidentity_t *plmn = plmns->list.array[p]; 
							char plmn_s[10] = {'\0'};
							memcpy(plmn_s, plmn->buf, plmn->size);
							log_msg(LOG_INFO, "S1setup Supported PLMN %s Plmn buffer size %d \n", plmn_s, plmn->size);
							char plmn_s1[10] = {'\0'};
							sprintf(plmn_s1, "%d %d %d ",plmn->buf[0], plmn->buf[1], plmn->buf[2]);
							log_msg(LOG_INFO, "S1setup Supported PLMN %s \n", plmn_s1);
							struct PLMN plmn_struct = {0}; 
							for(int b=0; b< plmn->size; b++) 
							{
								plmn_struct.idx[b]  = plmn->buf[b]; 
							}
							int config_plmn;
							for(config_plmn = 0; config_plmn < s1ap_cfg->num_plmns; config_plmn++)
							{
								if((s1ap_cfg->plmns[config_plmn].idx[0] == plmn_struct.idx[0]) &&
								  (s1ap_cfg->plmns[config_plmn].idx[1] == plmn_struct.idx[1]) &&
								  (s1ap_cfg->plmns[config_plmn].idx[2] == plmn_struct.idx[2])) 
								{
									log_msg(LOG_INFO, "PLMN match found  Configured %x %x %x \n", s1ap_cfg->plmns[config_plmn].idx[0], s1ap_cfg->plmns[config_plmn].idx[1], s1ap_cfg->plmns[config_plmn].idx[2]);
									log_msg(LOG_INFO, "PLMN match found  Received %x %x %x \n", plmn_struct.idx[0], plmn_struct.idx[1], plmn_struct.idx[2]);
                                    memcpy(&enbStruct.tai_m.plmn_id,
                                           &plmn_struct, 
                                           3); //sizeof(struct PLMN)); plmn struct has some more fields
                                    enbStruct.tai_m.tac = tac_i;
                                    match_found = true;
                                    matched_plmn = s1ap_cfg->plmns[config_plmn];
									break;
								}
								else 
								{
									log_msg(LOG_INFO, "PLMN match not found  - Configured - %x %x %x \n", s1ap_cfg->plmns[config_plmn].idx[0], s1ap_cfg->plmns[config_plmn].idx[1], s1ap_cfg->plmns[config_plmn].idx[2]);
									log_msg(LOG_INFO, "PLMN match not found Received - %x %x %x \n", plmn_struct.idx[0], plmn_struct.idx[1], plmn_struct.idx[2]);
								}
							}
							if(config_plmn >= s1ap_cfg->num_plmns)
							{
								//TODO : reject connection no match found 
							}
						}
					}
					break;
				}
				case ProtocolIE_ID_id_DefaultPagingDRX:
				{
					PagingDRX_t *val = &ie_p->value.choice.PagingDRX;
					break;
				}
				default:
					break;
			}
		}
	} 

    if(match_found)
    {
        log_msg(LOG_DEBUG, "PLMN Match found. Create CB and add Enb Info");
        cbIndex = findControlBlockWithEnbId(enbStruct.enbId_m);
        if(INVALID_CB_INDEX == cbIndex)
        {
            log_msg(LOG_DEBUG, "No ENb ctx found for enb id %d.\n", enbStruct.enbId_m);
            cbIndex = createControlBlock();
            if(INVALID_CB_INDEX == cbIndex)
            {
                log_msg(LOG_ERROR,"CB creation failed.");
                return E_FAIL;
            }

            setValuesForEnbCtx(cbIndex, &enbStruct);
        }
        else
        {
            log_msg(LOG_DEBUG, "ENB Ctx found for enb id %d. Update values.\n",enbStruct.enbId_m);
            setValuesForEnbCtx(cbIndex, &enbStruct);
        }
    }
    else
    {
        log_msg(LOG_ERROR, "No PLMN Match found for enb id %d.\n",enbStruct.enbId_m);
        /* Send S1Setup Failure.*/
   	    struct s1ap_common_req_Q_msg s1ap_setup_failure = {0};
        s1ap_setup_failure.IE_type = S1AP_SETUP_FAILURE;
        s1ap_setup_failure.enb_fd = enb_fd;
        s1ap_setup_failure.cause.present = s1apCause_PR_misc;
        s1ap_setup_failure.cause.choice.misc = s1apCauseMisc_unknown_PLMN;
        return s1_setup_failure(&s1ap_setup_failure);
    }

	/*Create S1Setup response*/
    s1_setup_response(enb_fd, &matched_plmn);

	return SUCCESS;
}

