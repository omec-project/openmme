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
#include "gtpV2StackWrappers.h"

/*Globals and externs*/
extern int g_Q_CSresp_fd;
extern struct GtpV2Stack* gtpStack_gp;
/*End : globals and externs*/


int
s11_CS_resp_handler(MsgBuffer* message, GtpV2MessageHeader* hdr)
{
	struct csr_Q_msg csr_info;
	/*****Message structure***
	*/

	/*Check whether has teid flag is set. Also check whether this check is needed for CSR.*/
	csr_info.ue_idx = hdr->teid;

	CreateSessionResponseMsgData msgData;
	memset(&msgData, 0, sizeof(CreateSessionResponseMsgData));

	bool rc = GtpV2Stack_decodeMessage(gtpStack_gp, hdr, message, &msgData);
	if(rc == false)
	{
			log_msg(LOG_ERROR, "s11_CS_resp_handler: "
								"Failed to decode Create Session Response Msg %d\n",
								hdr->teid);
			return E_PARSING_FAILED;
	}

	csr_info.s11_sgw_fteid.header.iface_type = 11;
	csr_info.s11_sgw_fteid.header.teid_gre = msgData.senderFTeidForControlPlane.teidGreKey;
	csr_info.s11_sgw_fteid.header.v4 = 1;
	csr_info.s11_sgw_fteid.ip.ipv4.s_addr = msgData.senderFTeidForControlPlane.ipV4Address.ipValue;

	csr_info.s5s8_pgwc_fteid.header.iface_type = 7;
	csr_info.s5s8_pgwc_fteid.header.teid_gre = msgData.pgwS5S8S2bFTeid.teidGreKey;
	csr_info.s5s8_pgwc_fteid.header.v4 = 1;
	csr_info.s5s8_pgwc_fteid.ip.ipv4.s_addr = msgData.pgwS5S8S2bFTeid.ipV4Address.ipValue;

	csr_info.s1u_sgw_fteid.header.iface_type = 1;
	csr_info.s1u_sgw_fteid.header.teid_gre = msgData.bearerContextsCreated[0].s1USgwFTeid.teidGreKey;
	csr_info.s1u_sgw_fteid.header.v4 = 1;
	csr_info.s1u_sgw_fteid.ip.ipv4.s_addr = msgData.bearerContextsCreated[0].s1USgwFTeid.ipV4Address.ipValue;

	csr_info.s5s8_pgwu_fteid.header.iface_type = 5;
	csr_info.s5s8_pgwu_fteid.header.teid_gre = msgData.bearerContextsCreated[0].s5S8UPgwFTeid.teidGreKey;
	csr_info.s5s8_pgwu_fteid.header.v4 = 1;
	csr_info.s5s8_pgwu_fteid.ip.ipv4.s_addr = msgData.bearerContextsCreated[0].s5S8UPgwFTeid.ipV4Address.ipValue;

	csr_info.pdn_addr.pdn_type = 1;
	csr_info.pdn_addr.ip_type.ipv4.s_addr = msgData.pdnAddressAllocation.ipV4Address.ipValue;
	

	/*Send CS response msg*/
	write_ipc_channel(g_Q_CSresp_fd, (char *)&csr_info, S11_CSRESP_STAGE6_BUF_SIZE);
	log_msg(LOG_INFO, "Send CS resp to mme-app stage6.\n");

	return SUCCESS;
}
