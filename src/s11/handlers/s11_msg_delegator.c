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
#include "s11_structs.h"

/*
  Get count of no of IEs in gtpv2c msg
*/
static int
get_IE_cnt(char *msg, int len)
{
	int cnt = 0;
	char *tmp = msg+11;
	struct s11_IE_header *header = (struct s11_IE_header *)tmp;

	for(; (char *)tmp <= msg + len; ++cnt) {
		tmp += sizeof(struct s11_IE_header) + ntohs(header->ie_len);
		header = (struct s11_IE_header*)tmp;
	}
	return cnt;
}

void
network_cp_fteid(struct fteid *teid, char *data)
{
	unsigned int *tmp;

	memcpy(teid, data, sizeof(struct fteid));
	teid->header.teid_gre = ntohl(teid->header.teid_gre);
	tmp = (unsigned int*)(data+5);
	*tmp = ntohl(*tmp);
	memcpy(&(teid->ip.ipv4), tmp, sizeof(struct in_addr));  
}

int
parse_bearer_ctx(struct bearer_ctx *bearer, char* data, short len)
{
	char no_of_ies = 4;
	//TODO: count no of IEs

	for(int i=0; i < no_of_ies; ++i) {
		struct s11_IE_header *header = (struct s11_IE_header*)data;
		char *value = data + sizeof(struct s11_IE_header);

		switch(header->ie_type){
		case S11_IE_CAUSE:
			memcpy(&(bearer->cause), value, sizeof(struct Cause));
			break;

		case S11_IE_FTEID_C:{
			#define S1U_SGW_FTEID 1 /*binary 0001*/
			if((0x0F & (unsigned char)(*value)) 
				== S1U_SGW_FTEID) {
				network_cp_fteid(&bearer->s1u_sgw_teid, value);
			}
			else { /*s5s8 pgw_U ftied*/
				network_cp_fteid(&bearer->s5s8_pgw_u_teid, value);
			}
			break;
		}

		case S11_IE_EPS_BEARER_ID:
			bearer->eps_bearer_id = (unsigned char)(*value);
			break;

		default:
		log_msg(LOG_ERROR, "Unhandled S11 bearer IE: %d\n", header->ie_type);
		}

		data += ntohs(header->ie_len) + sizeof(struct s11_IE_header); /*goto next IE*/
	}
	return SUCCESS;
}

int	
parse_gtpv2c_IEs(char *msg, int len, struct s11_proto_IE *proto_ies)
{
	proto_ies->no_of_ies = get_IE_cnt(msg, len);

	if(0 == proto_ies->no_of_ies) {
		log_msg(LOG_INFO, "No IEs recvd in message\n");
		return SUCCESS;
	}
	log_msg(LOG_INFO, "No of IEs - %d\n", proto_ies->no_of_ies);

	/*allocated IEs for message*/
	proto_ies->s11_ies = (struct s11_IE*)calloc(sizeof(struct s11_IE),
				proto_ies->no_of_ies);
	msg +=11;

	for(int i=0; i < proto_ies->no_of_ies; ++i) {
		struct s11_IE *ie = &(proto_ies->s11_ies[i]);
		char *data = msg + sizeof(struct s11_IE_header);

		memcpy(&(ie->header), msg, sizeof(struct s11_IE_header));

		switch(ie->header.ie_type){
		case S11_IE_CAUSE:
			memcpy(&(ie->data.cause), data, sizeof(struct Cause));
			break;

		case S11_IE_FTEID_C:{
			#define S11_SGW_C_FTEID 11 /*binary 1011*/
			if((0x0F & (unsigned char)(*data)) 
				== S11_SGW_C_FTEID) {
				network_cp_fteid(&(ie->data.s11_sgw_fteid), data);
			}
			else { /*s5s8 pgw_c ftied*/
				network_cp_fteid(&(ie->data.s5s8_pgw_c_fteid), data);
			}
			break;
		}

		case S11_IE_PAA: {
			memcpy(&(ie->data.pdn_addr.pdn_type), data,
				sizeof(ie->data.pdn_addr.pdn_type));
			memcpy(&(ie->data.pdn_addr.ip_type.ipv4), data+1, sizeof(int));
			break;
		}

		case S11_IE_APN_RESTRICTION:
			break;

		case S11_IE_BEARER_CTX:
			parse_bearer_ctx(&(ie->data.bearer), data, ntohs(ie->header.ie_len));
		break;

		default:
		log_msg(LOG_ERROR, "Unhandled S11 IE: %d\n", ie->header.ie_type);
		}

		msg += (ntohs(((struct s11_IE_header*)msg)->ie_len) + sizeof(struct s11_IE_header)) ; /*goto next IE*/
	}
	return SUCCESS;
}

void
handle_s11_message(void *message)
{
	struct gtpv2c_header *header = (struct gtpv2c_header*)message;
	
	log_msg(LOG_INFO, "S11 recv msg handler.\n");

	switch(header->gtp.message_type){
	case S11_GTP_CREATE_SESSION_RESP:
		s11_CS_resp_handler(message);
		break;

	case S11_GTP_MODIFY_BEARER_RESP:
		s11_MB_resp_handler(message);
		break;

	case S11_GTP_DELETE_SESSION_RESP:
		s11_DS_resp_handler(message);
		break;

	}
	return;
}
