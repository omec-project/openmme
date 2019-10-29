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
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <errno.h>

#include "options.h"
#include "ipc_api.h"
#include "main.h"
#include "s1ap.h"
#include "s1ap_config.h"
#include "sctp_conn.h"
#include "s1ap_structs.h"
#include "message_queues.h"
#include "thread_pool.h"
#include "tpool_queue.h"
#include "snow_3g.h"
#include "f9.h"


/*Global and externs **/
extern s1ap_config g_s1ap_cfg;
pthread_t s1ap_iam_t;

int g_enb_fd = 0;
int g_sctp_fd = 0;
struct thread_pool *g_tpool;

ipc_handle ipcHndl_attach;
ipc_handle ipcHndl_authresp;
ipc_handle ipcHndl_secresp;
ipc_handle ipcHndl_esmresp;
ipc_handle ipcHndl_icsresp;
ipc_handle ipcHndl_attachomplete;
ipc_handle ipcHndl_detach;
ipc_handle ipcHndl_ctx_release_complete;

ipc_handle ipcHndl_auth;
ipc_handle ipcHndl_smc;
ipc_handle ipcHndl_esm;
ipc_handle ipcHndl_ics;
ipc_handle ipcHndl_detach_accept;

ipc_handle ipcHndl_sctpsend_reader;
ipc_handle ipcHndl_sctpsend_writer;

pthread_t authReq_t;
pthread_t smcReq_t;
pthread_t esmReq_t;
pthread_t icsReq_t;
pthread_t detachAcpt_t;
pthread_t acceptSctp_t;

struct time_stat g_attach_stats[65535];
/**End: global and externs**/

#define MAX_ENB     10
#define BUFFER_LEN  1024

char *msg_to_hex_str(const char *msg, int len, char **buffer) {

  char chars[]= "0123456789abcdef";
  char *local;

  if (!len)
      return NULL;

  if (!((*buffer) = (char *)malloc(2 * len + 1)))
      return NULL;

  local = *buffer;
  for (int i = 0; i < len; i++) {
      local[2 * i] = chars[(msg[i] >> 4) & 0x0F];
      local[2 * i + 1] = chars[(msg[i]) & 0x0F];
  }
  local[2 * len] = '\0';

  return local;
}

unsigned short get_length(char **msg) {
    /* get length and consume msg bytes accordingly */

    unsigned short ie_len = 0;

    unsigned char val = ((*msg)[0] & 0xc0) >> 6;
    if(val == 2) {
        //log_msg(LOG_INFO, "length more than 128\n");
        unsigned short higher = (unsigned char)(*msg)[0] & 0x3f;
        (*msg)++;
        unsigned short lower = (unsigned char)(*msg)[0];
        ie_len = (higher << 8) | lower;
    } else {
        //log_msg(LOG_INFO, "length less than 128\n");
        ie_len = (unsigned short)(*msg)[0];
    }
    (*msg)++;
    return ie_len;
}

/**
 * @brief Decode int value from the byte array received in the s1ap incoming
 * packet.
 * @param[in] bytes - Array of bytes in packet
 * @param[in] len - Length of the bytes array from which to extract the int
 * @return Integer value extracted out of bytes array. 0 if failed.
 */
int
decode_int_val(unsigned char *bytes, short len)
{
	switch(len) {
		case 1:
		case 2:
			return (bytes[1] & 0xff);

		case 3:
			return (bytes[2] & 0xff) |
					(0xff00 & ((unsigned short)(bytes[1] << 8)));

		case 4:
			return (((((unsigned int)(bytes[1]) << 16) & 0xffff00) |
					((unsigned int)(bytes[2]) << 8)) & 0xffff00) |
					((unsigned int)(bytes[3]) & 0xff);
	};
	return 0;
}

/**
 * @brief Pack short number value in to the buffer
 * @param[out] buffer to fill the value
 * @param[in] value to fill
 * @return number of bytes filled in to the buffer
 */
int
copyU16(unsigned char *buffer, uint32_t val)
{
	if (val < 255) {
		buffer[0] = (val >> 8) & 0xFF;
		buffer[1] = val & 0xFF;
		return 2;
	} else if (val < 65535) {
		buffer[0] = 0x40;
		buffer[1] = (val >> 8) & 0xFF;
		buffer[2] = val & 0xFF;
		return 3;
	} else {
		buffer[0] = 0x80;
		buffer[1] = (val >> 16) & 0xFF;
		buffer[2] = (val >> 8) & 0xFF;
		buffer[3] = val & 0xFF;
		return 4;
	}
}

