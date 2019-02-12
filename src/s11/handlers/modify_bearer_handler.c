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
extern pthread_mutex_t s11_net_lock;

/*Making global just to avoid stack passing*/
static char buf[S11_MBREQ_STAGE7_BUF_SIZE];

/*TODO: S11 protocol sequence number - need to make it atomic. multiple thread to access this*/
extern volatile uint32_t g_s11_sequence;

static uint8_t g_udp_buf[4096];
static uint32_t g_udp_buf_size;

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
	uint32_t ieCount = 0;
	uint8_t u8Value;

	struct gtpv2c_header *gtpv2c_s11_tx =
			(struct gtpv2c_header *)g_udp_buf;

	set_gtpv2c_header(gtpv2c_s11_tx, GTP_MODIFY_BEARER_REQ,
			mb_msg->s11_sgw_c_fteid.header.teid_gre,
			g_s11_sequence);

	/*Only 2 mandatory IEs for MB*/
	gtpv2c_ie ies[2];

	ies[ieCount].type = IE_INDICATION;
	ies[ieCount].length = htons(3);
	ies[ieCount].instance = INSTANCE_ZERO;
	#if 0
	u8Value = 0x10;
	memcpy(ies[ieCount].value, &u8Value, sizeof(u8Value));
	u8Value = 0x01;
	memcpy(ies[ieCount].value + 1 , &u8Value, sizeof(u8Value));
	u8Value = 0x0;
	memcpy(ies[ieCount].value + 2, &u8Value, sizeof(u8Value));
	#endif

	memcpy(ies[ieCount].value, mb_msg->indication,
		S11_MB_INDICATION_FLAG_SIZE);
	ieCount++;

	gtpv2c_ie bearer[2];
	u8Value = 5;
	bearer[0].type = IE_EBI;
	bearer[0].length = htons(1);
	bearer[0].instance = INSTANCE_ZERO;
	memcpy(bearer[0].value, &u8Value, sizeof(u8Value));

	bearer[1].type = IE_FTEID; 
	bearer[1].length = htons(9);
	bearer[1].instance = INSTANCE_ZERO;
	unsigned int tt;
	memcpy(&tt, &(mb_msg->s1u_enb_fteid.ip.ipv4), 4);
	tt = htonl(tt);
	memcpy(&(mb_msg->s1u_enb_fteid.ip.ipv4), &tt, 4);
	mb_msg->s1u_enb_fteid.header.teid_gre = htonl(mb_msg->s1u_enb_fteid.header.teid_gre);
	memcpy(bearer[1].value, &mb_msg->s1u_enb_fteid, sizeof(struct fteid));//9

	ies[ieCount].type = IE_BEARER_CONTEXT;
	ies[ieCount].length = htons(18);
	ies[ieCount].instance = INSTANCE_ZERO;
	memcpy(ies[ieCount].value, &bearer[0], ntohs(bearer[0].length) +  4);
	memcpy(ies[ieCount].value + ntohs(bearer[0].length) + 4,
			&bearer[1], ntohs(bearer[1].length) +  4);
	ieCount++;

	g_udp_buf_size = ntohs(gtpv2c_s11_tx->gtp.len) + 4;
	//memcpy(g_udp_buf, &gtpv2c_s11_tx,sizeof(gtpv2c_s11_tx));
	//g_udp_buf_size += sizeof(gtpv2c_s11_tx);
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
	sendto(g_s11_fd, g_udp_buf, g_udp_buf_size, 0,
			(struct sockaddr*)&g_s11_cp_addr, g_s11_serv_size);

	//TODO " error chk, eagain etc?	
	log_msg(LOG_INFO, "Modify beader send, len - %d bytes.\n", g_udp_buf_size);

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
