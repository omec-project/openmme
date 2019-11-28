/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
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
#include <unistd.h>

#include "ProtocolIE-Container.h"
#include "ProtocolIE-ID.h"
#include "ProtocolIE-Field.h"
#include "log.h"
#include "err_codes.h"
#include "s1ap.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "main.h"
#include "sctp_conn.h"
#include "paging_info.h"

/****Globals and externs ***/

/*Making global just to avoid stack passing*/
static char buf[S1AP_PAGING_INFO_BUF_SIZE];
extern ipc_handle ipcHndl_paging;

static struct paging_Q_msg *g_paging_buf;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((ipcHndl_paging  = open_ipc_channel(
				S1AP_PAGING_QUEUE, IPC_READ)) == -1) {
		log_msg(LOG_ERROR, "Error in opening reader for Paging"
				"channel : %s\n", S1AP_PAGING_QUEUE);
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Paging reader: Connected.\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_PAGING_INFO_BUF_SIZE);
	while (bytes_read < S1AP_PAGING_INFO_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
				ipcHndl_paging, buf,
				S1AP_PAGING_INFO_BUF_SIZE)) == -1) {
					log_msg(LOG_ERROR, "Error reading paging req Q\n");
					/* TODO : Add proper error handling */
				}
		log_msg(LOG_INFO, "Paging recvd from mme on Q len-%d\n", bytes_read);
	}

	return bytes_read;
}


/**
* Stage specific message processing.
*/
static int
paging_processing()
{
	g_paging_buf = (struct paging_Q_msg *) buf;
#ifdef REPLACE_WITH_S1AP_ENCODING_DONE
	struct s1ap_PDU s1apPDU;

	ProtocolIE_Container_129P22_t paging_buf;
	PagingIEs_t *paging_ie = NULL;

	paging_buf.list.count = 1;
	
	//paging_ie = &(paging_buf.list.array[0]);

	paging_ie->id = ProtocolIE_ID_id_UEPagingID;

	/*TODO : Write code for encoding Paging s1ap API*/

#endif /*REPLACE_WITH_S1AP_ENCODING_DONE*/
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
/*TODO : uncomment this to send message when s1ap encoding is done.
	send_sctp_msg(g_authreqInfo->enb_fd, g_buffer.buf, g_buffer.pos, 1);*/
	log_msg(LOG_INFO, "\n-----Paging request completed.---\n");
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_paging()
{
	close_ipc_channel(ipcHndl_paging);
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
paging_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Paging handler ready.\n");

	while(1){
		read_next_msg();

		paging_processing();

		post_to_next();
	}

	return NULL;
}
