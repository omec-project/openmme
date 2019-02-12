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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>
#include <freeDiameter/libfdproto.h>
#include "s6a_config.h"
#include "s6a.h"
#include "s6a_fd.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "hss_message.h"
#include "thread_pool.h"

/**Globals and externs**/
struct fd_dict_objects g_fd_dict_objs;
struct fd_dict_data g_fd_dict_data;
int g_Q_mme_aia_fd;
int g_Q_mme_ula_fd;
int g_Q_mme_purge_fd;

int g_our_hss_fd;
struct thread_pool *g_tpool;
extern s6a_config g_s6a_cfg;

pthread_t g_AIR_handler_tid, g_ULR_handler_tid;
pthread_t g_detach_handler_tid;
pthread_t g_our_hss_tid;
/**Globals and externs**/

/**
 * @brief Initialize communication channel IPC or IPC to non freediameter HSS
 * ready
 * @param  None
 * @return void
 */
void
init_hss_rpc()
{
	struct sockaddr_un hss_serv;

	g_our_hss_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (g_our_hss_fd < 0) {
		log_msg(LOG_ERROR, "HSS socket creation failed.\n");
		perror("Error opening HSS socket");
		exit(-1);
	}

	hss_serv.sun_family = AF_UNIX;
	strcpy(hss_serv.sun_path, g_s6a_cfg.hss_ipc_endpt);

	if (connect(g_our_hss_fd, (struct sockaddr *)&hss_serv,
	sizeof(struct sockaddr_un)) < 0) {
		log_msg(LOG_ERROR, "HSS connect failed.\n");
		perror("connecting HSS socket");
		close(g_our_hss_fd);
		exit(-1);
	}
	log_msg(LOG_INFO, "Connected to HSS\n");
}

/**
 * @brief Initialize freediameter library, dictionary and data elements
 * ready
 * @param  None
 * @return int SUCCESS or S6A_FD_ERROR
 */
static int
init_fd()
{
	/* Initialize the core freeDiameter library */
	CHECK_FCT_DO(fd_core_initialize(), return S6A_FD_ERROR);

	/* Parse the configuration file */
	CHECK_FCT_DO(fd_core_parseconf(S6A_FD_CONF), return S6A_FD_ERROR);

	if(SUCCESS != s6a_fd_init()) exit(S6A_FD_ERROR);

	if(SUCCESS != s6a_fd_objs_init()) exit(S6A_FD_ERROR);

	if(SUCCESS != s6a_fd_data_init()) exit(S6A_FD_ERROR);

	if(SUCCESS != s6a_fd_cb_reg()) exit(S6A_FD_ERROR);

	CHECK_FCT_DO( fd_core_start(), return S6A_FD_ERROR);

	return SUCCESS;
}

/**
 * @brief Unused
 * ready
 * @param
 * @return i
 */
static void
check_args(int argc, char **argv)
{
	/*Parsse arguments to extract file path*/
	/*If no file path mentioned then use default*/
	/*For wrong arguments print help*/
	return;
}

/**
 * @brief Initialize s6a application message handlers
 * ready
 * @param None
 * @return int SUCCESS or FAIL
 */
static int
init_handlers()
{
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	/* set the thread detach state */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&g_AIR_handler_tid, &attr, &AIR_handler, NULL);
	//pthread_create(&g_ULR_handler_tid, &attr, &ULR_handler, NULL);

	pthread_create(&g_detach_handler_tid, &attr, &detach_handler, NULL);

	pthread_attr_destroy(&attr);
	return 0;
}

/**
 * @brief initialize s6a application IPC mechanism, queues
 * ready
 * @param None
 * @return int as SUCCESS or FAIL. exit() in case of error.
 */
static int
init_s6a_ipc()
{
	/*Initialize global Q connections, not part of handler threads*/
	log_msg(LOG_INFO, "Connecting to mme-app AIA queue\n");
	g_Q_mme_aia_fd = open_ipc_channel(S6A_AIA_STAGE2_QUEUE, IPC_WRITE);
	if (g_Q_mme_aia_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening writer IPC channel:S6A AIA response.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "AIA response - mme-app IPC: Connected.\n");

	log_msg(LOG_INFO, "Connecting to mme-app S6A ULA response queue\n");
	g_Q_mme_ula_fd = open_ipc_channel(S6A_ULA_STAGE2_QUEUE, IPC_WRITE);
	if (g_Q_mme_ula_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S6A ULA response.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "ULA response - mme-app IPC: Connected.\n");

	log_msg(LOG_INFO, "Connecting to mme-app S6A purge response queue\n");
	g_Q_mme_purge_fd = open_ipc_channel(S6A_PURGE_STAGE2_QUEUE, IPC_WRITE);
	if (g_Q_mme_purge_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S6A purge response.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "purge response - mme-app IPC: Connected.\n");
	return 0;
}

/**
 * @brief HSS message listener. Listen hss response and delegate to thread pool
 * case of dummy hss
 * ready
 * @param None
 * @return void
 */
void
s6a_run()
{
	unsigned char buf[HSS_RCV_BUF_SIZE];
	int len;

	/*If using in build perf-hss then start thread to handle it's responses*/
	if(HSS_FD == g_s6a_cfg.hss_type) {
		/*Use main thread for ULR or stats etc.*/
		while(1) {
			sleep(10);
		}
	} else {

	while(1) {
		bzero(buf, sizeof(buf));

		if ((len = read(g_our_hss_fd, buf,
						sizeof(struct hss_resp_msg))) < 0) {
			log_msg(LOG_ERROR, "Error reading hss buff\n");
	                perror("reading stream message");
			exit(-1);
		} else if (len == 0) {
			log_msg(LOG_ERROR, "Error reading hss buff\n");
	                perror("reading stream message");
			exit(-1);
		}else {
			unsigned char *tmp_buf = (unsigned char *)
					calloc(sizeof(char), len);
			memcpy(tmp_buf, buf, len);
			log_msg(LOG_INFO, "HSS Received msg len : %d \n",len);
			insert_job(g_tpool, hss_resp_handler, tmp_buf);
		}
	}
	} /*else - HSS_PERF*/
}

/**
 * brief main for s6a application
 * @param argc and argv
 * @return int - program's exit code
 */
int
main(int argc, char **argv)
{
	/*Check cmd line arguments for config file path*/
	check_args(argc, argv);

	init_parser("conf/s6a.json");
	parse_s6a_conf();

	if(HSS_FD == g_s6a_cfg.hss_type){
		/*Initialize free diameter*/
		init_fd();
	} else {
		init_hss_rpc();
		/* Initialize thread pool for handling HSS resp*/
		g_tpool = thread_pool_new(HSS_RESP_THREADPOOL_SIZE);
		if (g_tpool == NULL) {
			log_msg(LOG_ERROR, "Error in creating thread pool. \n");
			return -1;
		}
	}

	init_s6a_ipc();

	/*Initialize listner for AIR and ULR from mme-app*/
	init_handlers();

	s6a_run();

	return 0;
}
