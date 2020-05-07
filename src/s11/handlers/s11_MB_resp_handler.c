/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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
#include "stage8_info.h"
#include "gtpV2StackWrappers.h"

/*Globals and externs*/
extern int g_Q_MBresp_fd;

/*End : globals and externs*/

int
s11_MB_resp_handler(MsgBuffer* message, GtpV2MessageHeader* hdr)
{
	struct MB_resp_Q_msg mbr_info;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse S11 MB resp message\n");

	//TODO : check cause foor the result verification
	
	/*Check whether has teid flag is set. Also check whether this check is needed for CSR.*/
	mbr_info.ue_idx = hdr->teid;

	/*Send CS response msg*/
	write_ipc_channel(g_Q_MBresp_fd, (char *)&mbr_info, S11_MBRESP_STAGE8_BUF_SIZE);
	log_msg(LOG_INFO, "Send MB resp to mme-app stage8.\n");

	return SUCCESS;
}
