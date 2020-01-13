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

extern int g_enb_fd;
extern s1ap_config g_s1ap_cfg;
static struct Buffer resp_buf;

int
create_s1setup_response(/*enb info,*/unsigned char **s1_setup_resp)
{
	unsigned char data_len = 0;
	unsigned char msg[50];
	struct Buffer proto_ies;
	struct Buffer gummies;
	uint16_t proto_ie_id;
	unsigned char tmp_str[4];
	uint8_t criticality;

	/*Leave a byte to fill length*/
	resp_buf.pos = 0;
	/*Only in case of s1setup resp, first byte is 0x20, not for any other
	s1ap message. Nothing found in specs, please check.*/
	/**procedureCode: id-S1Setup (17)**/
	msg[0] = 0x20;
	msg[1] = S1AP_SETUP_REQUEST_CODE;
	msg[2] = CRITICALITY_REJECT;
	buffer_copy(&resp_buf, msg, 3);

	/**IE1*/
	/**Item 0: id-MMEname*/
	proto_ie_id = S1AP_IE_MMENAME;
	copyU16(tmp_str, proto_ie_id);
	buffer_copy(&proto_ies, tmp_str, sizeof(proto_ie_id));
	criticality = CRITICALITY_IGNORE;
	buffer_copy(&proto_ies, &criticality, sizeof(criticality));

	data_len = strlen(g_s1ap_cfg.mme_name);
	data_len = copyU16(tmp_str, data_len);
	tmp_str[1] = tmp_str[1]+2;
	buffer_copy(&proto_ies, &tmp_str[1], 1);
	proto_ies.buf[proto_ies.pos++] = 0x06;/*quest: what is this in encoding?*/
	proto_ies.buf[proto_ies.pos++] = 0x80;
	buffer_copy(&proto_ies, g_s1ap_cfg.mme_name, strlen(g_s1ap_cfg.mme_name));

	/*IE2*/
	/**Item 1: id-ServedGUMMEIs*/
	proto_ie_id = S1AP_IE_SERVED_GUMMEIES;
	copyU16(tmp_str, proto_ie_id);
	buffer_copy(&proto_ies, tmp_str, sizeof(proto_ie_id));
	criticality = CRITICALITY_REJECT;
	buffer_copy(&proto_ies, &criticality, sizeof(criticality));

	//msg[i++] = 0x0b;//len
	gummies.buf[0]=0x0;
	gummies.buf[1]=0x0;
	gummies.pos = 2;

	/**Item 1: id-ServedGUMMEIs
	 *       servedPLMNs: 1 item*/
	buffer_copy(&gummies, &(g_s1ap_cfg.mme_plmn_id), sizeof(struct PLMN));
	gummies.buf[gummies.pos++]=0x0;
	gummies.buf[gummies.pos++]=0x0;

	/**Item 1: id-ServedGUMMEIs
	 *       servedGroupIDs: 1 item*/
	data_len = copyU16(tmp_str, g_s1ap_cfg.mme_group_id);
	buffer_copy(&gummies, tmp_str, data_len);

	/**Item 1: id-ServedGUMMEIs
	 *       servedMMECs: 1 item*/
	gummies.buf[gummies.pos++]=0x0;
	gummies.buf[gummies.pos++] = g_s1ap_cfg.mme_code;

	data_len = copyU16(tmp_str, gummies.pos);
	buffer_copy(&proto_ies, &(tmp_str[1]), 1);
	buffer_copy(&proto_ies, &gummies.buf, gummies.pos);

	/*IE3*/
	/**id: id-RelativeMMECapacity (87)*/
	proto_ie_id = S1AP_IE_REL_MME_CAPACITY;
	copyU16(tmp_str, proto_ie_id);
	buffer_copy(&proto_ies, tmp_str, sizeof(proto_ie_id));
	criticality = CRITICALITY_IGNORE;
	buffer_copy(&proto_ies, &criticality, sizeof(criticality));
	data_len = 1;
	buffer_copy(&proto_ies, &(data_len), 1);
	g_s1ap_cfg.rel_cap = 1;
	buffer_copy(&proto_ies, &(g_s1ap_cfg.rel_cap), 1);

	/*number of proto IEs = 3*/
	data_len = copyU16(tmp_str, 3);

	data_len = data_len + proto_ies.pos + 1;
	buffer_copy(&resp_buf, &data_len, 1);

	resp_buf.buf[resp_buf.pos++] = 0;/*quest: packed value should be 2 bytes...
									   here it needs 3 bytes*/
	buffer_copy(&resp_buf, tmp_str, 2);

	buffer_copy(&resp_buf, &proto_ies, proto_ies.pos);
	*s1_setup_resp = resp_buf.buf;

	return resp_buf.pos;
}

int
s1_setup_handler(InitiatingMessage_t *msg, int enb_fd)
{
	unsigned char *resp_msg = NULL;
	int resp_len = 0;

	/*Validate all eNB info*/

	/*Add eNB info to hash*/

	/*Create S1Setup response*/
	resp_len = create_s1setup_response(/*enb info,*/ &resp_msg);

	/*Send S1Setup response*/
	log_msg(LOG_INFO, "Send s1setup response.\n");
	resp_len = send_sctp_msg(enb_fd, resp_msg, resp_len, 0);
	log_msg(LOG_INFO, "send len %d\n", resp_len);
	//free(resp_msg);

	return SUCCESS;
}