void
calculate_mac(uint8_t *int_key, uint32_t seq_no, uint8_t direction,
		uint8_t bearer, uint8_t *data, uint16_t data_len,
		uint8_t *mac)
{
	uint8_t *out;

	out = f9(int_key, seq_no, bearer, direction, data, data_len * 8);

	memcpy(mac, out, MAC_SIZE);

	return;
}

int
init_s1ap_workers()
{
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	/* set the thread detach state */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_attr_destroy(&attr);
	return 0;
}

/**
 * @brief Thread to read and distribute sctp request received. Messages will
 * be passed to s1ap handler function for further processing.
 * @param[in] thread data
 * @return thread return data
 */
void *
accept_sctp(void *data)
{
	log_msg(LOG_INFO, "accept connection on sctp sock\n");
	int new_socket = 0;
	int activity = 0;
	int i = 0;
	int valread = 0;
	int sd = 0;
	int max_sd = 0;
	int enb_socket[MAX_ENB] = {0};

	fd_set readfds;
	unsigned char buffer[BUFFER_LEN] = {0};


	while(1) {

		FD_ZERO(&readfds);
		FD_SET(g_sctp_fd, &readfds);
		max_sd = g_sctp_fd;

		for (i = 0; i < MAX_ENB; i++) {
			sd = enb_socket[i];

			if (sd > 0) {
				FD_SET(sd, &readfds);
			}

			if (sd > max_sd) {
				max_sd = sd;
			}
		}

		activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

		if ((activity < 0) && (errno != EINTR)) {
			log_msg(LOG_ERROR, "select error.\n");
		 }

		if (FD_ISSET(g_sctp_fd, &readfds)) {

			if ((new_socket = accept_sctp_socket(g_sctp_fd)) == -1) {
				log_msg(LOG_ERROR, "Error in accept on sctp socket.\n");
			}

			log_msg(LOG_INFO, "New Connection Established\n.");

			for (i = 0; i < MAX_ENB; i++) {

				if( enb_socket[i] == 0 ) {

					enb_socket[i] = new_socket;
					log_msg(LOG_INFO, "Adding to list of sockets at %d value %d\n" , i, new_socket);

					break;
				}
			}
		}

		for (i = 0; i < MAX_ENB; i++) {

			sd = enb_socket[i];

			if (FD_ISSET(sd, &readfds)) {
				if ((valread = recv_sctp_msg(sd, buffer, SCTP_BUF_SIZE)) == 0) {

					log_msg(LOG_INFO, "Host Disconnected\n");
					close(sd);
					enb_socket[i] = 0;

				} else {

					unsigned char *tmpBuf = (unsigned char *)
					malloc(sizeof(char) * valread + (2*sizeof(int)) );
					memcpy(tmpBuf, &sd, sizeof(sd));
					memcpy(tmpBuf + sizeof(int), &valread, sizeof(int));
					memcpy(tmpBuf + (2*sizeof(int)), buffer, valread);
					//tmpBuf[len] = '\0';
					log_msg(LOG_INFO, "SCTP Received msg len : %d \n",valread);
					insert_job(g_tpool, handle_s1ap_message, tmpBuf);

				}
			}
		}

	}/* while */

	return NULL;
}

/**
 * @brief Initialize sctp socket connection for eNB
 * @return Error code SUCCESS or FAIL
*/
int
init_sctp()
{
	log_msg(LOG_INFO, "Create sctp sock, ip:%d, port:%d\n",
			g_s1ap_cfg.s1ap_local_ip, g_s1ap_cfg.sctp_port);
	/*Create MME sctp listned socket*/
	g_sctp_fd = create_sctp_socket(g_s1ap_cfg.s1ap_local_ip,
					g_s1ap_cfg.sctp_port);

	if (g_sctp_fd == -1) {
		log_msg(LOG_ERROR, "Error in creating sctp socket. \n");
		return -E_FAIL;
	}

	pthread_attr_t attr;

	pthread_attr_init(&attr);
	/* set the thread detach state */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	int ret = pthread_create(&acceptSctp_t, &attr,&accept_sctp, NULL);
	if(ret < 0) {
		log_msg(LOG_ERROR,"SCTP ACCEPTS THREAD FAILED\n");
		return -E_FAIL;
	}

	pthread_attr_destroy(&attr);
	return SUCCESS;
}

/**
 * @brief Init all writer IPC channels for s1ap program
 * @return Success/fail error code
 */
