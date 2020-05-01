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
#include "stage3_info.h"
#include "s1ap_mme_msg.h"

extern int g_enb_fd;
extern ipc_handle ipcHndl_identityresp;
extern struct time_stat g_attach_stats[];

int
s1_identity_resp_handler(struct proto_IE *s1_id_resp_ies)
{
	struct identityResp_Q_msg id_resp;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse s1ap identity resp message:--\n");

	/*Validate all eNB info*/

	/*Add eNB info to hash*/

	/*Create Q structure for stage 1 to MME.
	  contains init UE information.*/
    for(int i = 0; i < s1_id_resp_ies->no_of_IEs; i++)
    {
        switch(s1_id_resp_ies->data[i].IE_type)
        {
            case S1AP_IE_MME_UE_ID:
                {
	                id_resp.ue_idx = s1_id_resp_ies->data[i].val.mme_ue_s1ap_id;
                }break;
            case S1AP_IE_NAS_PDU:
                {
                    if(s1_id_resp_ies->data[i].val.nas.header.message_type != NAS_IDENTITY_RESPONSE)
                    {
                        id_resp.status = S1AP_IDENTITY_FAILED; 
                    }
                    else
                    {
                        id_resp.status = SUCCESS;
                    }

                    memcpy(&(id_resp.IMSI), 
                           &(s1_id_resp_ies->data[i].val.nas.elements[0].pduElement.IMSI),
                           BINARY_IMSI_LEN);
                }break;
            default:
                log_msg(LOG_WARNING,"Unhandled IE In identification Response %d \n",s1_id_resp_ies->data[i].IE_type);
        }
    }

	//STIMER_GET_CURRENT_TP(g_attach_stats[s1_id_resp_ies->data[1].enb_ue_s1ap_id].auth_to_mme);
	write_ipc_channel(ipcHndl_identityresp, (char *)&id_resp, S1AP_IDRESP_BUF_SIZE);

	/*Send S1Setup response*/
	log_msg(LOG_INFO, "Auth resp send to mme-app stage3.\n");

	//TODO: free IEs
	return SUCCESS;
}


