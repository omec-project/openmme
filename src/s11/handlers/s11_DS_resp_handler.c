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
#include "detach_stage2_info.h"

/*Globals and externs*/
extern int g_Q_DSresp_fd;

/*End : globals and externs*/

int
s11_DS_resp_handler(char *message)
{
	struct s11_proto_IE s1_dsr_ies;
	struct DS_resp_Q_msg dsr_info;
	struct gtpv2c_header *header = (struct gtpv2c_header*)message;

	/*****Message structure****/
	log_msg(LOG_INFO, "Parse S11 DS resp message\n");
	parse_gtpv2c_IEs((char*)(header+1), ntohs(header->gtp.len), &s1_dsr_ies);

	//TODO : check cause for the result verification

	/*Check whether has teid flag is set.
	 * Also check whether this check is needed for DSR.
	 * */
	dsr_info.ue_idx = ntohl(header->teid.has_teid.teid);

	/*Send CS response msg*/
	write_ipc_channel(g_Q_DSresp_fd, (char *)&dsr_info,
			S1AP_DTCHRES_STAGE2_BUF_SIZE);
	log_msg(LOG_INFO, "Send DS resp to mme-app stage8.\n");

	return SUCCESS;
}
