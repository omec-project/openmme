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
#include "common_proc_info.h"
#include "InitiatingMessage.h"
#include "UE-S1AP-ID-pair.h"

extern s1ap_config g_s1ap_cfg;

int s1ap_mme_encode_initiating(
  struct s1ap_common_req_Q_msg *message_p,
  uint8_t **buffer,
  uint32_t *length)
{
    log_msg(LOG_INFO, "MME initiating msg Encode.\n");
    switch (message_p->IE_type) {
        case S1AP_CTX_REL_CMD:
            log_msg(LOG_INFO, "Ue Context release Command Encode.\n");
            return s1ap_mme_encode_ue_context_release_command(
                      message_p, buffer, length);
        case S1AP_PAGING_REQ:
            log_msg(LOG_INFO, "Paging req Encode.\n");
            return s1ap_mme_encode_paging_request(
                      message_p, buffer, length);
        default:
            log_msg(
                  LOG_WARNING,
                  "Unknown procedure ID (%d) for initiating message_p\n",
                  (int) message_p->IE_type);
      }

  return -1;
}

int s1ap_mme_encode_ue_context_release_command(
  struct s1ap_common_req_Q_msg *s1apPDU,
  uint8_t **buffer,
  uint32_t *length)
{
	S1AP_PDU_t                              pdu = {(S1AP_PDU_PR_NOTHING)};
    InitiatingMessage_t *initiating_msg = NULL;
	S1AP_PDU_t                             *pdu_p = &pdu;
	int                                     enc_ret = -1;
	memset ((void *)pdu_p, 0, sizeof (S1AP_PDU_t));

    pdu.present = S1AP_PDU_PR_initiatingMessage;
    pdu.choice.initiatingMessage = (InitiatingMessage_t*)malloc(sizeof(InitiatingMessage_t));
    if(pdu.choice.initiatingMessage == NULL)
    {
        log_msg(LOG_ERROR,"malloc failed.\n");
        return -1;
    }
    initiating_msg = pdu.choice.initiatingMessage;
    initiating_msg->procedureCode = ProcedureCode_id_UEContextRelease;
    initiating_msg->criticality = 0;
    initiating_msg->value.present = InitiatingMessage__value_PR_UEContextReleaseCommand;  
    //proto_c = &initiating_msg->value.choice.UEContextReleaseCommand.protocolIEs;
            
    UEContextReleaseCommand_IEs_t val[2];
    UE_S1AP_IDs_t ue_id_val;
    struct UE_S1AP_ID_pair s1apId_pair;
    if((s1apPDU->mme_s1ap_ue_id != 0xFFFFFFFF) 
        && (s1apPDU->enb_s1ap_ue_id != 0xFFFFFFFF))
    {
        log_msg(LOG_INFO,"S1ap Id pair.\n");
        ue_id_val.present = UE_S1AP_IDs_PR_uE_S1AP_ID_pair;
        s1apId_pair.eNB_UE_S1AP_ID = s1apPDU->enb_s1ap_ue_id;
        s1apId_pair.mME_UE_S1AP_ID = s1apPDU->mme_s1ap_ue_id;
        ue_id_val.choice.uE_S1AP_ID_pair = (struct UE_S1AP_ID_pair*)malloc(sizeof(struct UE_S1AP_ID_pair));
        if(ue_id_val.choice.uE_S1AP_ID_pair == NULL)
        {
            log_msg(LOG_ERROR,"malloc failed.\n");
            free(pdu.choice.initiatingMessage);
            return -1;
        }
        memcpy(ue_id_val.choice.uE_S1AP_ID_pair, &s1apId_pair, sizeof(struct UE_S1AP_ID_pair));
    }
    else if(s1apPDU->mme_s1ap_ue_id != 0xFFFFFFFF)
    {
        ue_id_val.present = UE_S1AP_IDs_PR_mME_UE_S1AP_ID;
        ue_id_val.choice.mME_UE_S1AP_ID = s1apPDU->mme_s1ap_ue_id;
    }
    else
    {
        ue_id_val.present = UE_S1AP_IDs_PR_NOTHING;
    }

    val[0].id = ProtocolIE_ID_id_UE_S1AP_IDs;
    val[0].criticality = 0;
    val[0].value.present = UEContextReleaseCommand_IEs__value_PR_UE_S1AP_IDs;
    memcpy(&val[0].value.choice.UE_S1AP_IDs, &ue_id_val, sizeof(UE_S1AP_IDs_t));

    val[1].id = ProtocolIE_ID_id_Cause;
    val[1].criticality = 1;
    val[1].value.present = UEContextReleaseCommand_IEs__value_PR_Cause;
    //memcpy(&val[1].value.choice.Cause, &s1apPDU->cause, sizeof(Cause_t));
    val[1].value.choice.Cause.present = s1apPDU->cause.present;
    switch(s1apPDU->cause.present)
    {
        case Cause_PR_radioNetwork:
            val[1].value.choice.Cause.choice.radioNetwork
                = s1apPDU->cause.choice.radioNetwork;
        break;
        case Cause_PR_transport:
            val[1].value.choice.Cause.choice.transport
                = s1apPDU->cause.choice.transport;
        break;
        case Cause_PR_nas:
            val[1].value.choice.Cause.choice.nas
                = s1apPDU->cause.choice.nas;
        break;
        case Cause_PR_protocol:
            val[1].value.choice.Cause.choice.protocol
                = s1apPDU->cause.choice.protocol;
        break;
        case Cause_PR_misc:
            val[1].value.choice.Cause.choice.misc
                = s1apPDU->cause.choice.misc;
        break;
        case Cause_PR_NOTHING:
        default:
            log_msg(LOG_WARNING,"Unknown Cause type:%d\n",s1apPDU->cause.present);
    }

    log_msg(LOG_INFO,"Add values to list.\n");
    ASN_SEQUENCE_ADD(&initiating_msg->value.choice.UEContextReleaseCommand.protocolIEs.list, &val[0]);
    ASN_SEQUENCE_ADD(&initiating_msg->value.choice.UEContextReleaseCommand.protocolIEs.list, &val[1]);

    if ((enc_ret = aper_encode_to_new_buffer (&asn_DEF_S1AP_PDU, 0, &pdu, (void **)buffer)) < 0) 
    {
        log_msg(LOG_ERROR, "Encoding of Ctx Release Cmd failed\n");
        return -1;
    }

    log_msg(LOG_INFO,"free allocated msgs");
    free(ue_id_val.choice.uE_S1AP_ID_pair);
    free(pdu.choice.initiatingMessage);
    
    *length = enc_ret;
    return enc_ret; 
}


