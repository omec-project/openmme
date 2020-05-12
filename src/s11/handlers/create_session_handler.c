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
#include <errno.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage5_s11_info.h"
#include "gtpv2c.h"
#include "gtpv2c_ie.h"
#include "s11_config.h"
#include "gtpV2StackWrappers.h"

/************************************************************************
Current file : Stage 5 handler.
ATTACH stages :
	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage3 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage4 handler]-->esm infor req
-->	Stage 5 : esm infor resp-->[stage5 handler]-->create session
	Stage 6 : create session resp-->[stage6 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage7 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

/*S11 CP communication parameters*/
extern int g_s11_fd;
extern struct sockaddr_in g_s11_cp_addr;
extern socklen_t g_s11_serv_size;
extern pthread_mutex_t s11_net_lock;

static int g_Q_CS_fd;

extern s11_config g_s11_cfg;

/*Making global just to avoid stack passing*/
static char buf[S11_CSREQ_STAGE5_BUF_SIZE];

struct CS_Q_msg *g_csReqInfo;

extern struct GtpV2Stack* gtpStack_gp;
struct MsgBuffer*  csReqMsgBuf_p = NULL;

volatile uint32_t g_s11_sequence = 1;

/****Global and externs end***/

void
bswap8_array(uint8_t *src, uint8_t *dest, uint32_t len)
{
	for (uint32_t i=0; i<len; i++)
		dest[i] = ((src[i] & 0x0F)<<4 | (src[i] & 0xF0)>>4);

	return;
}

