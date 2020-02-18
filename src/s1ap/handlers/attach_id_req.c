/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "log.h"
#include "err_codes.h"
#include "s1ap.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "main.h"
#include "sctp_conn.h"
#include "stage2_info.h"

/****Globals and externs ***/

/*Making global just to avoid stack passing*/
static char buf[S1AP_ID_REQ_BUF_SIZE];
ipc_handle ipcHndl_s1ap_attach_id_req;

static struct attachIdReq_info *g_attachIdReqInfo;
static struct Buffer g_buffer;
static struct Buffer g_value_buffer;
static struct Buffer g_nas_buffer;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((ipcHndl_s1ap_attach_id_req = open_ipc_channel(
				S1AP_ID_REQ_QUEUE, IPC_READ)) == -1) {
		log_msg(LOG_ERROR, "Error in opening reader for s1ap id request IPC"
				"channel : %s\n", S1AP_ID_REQ_QUEUE );
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "s1ap request queue reader: Connected.\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_ID_REQ_BUF_SIZE);
	while (bytes_read < S1AP_ID_REQ_BUF_SIZE) {
		if ((bytes_read = read_ipc_channel(
				ipcHndl_s1ap_attach_id_req , buf,
				S1AP_ID_REQ_BUF_SIZE )) == -1) {
					log_msg(LOG_ERROR, "Error reading s1ap ID Q \n");
					/* TODO : Add proper error handling */
				}
		log_msg(LOG_INFO, "S1ap id request message received from mme on Q len-%d", bytes_read);
	}

	return bytes_read;
}

/**
* Get ProtocolIE value for Auth Request sent by mme-app
*/
static int
get_attach_id_request_protoie_value(struct proto_IE *value)
{
	value->no_of_IEs = ATTACH_ID_REQUEST_NO_OF_IES;

	value->data = (proto_IEs *) malloc(ATTACH_ID_REQUEST_NO_OF_IES*
			sizeof(proto_IEs));

	value->data[0].val.mme_ue_s1ap_id = g_attachIdReqInfo->ue_idx;
	value->data[1].val.enb_ue_s1ap_id = g_attachIdReqInfo->s1ap_enb_ue_id;

	log_msg(LOG_INFO, "mme_ue_s1ap_id %d and enb_ue_s1ap_id %d\n",
			g_attachIdReqInfo->ue_idx, g_attachIdReqInfo->s1ap_enb_ue_id);

	/* TODO: Add enum for security header type */
	value->data[2].val.nas.header.security_header_type = 0;
	value->data[2].val.nas.header.proto_discriminator = EPSMobilityManagementMessages;
	value->data[2].val.nas.header.message_type = IdentityRequest;
	value->data[2].val.nas.header.nas_security_param = 0;

	return SUCCESS;
}


/**
* Stage specific message processing.
*/
static int
s1ap_attach_id_req_processing()
{
	struct s1ap_PDU s1apPDU;

	g_attachIdReqInfo = (struct attachIdReq_info *) buf;

	/* Assigning values to s1apPDU */
	s1apPDU.procedurecode = id_downlinkNASTransport;
	s1apPDU.criticality = CRITICALITY_IGNORE;

	get_attach_id_request_protoie_value(&s1apPDU.value);

	/* Copy values to buffer from s1apPDU */

	g_buffer.pos = 0;

	uint8_t initiating_message = 0; /* TODO: Add enum */
	buffer_copy(&g_buffer, &initiating_message,
			sizeof(initiating_message));

	buffer_copy(&g_buffer, &s1apPDU.procedurecode,
			sizeof(s1apPDU.procedurecode));

	buffer_copy(&g_buffer, &s1apPDU.criticality,
			sizeof(s1apPDU.criticality));

	/* Copy values in g_value_buffer */
	g_value_buffer.pos = 0;

	/* TODO remove hardcoded values */
	unsigned char chProtoIENo[3] = {0,0,3};

	buffer_copy(&g_value_buffer, chProtoIENo, 3);

	unsigned char tmpStr[4];

	/* id-MME-UE-S1AP-ID */
	uint16_t protocolIe_Id = id_MME_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_value_buffer, tmpStr,
					sizeof(protocolIe_Id));

	uint8_t protocolIe_criticality = CRITICALITY_REJECT;
	buffer_copy(&g_value_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));

	uint8_t datalen = 2;

	/* TODO needs proper handling*/
	unsigned char mme_ue_id[3];
	datalen = copyU16(mme_ue_id,
			s1apPDU.value.data[0].val.mme_ue_s1ap_id);
	buffer_copy(&g_value_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_value_buffer, mme_ue_id, datalen);

	/* id-eNB-UE-S1AP-ID */

	protocolIe_Id = id_eNB_UE_S1AP_ID;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_value_buffer, tmpStr,
						sizeof(protocolIe_Id));

	buffer_copy(&g_value_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));


	/* TODO needs proper handling*/
	unsigned char enb_ue_id[3];
	datalen = copyU16(enb_ue_id,
			s1apPDU.value.data[1].val.enb_ue_s1ap_id);
	buffer_copy(&g_value_buffer, &datalen, sizeof(datalen));
	buffer_copy(&g_value_buffer, enb_ue_id, datalen);

	/* id-NAS-PDU */
	protocolIe_Id = id_NAS_PDU;
	copyU16(tmpStr, protocolIe_Id);
	buffer_copy(&g_value_buffer, tmpStr,
						sizeof(protocolIe_Id));

	buffer_copy(&g_value_buffer, &protocolIe_criticality,
					sizeof(protocolIe_criticality));

	struct nasPDU *nas = &(s1apPDU.value.data[2].val.nas);
	uint8_t value = (nas->header.security_header_type) |
			nas->header.proto_discriminator;

	g_nas_buffer.pos = 0;

	buffer_copy(&g_nas_buffer, &value, sizeof(value));

	buffer_copy(&g_nas_buffer, &nas->header.message_type,
						sizeof(nas->header.message_type));

    value = g_attachIdReqInfo->ue_type; 
	buffer_copy(&g_nas_buffer, &value, sizeof(value));

	datalen = g_nas_buffer.pos + 1;

	buffer_copy(&g_value_buffer, &datalen,
						sizeof(datalen));

	buffer_copy(&g_value_buffer, &g_nas_buffer.pos,
						sizeof(g_nas_buffer.pos));


	buffer_copy(&g_value_buffer, &g_nas_buffer,
						g_nas_buffer.pos);

	buffer_copy(&g_buffer, &g_value_buffer.pos,
						sizeof(g_value_buffer.pos));

	buffer_copy(&g_buffer, &g_value_buffer,
						g_value_buffer.pos);

	free(s1apPDU.value.data);

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	send_sctp_msg(g_attachIdReqInfo->enb_fd, g_buffer.buf, g_buffer.pos,1);
	log_msg(LOG_INFO, "\n-----Stage2 completed.---\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_s1apIdReqstage()
{
	close_ipc_channel(ipcHndl_s1ap_attach_id_req);
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
s1ap_attach_id_req_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "S1Ap attach Id Request handler ready.\n");

	while(1){
		read_next_msg();

		s1ap_attach_id_req_processing();

		post_to_next();
	}

	return NULL;
}

