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

/*Globals and externs*/
extern int g_Q_MBresp_fd;

/*End : globals and externs*/

int
s11_MB_resp_handler(char *message)
{
	struct s11_proto_IE s1_mbr_ies;		
	struct MB_resp_Q_msg mbr_info;
	struct gtpv2c_header *header = (struct gtpv2c_header*)message;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse S11 MB resp message\n");
	parse_gtpv2c_IEs((char *)(header+1), ntohs(header->gtp.len), &s1_mbr_ies);

	//TODO : check cause foor the result verification
	
	/*Check whether has teid flag is set. Also check whether this check is needed for CSR.*/
	mbr_info.ue_idx = ntohl(header->teid.has_teid.teid);

	memcpy(&(mbr_info.s1u_sgw_fteid), &(s1_mbr_ies.s11_ies[1].data.bearer.s1u_sgw_teid), 
			sizeof(struct fteid));

	/*Send CS response msg*/
	write_ipc_channel(g_Q_MBresp_fd, (char *)&mbr_info, S11_MBRESP_STAGE8_BUF_SIZE);
	log_msg(LOG_INFO, "Send MB resp to mme-app stage8.\n");

	return SUCCESS;
}