/**
 Transform the imsi format for s11 interface packet
*/
uint32_t
convert_imsi_to_digits_array(uint8_t *src, uint8_t *dest, uint32_t len)
{
	uint8_t msb_digit = 0;
	uint8_t lsb_digit = 0;
	uint8_t num_of_digits = 0;

	for(uint32_t i = 1; i <= len; i++)
	{
		msb_digit = ((src[i-1] & 0xF0) >> 4);
		dest[(i-1)*2] = msb_digit;

		if (msb_digit != 0x0F)
			num_of_digits++;

		if (i != len) {
			lsb_digit = (src[i] & 0x0F);
			dest[(i*2)-1] = lsb_digit;

			if (lsb_digit != 0x0F)
				num_of_digits++;
		}
	}

	return num_of_digits;
}

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	//test ipc
	log_msg(LOG_INFO, "stage 5 create session initializer.\n");

	if ((g_Q_CS_fd  = open_ipc_channel(S11_CSREQ_STAGE5_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader Create session request IPC.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "S11 reader - Create session request: Opened\n");

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

	memset(buf, 0, S11_CSREQ_STAGE5_BUF_SIZE);
	MsgBuffer_reset(csReqMsgBuf_p);

	while (bytes_read < S11_CSREQ_STAGE5_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_CS_fd, buf,
			S11_CSREQ_STAGE5_BUF_SIZE ))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Create session request received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
create_session_processing()
{
	g_csReqInfo = (struct CS_Q_msg *) buf;

	GtpV2MessageHeader gtpHeader;
	gtpHeader.msgType = GTP_CREATE_SESSION_REQ;
	gtpHeader.sequenceNumber = g_s11_sequence;
	gtpHeader.teidPresent = true;
	gtpHeader.teid = 0;

	g_s11_sequence++;

	CreateSessionRequestMsgData msgData;
	memset(&msgData, 0, sizeof(msgData));

	msgData.imsiIePresent = true;
	memset(msgData.imsi.imsiValue.digits, 0x0f, 16);

	uint8_t imsi_len =
			convert_imsi_to_digits_array(g_csReqInfo->IMSI,
					msgData.imsi.imsiValue.digits,
					BINARY_IMSI_LEN);

	msgData.imsi.imsiValue.length = imsi_len;
	log_msg(LOG_INFO, "IMSI Len: %d\n", imsi_len);

	msgData.msisdnIePresent = true;
	msgData.msisdn.msisdnValue.length = 10;
	for (uint8_t i = 1; i <= 5; i++)
	{
		msgData.msisdn.msisdnValue.digits[2*(i-1)] = (g_csReqInfo->MSISDN[i-1] & 0x0F);
		msgData.msisdn.msisdnValue.digits[(2*i) - 1] = ((g_csReqInfo->MSISDN[i-1] & 0xF0) >> 4);
	}

	struct TAI *tai = &(g_csReqInfo->tai);
	struct CGI *cgi = &(g_csReqInfo->utran_cgi);

	msgData.userLocationInformationIePresent = true;
	msgData.userLocationInformation.taipresent = true;
	msgData.userLocationInformation.ecgipresent = true;

	msgData.userLocationInformation.tai.trackingAreaCode = ntohs(tai->tac);
	msgData.userLocationInformation.tai.mccDigit1 = tai->plmn_id.idx[0] & 0x0F;
	msgData.userLocationInformation.tai.mccDigit2 = (tai->plmn_id.idx[0] & 0xF0) >> 4;
	msgData.userLocationInformation.tai.mccDigit3 = tai->plmn_id.idx[1] & 0x0F;
	msgData.userLocationInformation.tai.mncDigit1 = tai->plmn_id.idx[2] & 0x0F;
	msgData.userLocationInformation.tai.mncDigit2 = (tai->plmn_id.idx[2] & 0xF0) >> 4;
	msgData.userLocationInformation.tai.mncDigit3 = (tai->plmn_id.idx[1] & 0xF0) >> 4;

	msgData.userLocationInformation.ecgi.eUtranCellId = ntohl(cgi->cell_id);
	msgData.userLocationInformation.ecgi.mccDigit1 = cgi->plmn_id.idx[0] & 0x0F;
	msgData.userLocationInformation.ecgi.mccDigit2 = (cgi->plmn_id.idx[0] & 0xF0) >> 4;
	msgData.userLocationInformation.ecgi.mccDigit3 = cgi->plmn_id.idx[1] & 0x0F;
	msgData.userLocationInformation.ecgi.mncDigit1 = cgi->plmn_id.idx[2] & 0x0F;
	msgData.userLocationInformation.ecgi.mncDigit2 = (cgi->plmn_id.idx[2] & 0xF0) >> 4;
	msgData.userLocationInformation.ecgi.mncDigit3 = (cgi->plmn_id.idx[1] & 0xF0) >> 4;

	msgData.servingNetworkIePresent = true;
	msgData.servingNetwork.mccDigit1 = tai->plmn_id.idx[0] & 0x0F;
	msgData.servingNetwork.mccDigit2 = (tai->plmn_id.idx[0] & 0xF0) >> 4;
	msgData.servingNetwork.mccDigit3 = tai->plmn_id.idx[1] & 0x0F;
	msgData.servingNetwork.mncDigit1 = tai->plmn_id.idx[2] & 0x0F;
	msgData.servingNetwork.mncDigit2 = (tai->plmn_id.idx[2] & 0xF0) >> 4;
	msgData.servingNetwork.mncDigit3 = (tai->plmn_id.idx[1] & 0xF0) >> 4;

	msgData.ratType.ratType = 6;

	msgData.indicationFlagsIePresent = true;
	msgData.indicationFlags.iMSV = true;

	msgData.senderFTeidForControlPlane.ipv4present = true;
	msgData.senderFTeidForControlPlane.interfaceType = 10;
	msgData.senderFTeidForControlPlane.ipV4Address.ipValue = g_s11_cfg.local_egtp_ip; /* network byte ordered */
	msgData.senderFTeidForControlPlane.teidGreKey = g_csReqInfo->ue_idx; /* Control is in the MME-app to give TEID */

	msgData.pgwS5S8AddressForControlPlaneOrPmipIePresent = true;
	msgData.pgwS5S8AddressForControlPlaneOrPmip.ipv4present = true;
	msgData.pgwS5S8AddressForControlPlaneOrPmip.interfaceType = 7;
	msgData.pgwS5S8AddressForControlPlaneOrPmip.ipV4Address.ipValue = ntohl(g_s11_cfg.pgw_ip);

	msgData.accessPointName.apnValue.count =
			g_csReqInfo->selected_apn.len + 1;
	memcpy(msgData.accessPointName.apnValue.values,
			&(g_csReqInfo->selected_apn.len), 1);
	memcpy(msgData.accessPointName.apnValue.values + 1,
			g_csReqInfo->selected_apn.val, g_csReqInfo->selected_apn.len);

	msgData.selectionModeIePresent = true;
	msgData.selectionMode.selectionMode = 1;

	msgData.pdnTypeIePresent = true;
	msgData.pdnType.pdnType = 1;

	msgData.pdnAddressAllocationIePresent = true;
	msgData.pdnAddressAllocation.pdnType = 1;
	msgData.pdnAddressAllocation.ipV4Address.ipValue = g_csReqInfo->paa_v4_addr; /* host order - Get value from MME */

	msgData.maximumApnRestrictionIePresent = true;
	msgData.maximumApnRestriction.restrictionValue = 0;

	/* Bearer Context */
	msgData.bearerContextsToBeCreatedCount = 1;
	msgData.bearerContextsToBeCreated[0].epsBearerId.epsBearerId = 5;

	msgData.bearerContextsToBeCreated[0].bearerLevelQos.pci = 1;
	msgData.bearerContextsToBeCreated[0].bearerLevelQos.pl = 11;
	msgData.bearerContextsToBeCreated[0].bearerLevelQos.pvi = 0;
	msgData.bearerContextsToBeCreated[0].bearerLevelQos.qci = 9;

	uint32_t mbr_uplink = htonl(MBR_UPLINK);
	uint32_t mbr_downlink = htonl(MBR_DOWNLINK);

	msgData.bearerContextsToBeCreated[0].bearerLevelQos.maxBitRateUl.count = 5;
	msgData.bearerContextsToBeCreated[0].bearerLevelQos.maxBitRateDl.count = 5;
	memcpy(&msgData.bearerContextsToBeCreated[0].bearerLevelQos.maxBitRateUl.values, &mbr_uplink, sizeof(mbr_uplink));
	memcpy(&msgData.bearerContextsToBeCreated[0].bearerLevelQos.maxBitRateDl.values, &mbr_downlink, sizeof(mbr_downlink));
	msgData.bearerContextsToBeCreated[0].bearerLevelQos.guraranteedBitRateUl.count = 5;
	msgData.bearerContextsToBeCreated[0].bearerLevelQos.guaranteedBitRateDl.count = 5;

	msgData.aggregateMaximumBitRateIePresent = true;
	msgData.aggregateMaximumBitRate.maxMbrUplink = g_csReqInfo->max_requested_bw_ul;
	msgData.aggregateMaximumBitRate.maxMbrDownlink = g_csReqInfo->max_requested_bw_dl;

    log_msg(LOG_INFO, "PCO length = %d\n", g_csReqInfo->pco_length);
    if(g_csReqInfo->pco_length > 0)
    {
        msgData.protocolConfigurationOptionsIePresent = true;
        msgData.protocolConfigurationOptions.pcoValue.count = g_csReqInfo->pco_length;
        memcpy(&msgData.protocolConfigurationOptions.pcoValue.values[0], &g_csReqInfo->pco_options[0], g_csReqInfo->pco_length);
    }

	GtpV2Stack_buildGtpV2Message(gtpStack_gp, csReqMsgBuf_p, &gtpHeader, &msgData);

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	log_msg(LOG_INFO, "send %d bytes.\n", MsgBuffer_getBufLen(csReqMsgBuf_p));

	int res = sendto (
			g_s11_fd,
			MsgBuffer_getDataPointer(csReqMsgBuf_p),
			MsgBuffer_getBufLen(csReqMsgBuf_p), 0,
			(struct sockaddr*)&g_s11_cp_addr,
			g_s11_serv_size);

	if (res < 0) {
		log_msg(LOG_ERROR,"Error in sendto in detach stage 3 post to next\n");
	}

	/* TODO: Add error handling */

	log_msg(LOG_INFO,"%d bytes sent. Err : %d, %s\n",res,errno,
			strerror(errno));
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_create_session()
{
	close_ipc_channel(g_Q_CS_fd);
	log_msg(LOG_INFO, "Shutdown create session handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
create_session_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Create sesssion handler initialized\n");

	while(1){
		read_next_msg();

		create_session_processing();

		post_to_next();
	}

	return NULL;
}
