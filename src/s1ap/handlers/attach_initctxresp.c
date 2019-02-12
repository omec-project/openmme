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
#include "stage7_info.h"

extern int g_enb_fd;
extern ipc_handle ipcHndl_icsresp;

int
s1_init_ctx_resp_handler(char *msg)
{
	struct proto_IE s1_ics_ies;
	struct initctx_resp_Q_msg ics_resp;

	/*****Message structure****/
	log_msg(LOG_INFO, "Parse int ctx s1ap response message:--\n");
	parse_IEs(msg+2, &s1_ics_ies, S1AP_INITIAL_CTX_RESP_CODE);

	ics_resp.ue_idx = s1_ics_ies.data[0].mme_ue_s1ap_id;
	ics_resp.transp_layer_addr = s1_ics_ies.data[2].erab.elements[0].su_res.transp_layer_addr;
	ics_resp.gtp_teid = s1_ics_ies.data[2].erab.elements[0].su_res.gtp_teid;

	int i = write_ipc_channel(ipcHndl_icsresp, (char *)&ics_resp, S1AP_ICSRESP_STAGE7_BUF_SIZE);

	if (i < 0) {
		log_msg(LOG_ERROR, "Error to write in s1_init_ctx_resp_handler\n");
	}
	/*Send S1Setup response*/
	log_msg(LOG_INFO, "Init ctx resp send to mme-app stage7. Bytes send %d\n", i);

	//TODO: free IEs
	return SUCCESS;
}
