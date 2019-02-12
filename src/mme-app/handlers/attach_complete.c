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

#include "mme_app.h"
#include "ue_table.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage8_info.h"

/************************************************************************
Current file : Stage 7 handler.
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

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_atchcomplete_fd;
static int g_Q_MBresp_fd;

/*Making global just to avoid stack passing*/
static char attach_complete[S1AP_ATT_COMP_STAGE8_BUF_SIZE];
static char MB_resp[S11_MBRESP_STAGE8_BUF_SIZE];

static fd_set g_stage8_fds;

extern uint32_t attach_stage8_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "Stage 8 reader - Attach complete: waiting\n");
	if ((g_Q_atchcomplete_fd  = open_ipc_channel(S1AP_ATT_COMP_STAGE8_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 8 S1AP IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 8 reader - s1ap Attach complete: Connected\n");

	log_msg(LOG_INFO, "Stage 8 reader - s11 MB response: waiting\n");
	if ((g_Q_MBresp_fd  = open_ipc_channel(S11_MBRESP_STAGE8_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 8 S11 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 8 reader - s11 MB response: Connected\n");

	return;
}

static int
process_MB_resp()
{
	struct MB_resp_Q_msg *mbr_msg =
		(struct MB_resp_Q_msg *)MB_resp;
	struct UE_info*ue_entry = GET_UE_ENTRY(mbr_msg->ue_idx);

	log_msg(LOG_INFO, "Modify beader for UE idx = %d\n", mbr_msg->ue_idx);

	if(STAGE8_NAS_ATCH_DONE == ue_entry->ue_state){
		ue_entry->ue_state = ATTACH_DONE;
		attach_stage8_counter++;
		log_msg(LOG_ERROR, "=====ATTACH COMPLETE UE - %d======\n", mbr_msg->ue_idx);
	}
	else
		ue_entry->ue_state = STAGE8_MBR_DONE;

	return mbr_msg->ue_idx;
}

static int
process_att_complete_resp()
{
	struct attach_complete_Q_msg *atch_msg =
		(struct attach_complete_Q_msg *)attach_complete;
	struct UE_info *ue_entry = GET_UE_ENTRY(atch_msg->ue_idx);

	ue_entry->ul_seq_no++;

	log_msg(LOG_INFO, "s1ap attach complete msg for UE idx = %d\n", atch_msg->ue_idx);

	if(STAGE8_MBR_DONE == ue_entry->ue_state) {
		ue_entry->ue_state = ATTACH_DONE;
		attach_stage8_counter++;
		log_msg(LOG_ERROR, "=====ATTACH COMPLETE UE - %d======\n", atch_msg->ue_idx);
	}
	else
		ue_entry->ue_state = STAGE8_NAS_ATCH_DONE;

	return atch_msg->ue_idx;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;
	struct timeval t;
	t.tv_sec = 0;
        t.tv_usec = 500;
	int ret = 0;

	/*Need to listen on two FD. using select*/
	FD_ZERO(&g_stage8_fds);
	FD_SET(g_Q_atchcomplete_fd, &g_stage8_fds);
	FD_SET(g_Q_MBresp_fd, &g_stage8_fds);

	memset(attach_complete, 0, S1AP_ATT_COMP_STAGE8_BUF_SIZE);

	ret = select(g_Q_MBresp_fd+1, &g_stage8_fds, NULL, NULL, &t);
	 switch (ret) {
		case -1:
		perror("select()");
		log_msg(LOG_ERROR, "Select failed for MB resp, attach complete.\n");
		return -1;

		case 0:
		//log_msg(LOG_ERROR, "Select failed for AIA and ULA - 0\n");
		return -1;

		default:
		/* All fd_set's should be checked. */
		if (FD_ISSET(g_Q_atchcomplete_fd, &g_stage8_fds)) {
			while (bytes_read < S1AP_ATT_COMP_STAGE8_BUF_SIZE) {//TODO : Recheck condition
			if ((bytes_read = read_ipc_channel(
				g_Q_atchcomplete_fd, attach_complete, S1AP_ATT_COMP_STAGE8_BUF_SIZE)) == -1) {
				log_msg(LOG_ERROR, "Error in reading \n");
				/* TODO : Add proper error handling */
			}
			log_msg(LOG_INFO, "Attach complete Message Received - Len: %d\n",bytes_read);
			return process_att_complete_resp();
			}
		} else if (FD_ISSET(g_Q_MBresp_fd, &g_stage8_fds)) {
			while (bytes_read < S11_MBRESP_STAGE8_BUF_SIZE) {//TODO : Recheck condition
			if ((bytes_read = read_ipc_channel(
				g_Q_MBresp_fd, MB_resp, S11_MBRESP_STAGE8_BUF_SIZE)) == -1) {
				log_msg(LOG_ERROR, "Error in reading \n");
				/* TODO : Add proper error handling */
			}
			log_msg(LOG_INFO, "MB response Received - Len: %d\n",bytes_read);
			}
			return process_MB_resp();
		}
        }
	return SUCCESS;
}

/**
* Stage specific message processing.
*/
static int
stage8_processing()
{
	/*Parse and validate  the buffer*/
	/*Find the UE*/
	/*Check the state*/
	/*Collect information for next processing*/
	/*post to next processing*/
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_stage8()
{
	close_ipc_channel(g_Q_atchcomplete_fd);
	close_ipc_channel(g_Q_MBresp_fd);
	log_msg(LOG_INFO, "Shutdown Stage 8 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
stage8_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Stage 8 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		stage8_processing();

		post_to_next();
	}

	return NULL;
}
