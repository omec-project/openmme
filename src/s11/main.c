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

#include "thread_pool.h"
#include "err_codes.h"
#include "options.h"
#include "ipc_api.h"
#include "message_queues.h"
#include "s11.h"
#include "s11_config.h"

/**Global and externs **/
extern s11_config g_s11_cfg;

/*S11 CP communication parameters*/
int g_s11_fd;
struct sockaddr_in g_s11_cp_addr;
socklen_t g_s11_serv_size;
struct sockaddr_in g_client_addr;
socklen_t g_client_addr_size;

/*Connections to send CS response and MB response to mme-app*/
int g_Q_CSresp_fd;
int g_Q_MBresp_fd;
int g_Q_DSresp_fd;

pthread_t g_cs_tid;
pthread_t g_mb_tid;
pthread_t g_ds_tid;

pthread_mutex_t s11_net_lock = PTHREAD_MUTEX_INITIALIZER;

struct thread_pool *g_tpool;
/**End: global and externs**/

int
init_s11_workers()
{
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	/* set the thread detach state */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&g_cs_tid, &attr, &create_session_handler, NULL);
	pthread_create(&g_mb_tid, &attr, &modify_bearer_handler, NULL);
	pthread_create(&g_ds_tid, &attr, &delete_session_handler, NULL);

	pthread_attr_destroy(&attr);
	return 0;
}

/*Initialize sctp socket connection for eNB*/
int
init_gtpv2()
{
	/*Create UDP socket*/
	g_s11_fd = socket(PF_INET, SOCK_DGRAM, 0);

	g_client_addr.sin_family = AF_INET;
	//g_client_addr.sin_addr.s_addr = htonl(g_s11_cfg.local_egtp_ip);
	g_client_addr.sin_addr.s_addr = htonl(g_s11_cfg.local_egtp_ip);
	fprintf(stderr, "....................local egtp %d\n", g_s11_cfg.local_egtp_ip);
	g_client_addr.sin_port = htons(0); /* TODO: Read value from config */

	bind(g_s11_fd, (struct sockaddr *)&g_client_addr, sizeof(g_client_addr));
	g_client_addr_size = sizeof(g_client_addr);

	/*Configure settings in address struct*/
	g_s11_cp_addr.sin_family = AF_INET;
	//g_s11_cp_addr.sin_port = htons(g_s11_cfg.egtp_def_port);
	fprintf(stderr, ".................... egtp def port %d\n", g_s11_cfg.egtp_def_port);
	g_s11_cp_addr.sin_port = htons(g_s11_cfg.egtp_def_port);
	//g_s11_cp_addr.sin_addr.s_addr = htonl(g_s11_cfg.sgw_ip);
	fprintf(stderr, "....................sgw ip %d\n", g_s11_cfg.sgw_ip);
	g_s11_cp_addr.sin_addr.s_addr = htonl(g_s11_cfg.sgw_ip);
	memset(g_s11_cp_addr.sin_zero, '\0', sizeof(g_s11_cp_addr.sin_zero));

	g_s11_serv_size = sizeof(g_s11_cp_addr);

	return SUCCESS;
}

int
init_s11_ipc()
{
	log_msg(LOG_INFO, "Connecting to mme-app S11 CS response queue\n");
	g_Q_CSresp_fd = open_ipc_channel(S11_CSRESP_STAGE6_QUEUE , IPC_WRITE);
	if (g_Q_CSresp_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S11 CS response\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "CS response - mme-app IPC: Connected.\n");

	log_msg(LOG_INFO, "Connecting to mme-app S11 MB response queue\n");
	g_Q_MBresp_fd = open_ipc_channel(S11_MBRESP_STAGE8_QUEUE , IPC_WRITE);
	if (g_Q_MBresp_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S11 MB Response\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "MB response - mme-app IPC: Connected.\n");

	log_msg(LOG_INFO, "Connecting to mme-app S11 DS response queue\n");
	g_Q_DSresp_fd = open_ipc_channel(S11_DTCHRES_STAGE2_QUEUE , IPC_WRITE);
	if (g_Q_DSresp_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S11 DS Response\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "DS response - mme-app IPC: Connected.\n");

	return 0;
}

/**
  Read incoming S11 messages and pass to threadpool
  for processing.
*/
void
s11_reader()
{
	unsigned char buffer[S11_GTPV2C_BUF_LEN];
	int len;

	while(1) {
		//len = recvfrom(g_s11_fd, buffer, S11_GTPV2C_BUF_LEN, 0,
		//	&g_client_addr, &g_client_addr_size);
		len = recvfrom(g_s11_fd, buffer, S11_GTPV2C_BUF_LEN, 0,
			(struct sockaddr*)&g_s11_cp_addr, &g_s11_serv_size);

		if(len > 0) {
			unsigned char *tmp_buf = (unsigned char *)
					calloc(sizeof(char), len);
			memcpy(tmp_buf, buffer, len);
			//tmpBuf[len] = '\0';
			log_msg(LOG_INFO, "S11 Received msg len : %d \n",len);
			insert_job(g_tpool, handle_s11_message, tmp_buf);
		}

	}
}

int
main(int argc, char **argv)
{
	init_parser("conf/s11.json");
	parse_s11_conf();

	/*Init writer sockets*/
	if (init_s11_ipc() != 0) {
		log_msg(LOG_ERROR, "Error in initializing ipc.\n");
		return -1;
	}

	init_s11_workers();

	/* Initialize thread pool for S11 messages from CP*/
	g_tpool = thread_pool_new(S11_THREADPOOL_SIZE);

	if (g_tpool == NULL) {
		log_msg(LOG_ERROR, "Error in creating thread pool. \n");
		return -1;
	}
	log_msg(LOG_INFO, "S11 listener threadpool initialized.\n");

	if (init_gtpv2() != 0)
		return -1;

	s11_reader();

	return 0;
}
