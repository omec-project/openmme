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
	struct ue_attach_info ue_info;

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
                    ue_info.esm_info_tx_required =
                        s1_init_ies->data[i].val.nas.elements[2].esm_info_tx_required;
                    memcpy(&(ue_info.IMSI), &(s1_init_ies->data[i].val.nas.elements[0].IMSI),
                           BINARY_IMSI_LEN);
                    memcpy(&(ue_info.ue_net_capab),
                           &(s1_init_ies->data[i].val.nas.elements[1].ue_network),
                           sizeof(struct UE_net_capab));
                    memcpy(&(ue_info.ms_net_capab),
                           &(s1_init_ies->data[i].val.nas.elements[4].ms_network),
                           sizeof(struct MS_net_capab));
                    ue_info.pti = s1_init_ies->data[i].val.nas.elements[5].pti;
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


