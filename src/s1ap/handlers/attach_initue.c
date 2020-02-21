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

extern int g_enb_fd;
extern ipc_handle ipcHndl_attach;
extern struct time_stat g_attach_stats[];

int
s1_init_ue_handler(struct proto_IE *s1_init_ies, int enodeb_fd)
{
	struct ue_attach_info ue_info = {0};
	int nas_index = 0;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse s1ap initial UE message\n");

	/*Validate all eNB info*/

	/*Add eNB info to hash*/
	//STIMER_GET_CURRENT_TP(g_attach_stats[s1_init_ies->data[0].enb_ue_s1ap_id].init_ue);

	/*Create Q structure for stage 1 to MME.
	  contains init UE information.*/
	ue_info.enb_fd = enodeb_fd;
	ue_info.criticality = s1_init_ies->criticality;
    for(int i = 0; i < s1_init_ies->no_of_IEs; i++)
    {
        switch(s1_init_ies->data[i].IE_type)
        {
            case S1AP_IE_ENB_UE_ID:
                {
	                ue_info.s1ap_enb_ue_id = s1_init_ies->data[i].val.enb_ue_s1ap_id;
                }break;
            case S1AP_IE_TAI:
                {
                    memcpy(&(ue_info.tai), &(s1_init_ies->data[i].val.tai), sizeof(struct TAI));
                }break;
            case S1AP_IE_UTRAN_CGI:
                {
                    memcpy(&(ue_info.utran_cgi), &(s1_init_ies->data[i].val.utran_cgi),
                           sizeof(struct CGI));
                }break;
            case S1AP_IE_NAS_PDU:
                {
                    while(nas_index < s1_init_ies->data[i].val.nas.elements_len)
                    {
                        log_msg(LOG_INFO, "nasIndex %d, msgType %d\n",
                                nas_index,
                                s1_init_ies->data[i].val.nas.elements[nas_index].msgType);
                        ue_info.seq_no = s1_init_ies->data[i].val.nas.header.seq_no;
                        switch(s1_init_ies->data[i].val.nas.elements[nas_index].msgType)
                        {
                            case NAS_IE_TYPE_ESM_MSG:
                                {
                                    break;
                                }
                            case NAS_IE_TYPE_EPS_MOBILE_ID_IMSI:
                                {
                                    ue_info.flags = s1_init_ies->data[i].val.nas.flags;
                                    if(UE_ID_IMSI(s1_init_ies->data[i].val.nas.flags))
                                    { 
                                        memcpy(&(ue_info.IMSI), 
                                               &(s1_init_ies->data[i].val.nas.elements[nas_index].pduElement.IMSI),
                                               BINARY_IMSI_LEN);
                                    }
                                    else if(UE_ID_GUTI(s1_init_ies->data[i].val.nas.flags))
                                    {
                                        memcpy(&(ue_info.mi_guti), &(s1_init_ies->data[i].val.nas.elements[nas_index].pduElement.mi_guti),
                                               sizeof(struct guti));
                                    }
                                    break;
                                }
                            case NAS_IE_TYPE_UE_NETWORK_CAPABILITY:
                                {
                                    memcpy(&(ue_info.ue_net_capab),
                                           &(s1_init_ies->data[i].val.nas.\
                                             elements[nas_index].pduElement.ue_network),
                                           sizeof(struct UE_net_capab));

                                    break;
                                }
                            case NAS_IE_TYPE_MS_NETWORK_CAPABILITY:
                                {
                                    memcpy(&(ue_info.ms_net_capab),
                                           &(s1_init_ies->data[i].val.nas.\
                                             elements[nas_index].pduElement.ms_network),
                                           sizeof(struct MS_net_capab));

                                    break;
                                }
                            case NAS_IE_TYPE_TX_FLAG:
                                {
                                    ue_info.esm_info_tx_required =
                                        s1_init_ies->data[i].val.nas.elements[nas_index].pduElement.esm_info_tx_required;
                                    break;
                                }
                            case NAS_IE_TYPE_PTI:
                                {
                                    ue_info.pti =
                                        s1_init_ies->data[i].val.nas.elements[nas_index].pduElement.pti;
                                    break;
                                }
                            case NAS_IE_TYPE_PCO:
                                {
                                        memcpy(&ue_info.pco_options[0], &s1_init_ies->data[i].val.nas.elements[nas_index].pduElement.pco_opt.pco_options[0], s1_init_ies->data[i].val.nas.elements[nas_index].pduElement.pco_opt.pco_length);
                                    ue_info.pco_length = s1_init_ies->data[i].val.nas.elements[nas_index].pduElement.pco_opt.pco_length;
                                    break;
                                }
                            default:
                                {
                                    log_msg(LOG_INFO, "nas element not handled\n");
                                }
                        }

                        nas_index++;
                    }

                }break;
            default:
                log_msg(LOG_WARNING,"Unhandled IE");
        }
    }

	write_ipc_channel(ipcHndl_attach, (char *)&ue_info, INITUE_STAGE1_BUF_SIZE);

	/*Send S1Setup response*/
	log_msg(LOG_INFO, "Send to mme-app stage1.\n");

	return SUCCESS;
}


