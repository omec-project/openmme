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
#include "ue_table.h"
#include "s1ap_error.h"


static int g_Q_reset_s1ap_fd;

/**
Initialize the stage settings, Q,
destination communication etc.
*/

void
open_reset_s1ap_stage_init()
{
	/*Writing the reset message to s1ap Queue*/
	if ((g_Q_reset_s1ap_fd = open_ipc_channel(S1AP_GEN_RESET_QUEUE,
						IPC_WRITE)) == -1){
		log_msg(LOG_ERROR, "Error in opening write reset s1ap channel \n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Reset S1ap Channel for write opened \n");
	return;
}

int send_reset(struct UE_info *ue_entry, uint32_t cause, uint32_t reset_type)
{
    /* Generate EMM error only 2 times for test purpose */
    struct ue_reset_info err = {0};
    err.enb_fd = ue_entry->enb_fd; 
    err.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
    err.mme_s1ap_ue_id = ue_entry->ue_index;
    err.reset_type = reset_type;
    // 3 - Release due to eutran generated reason  
    // 15 - unknown-pair-ue-s1ap-id 
    err.cause = cause; 
    send_reset_s1ap_channel_req(&err); 
    return 0;
}

int
send_reset_s1ap_channel_req(struct ue_reset_info *req)
{
	write_ipc_channel(g_Q_reset_s1ap_fd, (char *)(req), UE_RESET_INFO_BUF_SIZE);
	log_msg(LOG_INFO, "Posted Reset S1ap channel to s1ap-app.\n");
	return SUCCESS;
}
