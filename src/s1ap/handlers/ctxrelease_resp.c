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
#include "detach_stage3_info.h"

extern int g_enb_fd;
extern ipc_handle ipcHndl_ctx_release_complete;

int
s1_ctx_release_resp_handler(InitiatingMessage_t *msg)
{
	struct ctx_release_complete_Q_msg release_complete;
	struct proto_IE s1_ctx_release_ies;

    convertToInitUeProtoIe(msg, &s1_ctx_release_ies);

	/*TODO: Validate all eNB info*/

	release_complete.ue_idx = s1_ctx_release_ies.data[0].val.mme_ue_s1ap_id;

	int i = 0;
	i = write_ipc_channel(ipcHndl_ctx_release_complete,
				(char *)&release_complete,
				S1AP_CTXRELRESP_STAGE3_BUF_SIZE);
	if (i < 0) {

		log_msg(LOG_ERROR,"Error To write in s1_ctx_release_resp_handler\n");
	}

	log_msg(LOG_INFO, "Ctx Release complete sent to mme-app."
				"Bytes send %d\n", i);

	//TODO: free IEs
	return SUCCESS;
}

