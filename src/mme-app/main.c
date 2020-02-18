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

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "log.h"
#include "s11.h"
#include "s1ap.h"
#include "s6a.h"
#include "ue_table.h"
#include "mme_app.h"
#include "thread_pool.h"
#include "unix_sock.h"
#include "hash.h"
#include "ipc_api.h"
#include "message_queues.h"

/*Globals and externs*/
mme_config g_mme_cfg;

int g_Q_s1ap_common_reject; 
pthread_mutex_t s1ap_reject_queue_mutex;

/*List of UEs attached to MME*/
struct UE_info* g_UE_list[UE_POOL_SIZE];
int g_unix_fd = 0;
struct thread_pool *g_tpool;
pthread_t acceptUnix_t;

int g_tmsi_allocation_array[10000];


pthread_t stage_tid[TOTAL_STAGES];

int g_mme_hdlr_status;
extern void init_backtrace();

/*End globals and externs*/

/**
 * @brief Check whether all other programs are initialized to declare mme is
 * ready
 * @param  None
 * @return void
 */
void
check_mme_hdlr_status()
{
	/*TODO: not thread-safe*/
	if(!(g_mme_hdlr_status ^ 131071)) /*1 1111 1111 1111 1111 - 1 bit for init of 1 stage */
		log_msg(LOG_INFO, "MME setup is ready. Let's dance.\n");
}

/**
 * @brief Initialize MME resource pool and message queues
 * @param None
 * @return int as SUCCESS or FAIL
 */