int s1ap_mme_encode_paging_request(
  struct s1ap_common_req_Q_msg *s1apPDU,
  uint8_t **buffer,
  uint32_t *length)
{
	S1AP_PDU_t                              pdu = {(S1AP_PDU_PR_NOTHING)};
    InitiatingMessage_t *initiating_msg = NULL;
	S1AP_PDU_t                             *pdu_p = &pdu;
	int                                     enc_ret = -1;
	memset ((void *)pdu_p, 0, sizeof (S1AP_PDU_t));

    pdu.present = S1AP_PDU_PR_initiatingMessage;
    pdu.choice.initiatingMessage = (InitiatingMessage_t*)malloc(sizeof(InitiatingMessage_t));
    if(pdu.choice.initiatingMessage == NULL)
    {
        log_msg(LOG_ERROR,"malloc failed.\n");
        return -1;
    }
    initiating_msg = pdu.choice.initiatingMessage;
    initiating_msg->procedureCode = ProcedureCode_id_Paging;
    initiating_msg->criticality = 0;
    initiating_msg->value.present = InitiatingMessage__value_PR_Paging;  
    //proto_c = &initiating_msg->value.choice.UEContextReleaseCommand.protocolIEs;
            
    PagingIEs_t val[5];

    val[0].id = ProtocolIE_ID_id_UEIdentityIndexValue;
    val[0].criticality = 0;
    val[0].value.present = PagingIEs__value_PR_UEIdentityIndexValue;
    UEIdentityIndexValue_t* UEIdentityIndexValue = &val[0].value.choice.UEIdentityIndexValue;
    uint64_t ue_imsi_value = 0;
    /* Set UE Identity Index value : IMSI mod 4096 */
    UEIdentityIndexValue->size = 2;
    UEIdentityIndexValue->buf = (uint8_t*)malloc(
                                    UEIdentityIndexValue->size * sizeof(uint8_t));

    /* Conver string to value */
    uint8_t imsi_bcd[BCD_IMSI_STR_LEN];
	convert_imsi_to_bcd_str(s1apPDU->imsi, imsi_bcd);
    for (int i = 0; i < BCD_IMSI_STR_LEN; i++)
    {
        ue_imsi_value = ue_imsi_value*10 + (imsi_bcd[i] - '0');
    }

    /* index(10bit) = ue_imsi_value mod 1024 */
    uint16_t index_value = ue_imsi_value % 1024;
    UEIdentityIndexValue->buf[0] = index_value >> 2;
    UEIdentityIndexValue->buf[1] = (index_value & 0x3f) << 6;
    UEIdentityIndexValue->bits_unused = 6;

    val[1].id = ProtocolIE_ID_id_UEPagingID;
    val[1].criticality = 0;
    val[1].value.present = PagingIEs__value_PR_UEPagingID;
    UEPagingID_t pagingId;
    pagingId.present = UEPagingID_PR_s_TMSI;
    pagingId.choice.s_TMSI = (struct S_TMSI*)malloc(sizeof(struct S_TMSI));
    if(pagingId.choice.s_TMSI == NULL)
    {
        log_msg(LOG_ERROR,"malloc failed.\n");
        free(pdu.choice.initiatingMessage);
        return -1;
    }
    pagingId.choice.s_TMSI->mMEC.buf = (uint8_t*)malloc(sizeof(g_s1ap_cfg.mme_code));
    if(NULL == pagingId.choice.s_TMSI->mMEC.buf)
    {
        log_msg(LOG_ERROR,"malloc failed.\n");
        free(pdu.choice.initiatingMessage);
        free(pagingId.choice.s_TMSI);
        return -1;
    }
    memcpy(pagingId.choice.s_TMSI->mMEC.buf, 
           &g_s1ap_cfg.mme_code, sizeof(uint8_t));
    pagingId.choice.s_TMSI->mMEC.size = sizeof(uint8_t);
    
    pagingId.choice.s_TMSI->m_TMSI.buf = (uint8_t*)malloc(sizeof(s1apPDU->ue_idx));
    if(NULL == pagingId.choice.s_TMSI->m_TMSI.buf)
    {
        log_msg(LOG_ERROR,"malloc failed.\n");
        free(pdu.choice.initiatingMessage);
        free(pagingId.choice.s_TMSI);
        free(pagingId.choice.s_TMSI->mMEC.buf);
        return -1;
    }
    uint32_t ue_idx = htonl(s1apPDU->ue_idx);
    memcpy(pagingId.choice.s_TMSI->m_TMSI.buf, &ue_idx, sizeof(uint32_t));
    pagingId.choice.s_TMSI->m_TMSI.size = sizeof(uint32_t);
    memcpy(&val[1].value.choice.UEPagingID, 
             &pagingId, sizeof(UEPagingID_t));

    val[2].id = ProtocolIE_ID_id_CNDomain;
    val[2].criticality = 0;
    val[2].value.present = PagingIEs__value_PR_CNDomain;
    val[1].value.choice.CNDomain = s1apPDU->cn_domain;;

    val[3].id = ProtocolIE_ID_id_TAIList;
    val[3].criticality = 0;
    val[3].value.present = PagingIEs__value_PR_TAIList;
    TAIList_t tailist;
    TAIItemIEs_t tai_item;
    tai_item.id = ProtocolIE_ID_id_TAIItem;
    tai_item.criticality = 0;
    tai_item.value.present = TAIItemIEs__value_PR_TAIItem;
    memcpy(tai_item.value.choice.TAIItem.tAI.pLMNidentity.buf,
            s1apPDU->tai.plmn_id.idx, 3);
    tai_item.value.choice.TAIItem.tAI.pLMNidentity.size = 3;
    memcpy(tai_item.value.choice.TAIItem.tAI.tAC.buf,
            &s1apPDU->tai.tac, 2);
    tai_item.value.choice.TAIItem.tAI.tAC.size = 2;

    ASN_SEQUENCE_ADD(&tailist.list, &tai_item);
    log_msg(LOG_INFO,"Add values to list.\n");
    ASN_SEQUENCE_ADD(&initiating_msg->value.choice.Paging.protocolIEs.list, &val[0]);
    ASN_SEQUENCE_ADD(&initiating_msg->value.choice.Paging.protocolIEs.list, &val[1]);
    ASN_SEQUENCE_ADD(&initiating_msg->value.choice.Paging.protocolIEs.list, &val[2]);
    ASN_SEQUENCE_ADD(&initiating_msg->value.choice.Paging.protocolIEs.list, &val[3]);

    if ((enc_ret = aper_encode_to_new_buffer (&asn_DEF_S1AP_PDU, 0, &pdu, (void **)buffer)) < 0) 
    {
        log_msg(LOG_ERROR, "Encoding of Ctx Release Cmd failed\n");
        return -1;
    }

    log_msg(LOG_INFO,"free allocated msgs");
    free(pdu.choice.initiatingMessage);
    free(UEIdentityIndexValue->buf);
    free(pagingId.choice.s_TMSI->mMEC.buf);
    free(pagingId.choice.s_TMSI->m_TMSI.buf);
    free(pagingId.choice.s_TMSI);
    
    *length = enc_ret;
    return enc_ret; 
}
