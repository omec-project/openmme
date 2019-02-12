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
#include "stage6_info.h"

/*Globals and externs*/
extern int g_Q_CSresp_fd;

/*End : globals and externs*/


int
s11_CS_resp_handler(char *message)
{
	struct s11_proto_IE s1_csr_ies;		
	struct csr_Q_msg csr_info;
	struct gtpv2c_header *header = (struct gtpv2c_header*)message;

	/*****Message structure***
	*/
	log_msg(LOG_INFO, "Parse S11 CS resp message\n");
	parse_gtpv2c_IEs((char *)header+1, ntohs(header->gtp.len), &s1_csr_ies);

	/*Check whether has teid flag is set. Also check whether this check is needed for CSR.*/
	csr_info.ue_idx = ntohl(header->teid.has_teid.teid);

	/*Create CSR Q msg*/
	memcpy(&(csr_info.s11_sgw_fteid), &(s1_csr_ies.s11_ies[1].data.s11_sgw_fteid), 
			sizeof(struct fteid));
	
	memcpy(&(csr_info.s5s8_pgwc_fteid), &(s1_csr_ies.s11_ies[2].data.s5s8_pgw_c_fteid), 
			sizeof(struct fteid));
	
	memcpy(&(csr_info.s1u_sgw_fteid), &(s1_csr_ies.s11_ies[5].data.bearer.s1u_sgw_teid), 
			sizeof(struct fteid));
	
	memcpy(&(csr_info.s5s8_pgwu_fteid), &(s1_csr_ies.s11_ies[5].data.bearer.s5s8_pgw_u_teid), 
			sizeof(struct fteid));

	csr_info.pdn_addr.pdn_type = 1;//TODO: hardcoding for ipv4 for now
	memcpy(&(csr_info.pdn_addr.ip_type.ipv4), &(s1_csr_ies.s11_ies[3].data.pdn_addr.ip_type.ipv4), 
		sizeof(struct in_addr));
	
	/*Send CS response msg*/
	write_ipc_channel(g_Q_CSresp_fd, (char *)&csr_info, S11_CSRESP_STAGE6_BUF_SIZE);
	log_msg(LOG_INFO, "Send CS resp to mme-app stage6.\n");

	return SUCCESS;
}