static int
init_mme()
{
	/*init UEs arra to 65535 initially*/
	g_UE_list[0] = (struct UE_info*)calloc(sizeof(struct UE_info), UE_POOL_CNT);
	if(NULL == g_UE_list[0]) {
		log_msg(LOG_ERROR, "Allocation failed.\n");
		exit(-1);
	}
/*
	g_UE_list[1] = (struct UE_info*)calloc(sizeof(struct UE_info), UE_POOL_CNT);
	if(NULL == g_UE_list[1]) {
		log_msg(LOG_ERROR, "Allocation failed.\n");
		exit(-1);
	}
	g_UE_list[2] = (struct UE_info*)calloc(sizeof(struct UE_info), UE_POOL_CNT);
	if(NULL == g_UE_list[2]) {
		log_msg(LOG_ERROR, "Allocation failed.\n");
		exit(-1);
	}
*/
	/*Check system requirements*/

	/*Create all required IPC files*/
	log_msg(LOG_INFO, "Creating IPC Queues...\n");

	mkdir(S1AP_Q_DIR, 0777);
	mkdir(MME_APP_Q_DIR, 0777);
	mkdir(S6A_Q_DIR, 0777);
	mkdir(S11_Q_DIR, 0777);

	unlink(INITUE_STAGE1_QUEUE);
	create_ipc_channel(INITUE_STAGE1_QUEUE);

	unlink(S1AP_REQ_REJECT_QUEUE);
	create_ipc_channel(S1AP_REQ_REJECT_QUEUE);

	unlink(S1AP_ID_REQ_QUEUE);
	create_ipc_channel(S1AP_ID_REQ_QUEUE);

	unlink(S1AP_ID_RSP_QUEUE);
	create_ipc_channel(S1AP_ID_RSP_QUEUE);

	unlink(S6A_AIA_STAGE2_QUEUE);
	create_ipc_channel(S6A_AIA_STAGE2_QUEUE);

	unlink(S6A_ULA_STAGE2_QUEUE);
	create_ipc_channel(S6A_ULA_STAGE2_QUEUE);

	unlink(S6A_REQ_STAGE1_QUEUE );
	create_ipc_channel(S6A_REQ_STAGE1_QUEUE );

	unlink(S1AP_AUTHREQ_STAGE2_QUEUE );
	create_ipc_channel(S1AP_AUTHREQ_STAGE2_QUEUE );

	unlink(S1AP_AUTHRESP_STAGE3_QUEUE );
	create_ipc_channel(S1AP_AUTHRESP_STAGE3_QUEUE );

	unlink(S1AP_SECREQ_STAGE3_QUEUE );
	create_ipc_channel(S1AP_SECREQ_STAGE3_QUEUE );

	unlink(S1AP_SECRESP_STAGE4_QUEUE );
	create_ipc_channel(S1AP_SECRESP_STAGE4_QUEUE );

	unlink(S1AP_ESMREQ_STAGE4_QUEUE );
	create_ipc_channel(S1AP_ESMREQ_STAGE4_QUEUE );

	unlink(S1AP_ESMRESP_STAGE5_QUEUE);
	create_ipc_channel(S1AP_ESMRESP_STAGE5_QUEUE);

	unlink(S11_CSREQ_STAGE5_QUEUE);
	create_ipc_channel(S11_CSREQ_STAGE5_QUEUE);

	unlink(S11_CSRESP_STAGE6_QUEUE);
	create_ipc_channel(S11_CSRESP_STAGE6_QUEUE);

	unlink(S1AP_ICSREQ_STAGE6_QUEUE);
	create_ipc_channel(S1AP_ICSREQ_STAGE6_QUEUE);

	unlink(S1AP_ICSRESP_STAGE7_QUEUE);
	create_ipc_channel(S1AP_ICSRESP_STAGE7_QUEUE);

	unlink(S11_MBREQ_STAGE7_QUEUE);
	create_ipc_channel(S11_MBREQ_STAGE7_QUEUE);

	unlink(S11_MBRESP_STAGE8_QUEUE);
	create_ipc_channel(S11_MBRESP_STAGE8_QUEUE);

	unlink(S1AP_ATT_COMP_STAGE8_QUEUE);
	create_ipc_channel(S1AP_ATT_COMP_STAGE8_QUEUE);

	/*Stage 1 Detach/Delete Session*/

	unlink(S1AP_DTCHREQ_STAGE1_QUEUE);
	create_ipc_channel(S1AP_DTCHREQ_STAGE1_QUEUE);

	unlink(S11_DTCHREQ_STAGE1_QUEUE);
	create_ipc_channel(S11_DTCHREQ_STAGE1_QUEUE);

	unlink(S11_DTCHRES_STAGE2_QUEUE);
	create_ipc_channel(S11_DTCHRES_STAGE2_QUEUE);

	unlink(S6A_DTCHREQ_STAGE1_QUEUE);
	create_ipc_channel(S6A_DTCHREQ_STAGE1_QUEUE);

	unlink(S1AP_DTCHACCEPT_STAGE2_QUEUE);
	create_ipc_channel(S1AP_DTCHACCEPT_STAGE2_QUEUE);

	unlink(S6A_PURGE_STAGE2_QUEUE);
	create_ipc_channel(S6A_PURGE_STAGE2_QUEUE);

	unlink(S1AP_CTXRELRESP_STAGE3_QUEUE);
	create_ipc_channel(S1AP_CTXRELRESP_STAGE3_QUEUE);

    unlink(S11_DDN_QUEUE);
	create_ipc_channel(S11_DDN_QUEUE);

	unlink(S1AP_PAGING_QUEUE);
	create_ipc_channel(S1AP_PAGING_QUEUE);
	
	unlink(S1AP_MME_QUEUE);
	create_ipc_channel(S1AP_MME_QUEUE);
   
	unlink(S11_SEND_REQ_STAGE_QUEUE);
	create_ipc_channel(S11_SEND_REQ_STAGE_QUEUE);
   
	unlink(S11_RECV_RSP_STAGE_QUEUE);
	create_ipc_channel(S11_RECV_RSP_STAGE_QUEUE);
   
	unlink(S1AP_MME_TO_S1AP_QUEUE);
	create_ipc_channel(S1AP_MME_TO_S1AP_QUEUE);

	unlink(S11_DDN_ACK_QUEUE);
	create_ipc_channel(S11_DDN_ACK_QUEUE);

	unlink(S11_DDN_FAIL_QUEUE);
        create_ipc_channel(S11_DDN_FAIL_QUEUE);
	
	//Service Request
	unlink(S1AP_SERVICEREQ_QUEUE);
	create_ipc_channel(S1AP_SERVICEREQ_QUEUE);
 
	//TAU Request
	unlink(S1AP_TAUREQ_QUEUE);
	create_ipc_channel(S1AP_TAUREQ_QUEUE);

	//TAU Response
	unlink(S1AP_TAURSP_QUEUE);
	create_ipc_channel(S1AP_TAURSP_QUEUE);

	return SUCCESS;
}