int
init_writer_ipc()
{
	if ((ipcHndl_attach  = open_ipc_channel(
			INITUE_STAGE1_QUEUE, IPC_WRITE)) == -E_FAIL)
		return -E_FAIL;

	if ((ipcHndl_authresp  = open_ipc_channel(
			S1AP_AUTHRESP_STAGE3_QUEUE, IPC_WRITE)) == -E_FAIL)
		return -E_FAIL;

	if ((ipcHndl_secresp  = open_ipc_channel(
			S1AP_SECRESP_STAGE4_QUEUE, IPC_WRITE)) == -E_FAIL)
		return -E_FAIL;

	if ((ipcHndl_esmresp  = open_ipc_channel(
			S1AP_ESMRESP_STAGE5_QUEUE, IPC_WRITE)) == -E_FAIL)
		return -E_FAIL;

	if ((ipcHndl_icsresp  = open_ipc_channel(
			S1AP_ICSRESP_STAGE7_QUEUE, IPC_WRITE)) == -E_FAIL)
		return -E_FAIL;

	if ((ipcHndl_attachomplete = open_ipc_channel(
			S1AP_ATT_COMP_STAGE8_QUEUE, IPC_WRITE)) == -E_FAIL)
		return -E_FAIL;

	if ((ipcHndl_detach = open_ipc_channel(
			S1AP_DTCHREQ_STAGE1_QUEUE, IPC_WRITE)) == -E_FAIL)
		return -E_FAIL;

	if ((ipcHndl_ctx_release_complete = open_ipc_channel(
			S1AP_CTXRELRESP_STAGE3_QUEUE, IPC_WRITE)) == -E_FAIL)
		return -E_FAIL;

	log_msg(LOG_INFO, "Writer IPCs initialized\n");

	return SUCCESS;
}

/**
 * @brief Init handlers to process messages coming from mme-app
 * @return error code.
 */
int
start_mme_resp_handlers()
{
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	/* set the thread detach state */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&authReq_t, &attr, &authreq_handler, NULL);
	pthread_create(&smcReq_t, &attr, &secreq_handler, NULL);
	pthread_create(&esmReq_t, &attr, &esmreq_handler, NULL);
	pthread_create(&icsReq_t, &attr, &icsreq_handler, NULL);
	pthread_create(&detachAcpt_t, &attr, &detach_accept_handler, NULL);

	pthread_attr_destroy(&attr);
	return SUCCESS;
}

/**
 *@Thread to handle send messages to sctp thread
 * NOT user currently.
 */
void *
sctp_write(void *args)
{
	while(1) {

		sleep(10);

	}
}

int
start_sctp_threads()
{
	pthread_t sctp_writer;
	pthread_attr_t attr;
	int res = SUCCESS;

	res = pthread_attr_init(&attr);
	if (res != 0)
		return -E_FAIL;

	res = pthread_attr_setdetachstate(&attr,
			PTHREAD_CREATE_DETACHED);
	if (res != 0)
		return -E_FAIL;

	res = pthread_create(&sctp_writer, &attr,
			sctp_write, NULL);
	if (res != 0) {
		log_msg(LOG_ERROR, "Error in creating sctp writer thread.\n");
		pthread_attr_destroy(&attr);
		return -E_FAIL;
	}

	pthread_attr_destroy(&attr);

	return SUCCESS;
}

/**
 * @brief - main entry point for s1ap application. Read json config,
 * start all the handlers. Connect with configured enb
 */
int
main(int argc, char **argv)
{
	parse_args(argc, argv);

	init_parser("conf/s1ap.json");
	parse_s1ap_conf();

	if (init_writer_ipc() != SUCCESS) {
		log_msg(LOG_ERROR, "Error in initializing writer ipc.\n");
		return -E_FAIL_INIT;
	}

	if (start_mme_resp_handlers() != SUCCESS) {
			log_msg(LOG_ERROR, "Error in starting mme response handlers.\n");
			return -E_FAIL_INIT;
	}

	/* Initialize thread pool for sctp request parsers */
	g_tpool = thread_pool_new(THREADPOOL_SIZE);

	if (g_tpool == NULL) {
		log_msg(LOG_ERROR, "Error in creating thread pool. \n");
		return -E_FAIL_INIT;
	}
	log_msg(LOG_INFO, "S1AP Listener theadpool initalized.\n");


	if (init_sctp() != SUCCESS) {
		log_msg(LOG_ERROR, "Error in initializing sctp server.\n");
		return -E_FAIL_INIT;
	}

	log_msg(LOG_INFO, "Connection accespted from enb \n");

	if (start_sctp_threads() != SUCCESS) {
		log_msg(LOG_ERROR, "Error in creating sctp reader/writer thread.\n");
		return -E_FAIL_INIT;
	}

	log_msg(LOG_INFO, "sctp reader/writer thread started.\n");

	while (1) {
		sleep(10);
	}

	return SUCCESS;
}
