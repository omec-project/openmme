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
#include "stage5_info.h"

extern int g_enb_fd;
extern  ipc_handle ipcHndl_esmresp;

int
s1_esm_resp_handler(struct proto_IE *s1_esm_resp_ies)
{
	struct esm_resp_Q_msg esm_resp;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse s1ap ESM response message:--\n");

	/*Validate all eNB info*/

	/*Add eNB info to hash*/

	/*Create Q structure for stage 1 to MME.
	  contains init UE information.*/
    for(int i = 0; i < s1_esm_resp_ies->no_of_IEs; i++)
    {
        switch(s1_esm_resp_ies->data[i].IE_type)
        {
            case S1AP_IE_MME_UE_ID:
                {
	                esm_resp.ue_idx = s1_esm_resp_ies->data[i].val.mme_ue_s1ap_id;
                }break;
            case S1AP_IE_NAS_PDU:
                {
                    if(s1_esm_resp_ies->data[i].val.nas.header.message_type != NAS_ESM_RESP)
                    {
                        esm_resp.status = S1AP_SECMODE_FAILED;//Error in authentication
                    }
                    else
                    {
                        esm_resp.status = SUCCESS;
	                    memcpy(&(esm_resp.apn), &(s1_esm_resp_ies->data[i].val.nas.elements[0].apn),
		                       sizeof(struct apn_name));
                    }

                }break;
            default:
                log_msg(LOG_WARNING,"Unhandled IE");
        }
    }

	int i = write_ipc_channel(ipcHndl_esmresp, (char *)&esm_resp, S1AP_ESMRESP_STAGE5_BUF_SIZE);

	if (i < 0) {
		log_msg(LOG_ERROR, "Error to write in s1_esm_resp_handler\n");
	}
	/*Send S1Setup response*/
	log_msg(LOG_INFO, "ESM resp send to mme-app stage5. Bytes send %d\n", i);

	//TODO: free IEs
	return SUCCESS;
}

