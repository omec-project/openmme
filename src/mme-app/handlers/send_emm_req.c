/*
 * Copyright 2019-present Open Networking Foundation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "mme_app.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "s1ap_emm_message.h"


static int g_Q_send_emm_fd;

/**
Initialize the stage settings, Q,
destination communication etc.
*/

void
open_emm_info_s1ap_stage_init()
{
	/*Writing the EMM info message to s1ap queue */
	if ((g_Q_send_emm_fd = open_ipc_channel(EMM_INFOREQ_QUEUE,
						IPC_WRITE)) == -1){
		log_msg(LOG_ERROR, "Error in opening write emm info s1ap channel \n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "EMM info S1ap Channel for write opened \n");
	return;
}

int
send_emm_info_s1ap_channel_req(struct ue_emm_info *req)
{
	write_ipc_channel(g_Q_send_emm_fd, (char *)(req), UE_EMM_INFO_BUF_SIZE );
	log_msg(LOG_INFO, "Posted EMM info S1ap channel to s1ap-app %d .\n",UE_EMM_INFO_BUF_SIZE);
	return SUCCESS;
}
