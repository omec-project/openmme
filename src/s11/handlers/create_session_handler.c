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
#include <errno.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage5_s11_info.h"
#include "gtpv2c.h"
#include "gtpv2c_ie.h"
#include "s11_config.h"

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

static uint8_t g_udp_buf[4096];
static uint32_t g_udp_buf_size;

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
void
format_imsi_for_s11(uint8_t *src, uint8_t *dest, uint32_t len)
{
        // Change it to a human readable number
        uint8_t imsi_tmp[BINARY_IMSI_LEN];
        bswap8_array(src, imsi_tmp, BINARY_IMSI_LEN);

        // Remove the extra 4 bits and fill in 1 according to the spec
        for (uint32_t i = 0; i < len - 1; i++){
                dest[i] = ( ( imsi_tmp[i] & 0x0F ) << 4 ) | ( ( imsi_tmp[i + 1] & 0xF0 ) >> 4 );
        }
        dest[len - 1] = ( ( imsi_tmp[len - 1] & 0x0f ) << 4 ) | ( 0xF0 >> 4) ;
        bswap8_array(dest, dest, BINARY_IMSI_LEN);

        return;
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
	fteid_ie ftied;
	uint32_t ieCount = 0;
	uint32_t ieSize = 0;
	uint8_t u8Value;
	uint8_t imsi[BINARY_IMSI_LEN];

	g_csReqInfo = (struct CS_Q_msg *) buf;

	struct gtpv2c_header *gtpv2c_s11_tx =
			(struct gtpv2c_header *)g_udp_buf;

	set_gtpv2c_header(gtpv2c_s11_tx, GTP_CREATE_SESSION_REQ, 0, g_s11_sequence);

	gtpv2c_ie ies[15];

	// check imsi odd or even, then handle it differently.The current IMSI stores
	// the 4 bits of EPS mobility identity, which indicates "Odd/even indication"
	// and "Type of identity", so here we use IMSI to check.
	if ( (g_csReqInfo->IMSI[0] & 0x08) != 0  ){
		// odd
		format_imsi_for_s11(g_csReqInfo->IMSI, imsi, BINARY_IMSI_LEN);
	}else {
		// even
		bswap8_array(g_csReqInfo->IMSI, imsi, BINARY_IMSI_LEN);

	}
	ies[ieCount].type = IE_IMSI;
	ies[ieCount].length = htons(BINARY_IMSI_LEN);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, imsi, BINARY_IMSI_LEN);
	ieCount++;

	ies[ieCount].type = IE_MSISDN;
	ies[ieCount].length = htons(5);
	ies[ieCount].instance = INSTANCE_ZERO;
	bswap8_array(g_csReqInfo->MSISDN, ies[ieCount].value, 5);
	ieCount++;

	ies[ieCount].type = IE_ULI;
	ies[ieCount].length = htons(13);
	ies[ieCount].instance = INSTANCE_ZERO;
	u8Value = 24; /* ULI flags value, ECGI Present and TAI present */
	memcpy(ies[ieCount].value, &u8Value, sizeof(u8Value));
	ieSize = sizeof(u8Value);
	memcpy(ies[ieCount].value + ieSize, &(g_csReqInfo->tai),
			sizeof(g_csReqInfo->tai));
	ieSize += sizeof(g_csReqInfo->tai);
	memcpy(ies[ieCount].value + ieSize, &(g_csReqInfo->utran_cgi),
			sizeof(g_csReqInfo->utran_cgi));
	ieCount++;

	ies[ieCount].type = IE_SERVING_NETWORK;
	ies[ieCount].length = htons(3);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, g_csReqInfo->tai.plmn_id.idx, 3);
	ieCount++;

	u8Value = 1;
	ies[ieCount].type = IE_RAT_TYPE;
	ies[ieCount].length = htons(1);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &u8Value, sizeof(u8Value));
	ieCount++;

	ies[ieCount].type = IE_INDICATION;
	ies[ieCount].length = htons(3);
	ies[ieCount].instance = INSTANCE_ZERO;
	u8Value = 0x10;
	memcpy(ies[ieCount].value, &u8Value, sizeof(u8Value));
	u8Value = 0x01;
	memcpy(ies[ieCount].value + 1 , &u8Value, sizeof(u8Value));
	u8Value = 0x0;
	memcpy(ies[ieCount].value + 2, &u8Value, sizeof(u8Value));
	ieCount++;

	/* TODO: Remove hardcoded values */
	ftied.iface_type = 10;
	ftied.ipv4 = 1;
	ftied.ipv6 = 0;
	ftied.teid = htonl(g_csReqInfo->ue_idx);
	ftied.ipaddr.ipv4 = htonl(g_s11_cfg.local_egtp_ip);
	ies[ieCount].type = IE_FTEID;
	ies[ieCount].length = htons(9);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &ftied, 9);
	ieCount++;


	ftied.iface_type = 7;
	ftied.ipv4 = 1;
	ftied.ipv6 = 0;
	ftied.teid = 0x00000000;
	ftied.ipaddr.ipv4 = htonl(g_s11_cfg.pgw_ip);
	ies[ieCount].type = IE_FTEID;
	ies[ieCount].length = htons(9);
	ies[ieCount].instance = INSTANCE_ONE;
	memcpy(ies[ieCount].value, &ftied, 9);
	ieCount++;


	ies[ieCount].type = IE_APN;
	ies[ieCount].length = htons(g_csReqInfo->apn.len);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, g_csReqInfo->apn.val,
			g_csReqInfo->apn.len);
	ieCount++;

	uint32_t ambr_uplink = htonl(g_csReqInfo->max_requested_bw_ul);
	uint32_t ambr_downlink = htonl(g_csReqInfo->max_requested_bw_dl);
	ies[ieCount].type = IE_AMBR;
	ies[ieCount].length = htons(8);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &ambr_uplink,
			sizeof(ambr_uplink));
	memcpy(ies[ieCount].value + 4, &ambr_downlink,
			sizeof(ambr_downlink));
	ieCount++;

	u8Value = 0;
	ies[ieCount].type = IE_SELECTION_MODE;
	ies[ieCount].length = htons(1);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &u8Value, sizeof(u8Value));
	ieCount++;

	u8Value = 1;
	ies[ieCount].type = IE_PDN_TYPE;
	ies[ieCount].length = htons(1);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &u8Value, sizeof(u8Value));
	ieCount++;

	/* TODO : What should be value of PDN Address and prefix */
	char tmpStr[4] = {0,0,0,0};
	u8Value = 1;
	ies[ieCount].type = IE_PAA;
	ies[ieCount].length = htons(5);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &u8Value, sizeof(u8Value));
	memcpy(ies[ieCount].value + 1, tmpStr, 4);
	ieCount++;

	u8Value = 0;
	ies[ieCount].type = IE_APN_RESTRICTION;
	ies[ieCount].length = htons(1);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &u8Value, sizeof(u8Value));
	ieCount++;

	gtpv2c_ie bearer[2];
	u8Value = 5;
	bearer[0].type = IE_EBI;
	bearer[0].length = htons(1);
	bearer[0].instance = INSTANCE_ZERO;
	memcpy(bearer[0].value, &u8Value, sizeof(u8Value));

	u8Value = 236;
	bearer[1].type = IE_BEARER_QOS;
	bearer[1].length = htons(22);
	bearer[1].instance = INSTANCE_ZERO;
	memcpy(bearer[1].value, &u8Value, sizeof(u8Value));
	u8Value = 9;
	memcpy(bearer[1].value + 1, &u8Value, sizeof(u8Value));
	uint32_t mbr_uplink = htonl(MBR_UPLINK);
	uint32_t mbr_downlink = htonl(MBR_DOWNLINK);
	uint32_t gbr_uplink = htonl(0);
	uint32_t gbr_downlink = htonl(0);
	memcpy(bearer[1].value + 2, &mbr_uplink, sizeof(mbr_uplink));
	memcpy(bearer[1].value + 6, &mbr_downlink, sizeof(mbr_downlink));
	memcpy(bearer[1].value + 10, &gbr_uplink, sizeof(gbr_uplink));
	memcpy(bearer[1].value + 14, &gbr_downlink, sizeof(gbr_downlink));

	ies[ieCount].type = IE_BEARER_CONTEXT;
	ies[ieCount].length = htons(31);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &bearer[0], ntohs(bearer[0].length) +  4);
	memcpy(ies[ieCount].value + ntohs(bearer[0].length) + 4,
			&bearer[1], ntohs(bearer[1].length) +  4);
	ieCount++;

	g_udp_buf_size = ntohs(gtpv2c_s11_tx->gtp.len) + 4;
	for (int i=0; i<ieCount; i++) {
		memcpy(g_udp_buf + g_udp_buf_size, &ies[i], ntohs(ies[i].length) +4);
		g_udp_buf_size += ntohs(ies[i].length) + 4;
	}

	gtpv2c_s11_tx->gtp.len = htons(g_udp_buf_size - 4);

	g_s11_sequence++;

	return SUCCESS;

}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	log_msg(LOG_INFO, "send %d bytes.\n", g_udp_buf_size);
	int res = sendto(g_s11_fd, g_udp_buf, g_udp_buf_size, 0,
			(struct sockaddr*)&g_s11_cp_addr, g_s11_serv_size);

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
