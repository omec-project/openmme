/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "s11_structs.h"
#include "stage7_info.h"
#include "gtpv2c.h"
#include "gtpv2c_ie.h"
#include "gtpV2StackWrappers.h"

/************************************************************************
Current file : Stage 7 handler. To listen MB from mme-app and fwd to CP
ATTACH stages :
	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage3 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage4 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage5 handler]-->create session
	Stage 6 : create session resp-->[stage6 handler]-->init ctx setup
-->	Stage 7 : attach complete-->[stage7 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

static int g_Q_MB_fd;
extern int g_s11_fd;

extern struct sockaddr_in g_s11_cp_addr;
extern socklen_t g_s11_serv_size;

/*Making global just to avoid stack passing*/
static char buf[S11_MBREQ_STAGE7_BUF_SIZE];

/*TODO: S11 protocol sequence number - need to make it atomic. multiple thread to access this*/
extern volatile uint32_t g_s11_sequence;

struct MsgBuffer*  mbReqMsgBuf_p = NULL;
extern struct GtpV2Stack* gtpStack_gp;

/****Global and externs end***/

/**
Initialize the stage settings, Q, 
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "Stag 7 modify bearer initializer\n");
	if ((g_Q_MB_fd  = open_ipc_channel(S11_MBREQ_STAGE7_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error starting reader Modify bearer"\
			" request IPC.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "S11 reader - Modify bearer request: Opened\n");

	/*Open destination queue for writing. It is AIR, ULR Q in this stage*/
	log_msg(LOG_INFO, "S11 interface writer: waiting\n");
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S11_MBREQ_STAGE7_BUF_SIZE);
	MsgBuffer_reset(mbReqMsgBuf_p);

	while (bytes_read < S11_MBREQ_STAGE7_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_MB_fd, buf, 
			S11_MBREQ_STAGE7_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Modify bearer request received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
modify_bearer_processing()
{
	struct MB_Q_msg *mb_msg = (struct MB_Q_msg *)buf;

	GtpV2MessageHeader gtpHeader;
	gtpHeader.msgType = GTP_MODIFY_BEARER_REQ;
	gtpHeader.sequenceNumber = g_s11_sequence;
	gtpHeader.teidPresent = true;
	gtpHeader.teid = mb_msg->s11_sgw_c_fteid.header.teid_gre;

	g_s11_sequence++;

	ModifyBearerRequestMsgData msgData;
	memset(&msgData, 0, sizeof(msgData));
	msgData.bearerContextsToBeModifiedCount = 1;
	msgData.bearerContextsToBeModified[0].epsBearerId.epsBearerId = 5;
	msgData.bearerContextsToBeModified[0].s1EnodebFTeidIePresent = true;
	msgData.bearerContextsToBeModified[0].s1EnodebFTeid.ipv4present = true;
	msgData.bearerContextsToBeModified[0].s1EnodebFTeid.interfaceType = mb_msg->s1u_enb_fteid.header.iface_type;
	msgData.bearerContextsToBeModified[0].s1EnodebFTeid.teidGreKey = mb_msg->s1u_enb_fteid.header.teid_gre;
	msgData.bearerContextsToBeModified[0].s1EnodebFTeid.ipV4Address.ipValue = mb_msg->s1u_enb_fteid.ip.ipv4.s_addr;

	GtpV2Stack_buildGtpV2Message(gtpStack_gp, mbReqMsgBuf_p, &gtpHeader, &msgData);

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int 
post_to_next()
{
	sendto(g_s11_fd,
			MsgBuffer_getDataPointer(mbReqMsgBuf_p),
			MsgBuffer_getBufLen(mbReqMsgBuf_p), 0,
			(struct sockaddr*)&g_s11_cp_addr,
			g_s11_serv_size);

	//TODO " error chk, eagain etc?	
	log_msg(LOG_INFO, "Modify beader send, len - %d bytes.\n", MsgBuffer_getBufLen(mbReqMsgBuf_p));

	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_modify_bearer()
{
	close_ipc_channel(g_Q_MB_fd);
	log_msg(LOG_INFO, "Shutdown modify bearer handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
modify_bearer_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Modify bearer handler initialized\n");
	
	while(1){
		read_next_msg();

		modify_bearer_processing();

		post_to_next();
	}

	return NULL;
}
