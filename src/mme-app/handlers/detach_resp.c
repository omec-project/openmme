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
#include "stage1_s6a_msg.h"
#include "stage2_info.h"
#include "detach_stage2_info.h"

/************************************************************************
Current file : detach stage 2 handler.
DEATTACH stages :
	Stage 1 :
-->	Stage 2 :
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_purge_fd;
static int g_Q_ds_fd;
static int g_Q_detach_accept_fd;

/*Making global just to avoid stack passing*/

static char ds_resp[S1AP_DTCHRES_STAGE2_BUF_SIZE];

static char purge_resp[S1AP_PURGERESP_STAGE2_BUF_SIZE];

static fd_set fds;

extern uint32_t detach_stage2_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{

	log_msg(LOG_INFO, "Connecting to Detach Stage 2 s6a reader .\n");
	if ((g_Q_purge_fd  = open_ipc_channel(S6A_PURGE_STAGE2_QUEUE,
					IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening purge reader IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Detach Stage 2 reader  - purge : Connected\n");

	log_msg(LOG_INFO, "Connecting to Detach Stage 2 reader .\n");
	if ((g_Q_ds_fd  = open_ipc_channel(S11_DTCHRES_STAGE2_QUEUE,
			IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening Detach reader stage 2 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Detach Stage 2 reader  - Detach : Connected\n");

	/*Open destination queue for writing. */
	log_msg(LOG_INFO, "Stage 2 witer  - s1ap Detach accept: waiting\n");
	g_Q_detach_accept_fd = open_ipc_channel(
			S1AP_DTCHACCEPT_STAGE2_QUEUE, IPC_WRITE);

	if (g_Q_detach_accept_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: "
				"Detach accept\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage2 writer - s1ap Detach accept Connected\n");

	return;
}

static int
process_purge_resp()
{
	struct purge_resp_Q_msg *purge_msg = (struct purge_resp_Q_msg *)purge_resp;
	struct UE_info *ue_entry = GET_UE_ENTRY(purge_msg->ue_idx);
	log_msg(LOG_INFO, "Purge resp for UE idx = %d\n", purge_msg->ue_idx);

	/*If delete sessoin also done then set flag for deleted*/
	if(DETACH_STAGE2_DS_DONE == ue_entry->ue_state) {
		ue_entry->ue_state = DETACH_STAGE2;
		detach_stage2_counter++;
	}
	else
		ue_entry->ue_state = DETACH_STAGE2_PURGE_DONE;

	return purge_msg->ue_idx;
}

static int
process_ds_resp()
{
	struct DS_resp_Q_msg *resp = (struct DS_resp_Q_msg *)ds_resp;
	struct UE_info *ue_entry = GET_UE_ENTRY(resp->ue_idx);
	log_msg(LOG_INFO, "DS resp for UE idx = %d\n", resp->ue_idx);


	if (DETACH_STAGE2_PURGE_DONE == ue_entry->ue_state) {
		ue_entry->ue_state = DETACH_STAGE2;
		detach_stage2_counter++;
	}
	else
		ue_entry->ue_state = DETACH_STAGE2_DS_DONE;

	return resp->ue_idx;
}

static int
read_next_msg()
{
	int bytes_read=0;
	struct timeval t;
	t.tv_sec = 0;
	t.tv_usec = 500;
	int ret = 0;

	/*Need to listen on two FD. using select*/
	FD_ZERO(&fds);
	FD_SET(g_Q_purge_fd, &fds);
	FD_SET(g_Q_ds_fd, &fds);

	ret = select(g_Q_ds_fd+1, &fds, NULL, NULL, &t);
	 switch (ret) {
		case -1:
		perror("select()");
		log_msg(LOG_ERROR, "Select failed for AIA and ULA\n");
		return -1;

		case 0:
		//log_msg(LOG_ERROR, "Select failed for purge and ds response - 0\n");
		return -1;

		default:
		/* All fd_set's should be checked. */
		if (FD_ISSET(g_Q_purge_fd, &fds)) {
			while (bytes_read < S1AP_PURGERESP_STAGE2_BUF_SIZE) {//TODO : Recheck condition
			if ((bytes_read = read_ipc_channel(
				g_Q_purge_fd, purge_resp, S1AP_PURGERESP_STAGE2_BUF_SIZE)) == -1) {
				log_msg(LOG_ERROR, "Error in reading \n");
				/* TODO : Add proper error handling */
			}
			log_msg(LOG_INFO, "S6A Purge resp rcvd - Len: %d\n",
				bytes_read);
			return process_purge_resp();
			}
		} else if (FD_ISSET(g_Q_ds_fd, &fds)) {
			while (bytes_read < S1AP_DTCHRES_STAGE2_BUF_SIZE) {//TODO : Recheck condition
			if ((bytes_read = read_ipc_channel(
					g_Q_ds_fd, ds_resp,
					S1AP_DTCHRES_STAGE2_BUF_SIZE)) == -1) {
				log_msg(LOG_ERROR, "Error in reading \n");
				/* TODO : Add proper error handling */
			}
			log_msg(LOG_INFO, "DS response Message Received -"
					" Len: %d\n",bytes_read);
			}
			return process_ds_resp();
		}
	}

	return ret;
}


/** UNUSED
* Stage specific message processing.
static int
detach_stage2_processing()
{
	return SUCCESS;
}
*/

/**
* Post message to next handler of the stage
*/
static int
post_to_next(int ue_index)
{
	struct UE_info *ue_entry = GET_UE_ENTRY(ue_index);
	if(ue_entry->ue_state == DETACH_STAGE2) {
		struct detach_accept_Q_msg req;

		log_msg(LOG_INFO, "Detach stage2 started. %d\n", ue_index);

		/*Create message to send to S1ap*/

		req.enb_fd = ue_entry->enb_fd;
		req.ue_idx = ue_index;
		req.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
		req.dl_seq_no = ue_entry->dl_seq_no++;
		memcpy(&(req.int_key), &(ue_entry->ue_sec_info.int_key),
				NAS_INT_KEY_SIZE);

		/*post message to next stage i.e. s1ap auth req*/
		write_ipc_channel(g_Q_detach_accept_fd, (char *)&(req),
				S1AP_DTCHACCEPT_STAGE2_BUF_SIZE);
		log_msg(LOG_INFO, "Detach Stage 2. Posted message to s1ap - Detach accept\n");

		int ret = insert_index_into_list(ue_index);
		if (ret == -1) {
			log_msg(LOG_INFO, "List is full. More indexes cannot be added\n");
		} else {
			log_msg(LOG_INFO, "Index with %d is added to list\n",ue_index);
		}

	}
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_detach_stage2()
{
	close_ipc_channel(g_Q_purge_fd);
	close_ipc_channel(g_Q_ds_fd);
	close_ipc_channel(g_Q_detach_accept_fd);
	log_msg(LOG_INFO, "Shutdown Stage 2 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
detach_stage2_handler(void *data)
{
	int ue_index = -1;
	init_stage();
	log_msg(LOG_INFO, "Stage 2 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		ue_index = read_next_msg();

		//detach_stage2_processing();

		if(ue_index >= 0)
			post_to_next(ue_index);
	}

	return NULL;
}
