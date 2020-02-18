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
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "err_codes.h"
#include "options.h"
#include "ipc_api.h"
#include "message_queues.h"
#include "s11.h"
#include "s11_config.h"
#include "common_proc_info.h"

/*Globals and externs*/
extern int g_Q_S11_Incoming_fd;

/*End : globals and externs*/

int
s11_RABR_resp_handler(MsgBuffer* message, GtpV2MessageHeader* hdr)
{
	struct s11_resp_Q_msg rabr_info;
	struct gtpv2c_header *header = (struct gtpv2c_header*)message;

	/*****Message structure****/
	log_msg(LOG_INFO, "Parse S11 RABR resp message\n");

	rabr_info.IE_type = S11_RABR_RESP;
	rabr_info.ue_idx = hdr->teid;

	/*Send RABR response msg*/
	write_ipc_channel(g_Q_S11_Incoming_fd, (char *)&rabr_info,
			S11_COMM_RES_STAGE_BUF_SIZE);
	log_msg(LOG_INFO, "Send RAB resp to mme-app .\n");

	return SUCCESS;
}
