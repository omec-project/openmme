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
#include "common_proc_info.h"

/************************************************************************
Current file : Stage 1 handler.
ATTACH stages :
	Stage 1 : Ctx release -> Release access bearer
**************************************************************************/

/****Globals and externs ***/

/*S11 CP communication parameters*/
extern int g_s11_fd;
extern struct sockaddr_in g_s11_cp_addr;
extern socklen_t g_s11_serv_size;
extern pthread_mutex_t s11_net_lock;

static int g_Q_S11_read_fd;

/*Making global just to avoid stack passing*/
static char buf[S11_COMM_REQ_STAGE_BUF_SIZE];

struct thread_pool *g_tpool;

static uint8_t g_udp_buf[4096];
static uint32_t g_udp_buf_size;

extern volatile uint32_t g_s11_sequence;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	//test ipc
	log_msg(LOG_INFO, "Mme to s11 msg Handler.\n");

	if ((g_Q_S11_read_fd  = open_ipc_channel(S11_SEND_REQ_STAGE_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader mme to S11 IPC.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "S11 reader : Opened\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S11_COMM_REQ_STAGE_BUF_SIZE);
	while (bytes_read < S11_COMM_REQ_STAGE_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
				g_Q_S11_read_fd, buf,
				S11_COMM_REQ_STAGE_BUF_SIZE )) == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, " MME to S11 request received - Len: %d\n",
			bytes_read);
	}


	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
rabr_processing()
{
	struct s11_req_Q_msg *rabr_msg = (struct s11_req_Q_msg *) buf;

	struct gtpv2c_header *gtpv2c_s11_tx =
			(struct gtpv2c_header *)g_udp_buf;

	set_gtpv2c_header(gtpv2c_s11_tx, GTP_RABR_REQ,
			rabr_msg->s11_sgw_c_fteid.header.teid_gre,
			g_s11_sequence);

	g_udp_buf_size = ntohs(gtpv2c_s11_tx->gtp.len) + 4;
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
	log_msg(LOG_INFO, "Send RAB request\n");

	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_rabr_session()
{
	close_ipc_channel(g_Q_S11_read_fd);
	log_msg(LOG_INFO, "Shutdown handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
s11_out_msg_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Mme to S11 msg handler initialized\n");

	while(1){
        read_next_msg();
	    
        struct s11_req_Q_msg *s11_common_req =
		    	(struct s11_req_Q_msg *) buf;
        switch(s11_common_req->IE_type)
        {
            case S11_RABR_REQ:
                log_msg(LOG_DEBUG, "RABR handling Start");
		        if (rabr_processing() == SUCCESS)
                {
			        post_to_next();
                }
                else
                {
                    log_msg(LOG_ERROR, "RABR handling failed");
                }
                break;
            default:
                    log_msg(LOG_ERROR, "Unknown msg %d\n", s11_common_req->IE_type);
        }
	}

	return NULL;
}

