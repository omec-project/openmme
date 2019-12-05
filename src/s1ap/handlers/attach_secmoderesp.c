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
#include "stage4_info.h"

extern int g_enb_fd;
extern ipc_handle ipcHndl_secresp;

int
s1_secmode_resp_handler(struct proto_IE *s1_sec_resp_ies)
{
	//TODO: use static instead of synamic for perf.
	struct secmode_resp_Q_msg secmode_resp;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse s1ap sec mode complete message:--\n");

	/*Validate all eNB info*/

	/*Add eNB info to hash*/

	/*Create Q structure for stage 1 to MME.
	  contains init UE information.*/
    for(int i = 0; i < s1_sec_resp_ies->no_of_IEs; i++)
    {
        switch(s1_sec_resp_ies->data[i].IE_type)
        {
            case S1AP_IE_MME_UE_ID:
                {
	                secmode_resp.ue_idx = s1_sec_resp_ies->data[i].val.mme_ue_s1ap_id;
                }break;
            case S1AP_IE_NAS_PDU:
                {
                    if(s1_sec_resp_ies->data[i].val.nas.header.message_type != NAS_SEC_MODE_COMPLETE)
                    {
                        secmode_resp.status = S1AP_SECMODE_FAILED;//Error in authentication
                    }
                    else
                    {
                        secmode_resp.status = SUCCESS;
                    }

                }break;
            default:
                log_msg(LOG_WARNING,"Unhandled IE");
        }
    }

	/*Copy xres from response, send to mme for verification*/
	//...
	//auth_res.res.len = a1_secmode_resp_ies[2].data.nas.authresp_len;
	//memcpy(&(auth_res.res.val, s1_sec_resp_ies[2].data.nas.RES, authres.res.len);

	write_ipc_channel(ipcHndl_secresp, (char *)&secmode_resp, S1AP_SECRESP_STAGE4_BUF_SIZE);

	/*Send S1Setup response*/
	log_msg(LOG_INFO, "Auth resp send to mme-app stage4.\n");

	//TODO: free IEs
	return SUCCESS;
}

