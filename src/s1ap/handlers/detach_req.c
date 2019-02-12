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
#include "detach_stage1_info.h"

extern int g_enb_fd;
extern ipc_handle ipcHndl_detach;

int
detach_stage1_handler(struct proto_IE *detach_ies, bool retransmit)
{
	struct detach_req_Q_msg req;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse s1ap detach request message\n");

	/*Validate all eNB info*/

	/*Add eNB info to hash*/

	/*Create Q structure for detach stage 1 to MME.
	  contains init UE information.*/
	/* TODO : Revisit, in InitialContextSetup Request we are sending
	 * MME UE S1AP Id as M-TMSI.
	 */
	if (!retransmit)
		req.ue_idx = detach_ies->data[0].mme_ue_s1ap_id;
	else
		req.ue_idx = ntohl(detach_ies->data[1].nas.elements[0].mi_guti.m_TMSI);

	write_ipc_channel(ipcHndl_detach, (char *)&req, S1AP_DETACHREQ_STAGE1_BUF_SIZE);

	/*Send S1Setup response*/
	log_msg(LOG_INFO, "Send to mme-app stage1.\n");

	return SUCCESS;
}


