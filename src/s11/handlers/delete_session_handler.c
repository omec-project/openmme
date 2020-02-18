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

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "gtpv2c.h"
#include "gtpv2c_ie.h"
#include "detach_stage1_info.h"
#include "gtpV2StackWrappers.h"

/************************************************************************
Current file : Stage 1 handler.
ATTACH stages :
	Stage 1 : detach request -->delete session
**************************************************************************/

/****Globals and externs ***/

/*S11 CP communication parameters*/
extern int g_s11_fd;
extern struct sockaddr_in g_s11_cp_addr;
extern socklen_t g_s11_serv_size;
extern pthread_mutex_t s11_net_lock;

static int g_Q_DS_fd;

/*Making global just to avoid stack passing*/
static char buf[S11_DTCHREQ_STAGE1_BUF_SIZE];

struct thread_pool *g_tpool;

extern struct GtpV2Stack* gtpStack_gp;
extern volatile uint32_t g_s11_sequence;

struct MsgBuffer*  dsReqMsgBuf_p = NULL;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	//test ipc
	log_msg(LOG_INFO, "stage 1 delete session initializer.\n");

	if ((g_Q_DS_fd  = open_ipc_channel(S11_DTCHREQ_STAGE1_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader Delete session request IPC.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "S11 reader - Delete session request: Opened\n");

	/*Open destination queue for writing. It is AIR, ULR Q in this stage*/
//	log_msg(LOG_INFO, "S11 interface writer: waiting\n");
/*
	g_Q_CSreq_fd = open_ipc_channel(S11_CSREQ_STAGE5_QUEUE , IPC_WRITE);
	if (g_Q_CSreq_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S11 CS Request\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 5 writer - s11 CS request: Opened\n");
*/
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S11_DTCHREQ_STAGE1_BUF_SIZE);
	MsgBuffer_reset(dsReqMsgBuf_p);

	while (bytes_read < S11_DTCHREQ_STAGE1_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
				g_Q_DS_fd, buf,
				S11_DTCHREQ_STAGE1_BUF_SIZE )) == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, " Delete session request received - Len: %d\n",
			bytes_read);
	}


	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
delete_session_processing()
{
	struct DS_Q_msg *ds_msg = (struct DS_Q_msg *) buf;

	GtpV2MessageHeader gtpHeader;
	gtpHeader.msgType = GTP_DELETE_SESSION_REQ;
	gtpHeader.sequenceNumber = g_s11_sequence;
	gtpHeader.teidPresent = true;
	gtpHeader.teid = ds_msg->s11_sgw_c_fteid.header.teid_gre;

	DeleteSessionRequestMsgData msgData;
	memset(&msgData, 0, sizeof(DeleteSessionRequestMsgData));

	msgData.indicationFlagsIePresent = true;
	msgData.indicationFlags.iOI = true;

	msgData.linkedEpsBearerIdIePresent = true;
	msgData.linkedEpsBearerId.epsBearerId = ds_msg->bearer_id;

	GtpV2Stack_buildGtpV2Message(gtpStack_gp, dsReqMsgBuf_p, &gtpHeader, &msgData);

	g_s11_sequence++;

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	sendto(g_s11_fd,
			MsgBuffer_getDataPointer(dsReqMsgBuf_p),
			MsgBuffer_getBufLen(dsReqMsgBuf_p), 0,
			(struct sockaddr*)&g_s11_cp_addr, g_s11_serv_size);

	//TODO " error chk, eagain etc?
	log_msg(LOG_INFO, "Send delete session request\n");

	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_delete_session()
{
	close_ipc_channel(g_Q_DS_fd);
	log_msg(LOG_INFO, "Shutdown create session handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
delete_session_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Delete session handler initialized\n");

	while(1){

		read_next_msg();

		delete_session_processing();

		post_to_next();
	}

	return NULL;
}

