/*
 * Copyright 2019-present Open Networking Foundation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
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

extern ipc_handle ipcHndl_taureq;

int
s1_tau_request_handler(struct proto_IE *s1_tau_req_ies, int enb_fd)
{
	log_msg(LOG_INFO, "S1ap received tau Request:--\n");
	struct tauReq_Q_msg tau_req;
    tau_req.enb_fd = enb_fd;

    for(int i = 0; i < s1_tau_req_ies->no_of_IEs; i++)
    {
        switch(s1_tau_req_ies->data[i].IE_type)
        {
			case S1AP_IE_ENB_UE_ID:
			{
				tau_req.s1ap_enb_ue_id = s1_tau_req_ies->data[i].val.enb_ue_s1ap_id;
				break;
			}
			case S1AP_IE_MME_UE_ID:
			{
				tau_req.ue_idx = s1_tau_req_ies->data[i].val.mme_ue_s1ap_id;
				break;
			}
            case S1AP_IE_NAS_PDU:
            {
                nas_pdu_header *hdr = &s1_tau_req_ies->data[i].val.nas.header;
                tau_req.seq_num = hdr->seq_no;
                break;
            }
            default:
			// Once MME starts handlign thsi request we can parse and send the content 
			log_msg(LOG_WARNING,"Unhandled IE In tau request %d",s1_tau_req_ies->data[i].IE_type);
		}
	}
	log_msg(LOG_INFO, "Send TAU request to mme-app\n");
	write_ipc_channel(ipcHndl_taureq, (char *)&tau_req, S1AP_TAUREQ_BUF_SIZE);
	log_msg(LOG_INFO, "Sent TAU request to mme-app\n");
	return SUCCESS;
}

