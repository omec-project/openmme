/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
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
#include "paging_info.h"

/************************************************************************
Paging handler.
Flow : 36.413 - release 15 - Section 8.5
		DDN Request : SGW-->MME 
--->		Paging MME --> eNB
**************************************************************************/

/****Globals and externs ***/

extern int g_mme_hdlr_status;

static int g_Q_paging_fd;
static int g_Q_DDN_fd;

/*Making global just to avoid stack passing*/
static char DDN_buf[10];//[S6A_DDN_BUF_SIZE];
/*tmp defined*/
#define S6A_DDN_BUF_SIZE 10

extern uint32_t paging_counter;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "DDN reader complete: waiting\n");
	if ((g_Q_DDN_fd  = open_ipc_channel(
					S6A_DDN_QUEUE, IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader - DDN"
				"S6A IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "DDN reader complete: Connected\n");
	g_Q_paging_fd = open_ipc_channel(S1AP_PAGING_QUEUE, IPC_WRITE);
	if (g_Q_paging_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:s1ap Paging\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "s1ap Paging writer: Connected\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(DDN_buf, 0, S6A_DDN_BUF_SIZE);
	while (bytes_read < S6A_DDN_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
						g_Q_DDN_fd,
						DDN_buf,
						S6A_DDN_BUF_SIZE)) == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "DDN Msg Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
DDN_processing()
{
/*
	struct DDN_Q_msg *ddn_info = (struct DDN_Q_msg *)buf;
*/
	struct UE_info *ue_entry ;/* =  GET_UE_ENTRY(ddn_info->ue_idx);*/

	/*Change UE state */
	/*DDN throtelling if required*/

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
/*
	struct DDN_Q_msg *ddn_info = (struct DDN_Q_msg *)buf;
*/
	struct UE_info *ue_entry ;/* =  GET_UE_ENTRY(ddn_info->ue_idx);*/
	struct paging_Q_msg paging_msg;

	log_msg(LOG_INFO, "Post for s1ap paging processing.\n");

	paging_msg.ue_idx = 0;/* ddn_info->ue_idx;*/
	memcpy(&(paging_msg.IMSI), &(ue_entry->IMSI), BINARY_IMSI_LEN);

	write_ipc_channel(g_Q_paging_fd, (char *)&(paging_msg), S1AP_PAGING_INFO_BUF_SIZE);

	log_msg(LOG_INFO, "Post for paging processing. SUCCESS\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_paging()
{
	close_ipc_channel(g_Q_DDN_fd);
	close_ipc_channel(g_Q_paging_fd);
	log_msg(LOG_INFO, "Shutdown DDN/Paging handlers. \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
DDN_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "DDN stage ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		DDN_processing();

		post_to_next();
		paging_counter++;
	}

	return NULL;
}
