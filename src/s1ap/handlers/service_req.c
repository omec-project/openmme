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
#include "servicereq_info.h"

extern int g_enb_fd;
extern ipc_handle ipcHndl_service_req;

int
s1_init_ue_service_req_handler(struct proto_IE *service_req_ies, int enb_fd)
{
	struct service_req_Q_msg req;
	s1ap_config_t *s1ap_cfg = get_s1ap_config();

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse s1ap Service request message\n");

	/*Validate all eNB info*/

	/*Add eNB info to hash*/

	/*Create Q structure for Service req to MME.
	  contains init UE information.*/
	/* TODO : Revisit, in InitialContextSetup Request we are sending
	 * MME UE S1AP Id as M-TMSI.
	 */

    req.enb_fd = enb_fd;
    for(int i = 0; i < service_req_ies->no_of_IEs; i++)
    {
        switch(service_req_ies->data[i].IE_type)
        {
            case S1AP_IE_ENB_UE_ID:
                {
                    log_msg(LOG_INFO, "Service Req S1AP_IE_ENB_UE_ID.\n");
                    req.s1ap_enb_ue_id = service_req_ies->data[i].val.enb_ue_s1ap_id;
                }break;
            case S1AP_IE_NAS_PDU:
                {
                    log_msg(LOG_INFO, "Service Req NAS PDU.\n");
                    req.ksi = service_req_ies->data[i].val.nas.header.ksi;;
                    req.seq_no = service_req_ies->data[i].val.nas.header.seq_no;
                    memcpy(&req.mac, service_req_ies->data[i].val.nas.header.short_mac, sizeof(uint16_t));
                }break;
            case S1AP_IE_TAI:
                {
                    log_msg(LOG_INFO, "Service Req TAI.\n");
                    memcpy(&req.tai, 
                        &service_req_ies->data[i].val.tai, 
                        sizeof(struct TAI));
                }break;
            case S1AP_IE_UTRAN_CGI:
                {
                    log_msg(LOG_INFO, "Service Req CGI.\n");
                    memcpy(&req.utran_cgi, 
                        &service_req_ies->data[i].val.utran_cgi, 
                        sizeof(struct CGI));
                }break;
            case S1AP_IE_S_TMSI:
                {
                    log_msg(LOG_INFO, "Service Req STMSI.\n");
                    if(service_req_ies->data[i].val.s_tmsi.mme_code 
                       == s1ap_cfg->mme_code)
                    {
                        log_msg(LOG_INFO, "Service Req MME Code matched.\n");
                        req.ue_idx = ntohl(service_req_ies->data[i].val.s_tmsi.m_TMSI);
                        memcpy(&req.s_tmsi, 
                        &service_req_ies->data[i].val.s_tmsi,
                         sizeof(struct STMSI));
                    }
                    else
                    {
                        log_msg(LOG_ERROR, "MME code mismatch. Send Service Reject. TBD");
                        return -E_FAIL;
                    }
                }break;
            default:
                log_msg(LOG_WARNING,"Unhandled IE %d \n", service_req_ies->data[i].IE_type);
        }
    }

	write_ipc_channel(ipcHndl_service_req, (char *)&req, S1AP_SERVICEREQ_BUF_SIZE);

	/*Send Service req to mme-app*/
	log_msg(LOG_INFO, "Send to mme-app service req handler.\n");

	return SUCCESS;
}