/**
 * @brief initialize all the stage handler threads
 * @param None
 * @return int as SUCCESS or FAIL
 */
static int
init_stage_handlers()
{
	pthread_attr_t attr;

	log_msg(LOG_INFO, "Starting stage handlers\n");
	pthread_attr_init(&attr);
	/* set the thread detach state */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&stage_tid[0], &attr, &stage1_handler, NULL);
	pthread_create(&stage_tid[1], &attr, &stage2_handler, NULL);
	pthread_create(&stage_tid[2], &attr, &stage3_handler, NULL);
	pthread_create(&stage_tid[3], &attr, &stage4_handler, NULL);
	pthread_create(&stage_tid[4], &attr, &stage5_handler, NULL);
	pthread_create(&stage_tid[5], &attr, &stage6_handler, NULL);
	pthread_create(&stage_tid[6], &attr, &stage7_handler, NULL);
	pthread_create(&stage_tid[7], &attr, &stage8_handler, NULL);
	pthread_create(&stage_tid[8], &attr, &detach_stage1_mme_handler, NULL);
	pthread_create(&stage_tid[9], &attr, &detach_stage2_handler, NULL);
	pthread_create(&stage_tid[10], &attr, &detach_stage3_handler, NULL);
	pthread_create(&stage_tid[11], &attr, &DDN_handler, NULL);
	pthread_create(&stage_tid[12], &attr, &s1ap_req_common_mme_handler, NULL);
	pthread_create(&stage_tid[13], &attr, &s11_rsp_common_mme_handler, NULL);
	pthread_create(&stage_tid[14], &attr, &service_request_handler, NULL);
	pthread_create(&stage_tid[15], &attr, &identity_rsp_handler, NULL);
	pthread_create(&stage_tid[16], &attr, &tau_request_handler, NULL);
  
	if ((g_Q_s1ap_common_reject  = open_ipc_channel(S1AP_MME_TO_S1AP_QUEUE,
						IPC_WRITE)) == -1){
		log_msg(LOG_ERROR, "Error in opening MME to S1AP write IPC channel.\n");
		pthread_exit(NULL);
	}

	pthread_attr_destroy(&attr);
	return SUCCESS;
}


/**
 * @brief MME-app main function.
 * @param None
 * @return int as SUCCESS or FAIL
 */
int main()
{
    init_backtrace();
    srand(time(0));
    for(int i=0;i<10000;i++)
        g_tmsi_allocation_array[i] = -1;
	/*Read MME configurations*/
    mme_parse_config(&g_mme_cfg); 

	/*Initialize MME*/
	init_mme();

	/*Initialize workers*/
	init_stage_handlers();

#ifdef  STATS
	stat_init();
#endif
	/* Initialize thread pool for sctp request parsers */
	g_tpool = thread_pool_new(THREADPOOL_SIZE);

	if (g_tpool == NULL) {
		log_msg(LOG_ERROR, "Error in creating thread pool. \n");
		return -E_FAIL_INIT;
	}
	log_msg(LOG_INFO, "monitor Listener theadpool initalized.\n");

	if (init_sock() != SUCCESS) {
		log_msg(LOG_ERROR, "Error in initializing unix domain socket server.\n");
		return -E_FAIL_INIT;
	}

	log_msg(LOG_INFO, "socket started in listen mode \n");

	log_msg(LOG_INFO, "Register for config Triggers \n");
    register_config_updates();

	log_msg(LOG_INFO, "MME connections are ready. Start other dependent"\
			"processess s1ap, s6a, s11...)\n");


	/*Start main thread*/
	start_mme();

	return SUCCESS;
}

void mme_parse_config(mme_config *config)
{
	/*Read MME configurations*/
	init_parser("conf/mme.json");
	parse_mme_conf(config);
    /* Lets apply logging setting */
    set_logging_level(config->logging);
}

