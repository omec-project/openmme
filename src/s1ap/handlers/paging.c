/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
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
#include "common_proc_info.h"

/****Globals and externs ***/

/*Making global just to avoid stack passing*/
static char buf[S1AP_COMMON_REQ_BUF_SIZE];
extern ipc_handle ipcHndl_paging;
static Buffer g_paging_buffer;

static struct s1ap_common_req_Q_msg *g_paging_buf;

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

	memset(buf, 0, S1AP_COMMON_REQ_BUF_SIZE);
	while (bytes_read < S1AP_COMMON_REQ_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
				ipcHndl_paging, buf,
				S1AP_COMMON_REQ_BUF_SIZE)) == -1) {
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
	uint32_t length = 0;
    uint8_t *buffer = NULL;
	g_paging_buf = (struct s1ap_common_req_Q_msg *) buf;

    int ret = s1ap_mme_encode_initiating(g_paging_buf, &buffer, &length);
    if(ret == -1)
    {
        log_msg(LOG_ERROR, "Encoding Paging request failed.\n");
        return E_FAIL;
    }

	buffer_copy(&g_paging_buffer, buffer, length);

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	send_sctp_msg(g_paging_buf->enb_fd, 
                    g_paging_buffer.buf, g_paging_buffer.pos, 1);
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
