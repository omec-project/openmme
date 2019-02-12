/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
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
#include <stdbool.h>
#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>
#include <freeDiameter/libfdproto.h>

#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "sec.h"
#include "s6a_fd.h"
#include "s6a.h"
#include "s6a_config.h"
#include "detach_stage1_info.h"

/************************************************************************
Current file : Stage  - AIR handler of S6A
ATTACH stages :
@@@	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage1 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage1 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage1 handler]-->create session
	Stage 6 : create session resp-->[stage1 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage1 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

static int g_Q_detachread_fd;

/*Making global just to avoid stack passing*/

static char buf[S6A_PURGEREQ_STAGE1_BUF_SIZE];

extern s6a_config g_s6a_cfg;
extern struct fd_dict_objects g_fd_dict_objs;
extern struct fd_dict_data g_fd_dict_data;
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "Waiting for session detach initialiser  from mme-app\n");
	if ((g_Q_detachread_fd  = open_ipc_channel(S6A_DTCHREQ_STAGE1_QUEUE, IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader detach channel.\n");
		pthread_exit(NULL);
	}
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;
	memset(buf, 0, S6A_PURGEREQ_STAGE1_BUF_SIZE);
	while (bytes_read < S6A_PURGEREQ_STAGE1_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_detachread_fd, buf, S6A_PURGEREQ_STAGE1_BUF_SIZE)) == -1) {
			log_msg(LOG_ERROR, "Error in reading from AIR Q.\n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Purge msg received, len - %d\n", bytes_read);
	}
	return bytes_read;
}

/**
 * @brief Prepare PUR freediameter message, dump and post to HSS
 * @param[in] ue_idx UE indx to append to session id
 * @param[in] imsi - IMSI
 * @return int Sucess or failure code
 */
static int
send_purge(int ue_idx, char imsi[])
{
	struct msg *fd_msg = NULL;
	union avp_value val;
	struct s6a_sess_info s6a_sess = {.sess_id="", .sess_id_len = 0};

	if(SUCCESS != create_fd_sess_id(&s6a_sess, ue_idx)) return S6A_FD_ERROR;

	CHECK_FCT_DO(fd_msg_new(g_fd_dict_objs.PUR, MSGFL_ALLOC_ETEID, &fd_msg),
			return S6A_FD_ERROR);

	/*AVP: Session-Id*/
	val.os.data = (unsigned char*)s6a_sess.sess_id;
	val.os.len = strlen(s6a_sess.sess_id);
	add_fd_msg(&val, g_fd_dict_objs.sess_id, &fd_msg);

	/*AVP: Auth-Session-State*/
	val.i32 = 1; /*NO_STATE_MAINTAINED*/
	val.os.len = 0;
	add_fd_msg(&val, g_fd_dict_objs.auth_sess_state, &fd_msg);

	/*AVP: Origin-Host/Realm*/
	CHECK_FCT_DO(fd_msg_add_origin(fd_msg, 0), return S6A_FD_ERROR);

	/*AVP: Destination-Host*/
	val.os.data = (unsigned char *)g_s6a_cfg.hss_host_name;
	val.os.len = strlen(g_s6a_cfg.hss_host_name);
	add_fd_msg(&val, g_fd_dict_objs.dest_host, &fd_msg);

	/*AVP: Destination-Realm*/
	val.os.data = (unsigned char*)g_s6a_cfg.realm;
	val.os.len = strlen(g_s6a_cfg.realm);
	add_fd_msg(&val, g_fd_dict_objs.dest_realm, &fd_msg);

	/*AVP: User-Name*/
	val.os.data = (unsigned char*)imsi;
	val.os.len = strlen(imsi);
	add_fd_msg(&val, g_fd_dict_objs.user_name, &fd_msg);

	/*AVP: PUR-Flags*/
	val.u32 = true;
	val.os.len = 0;
	add_fd_msg(&val, g_fd_dict_objs.PUR_flags, &fd_msg);

	dump_fd_msg(fd_msg);

	/*Post message to hss*/
	CHECK_FCT_DO(fd_msg_send(&fd_msg, NULL, NULL), return S6A_FD_ERROR);

	return SUCCESS;
}

static void
send_rpc_purge(int ue_idx, char imsi[])
{
	/* TODO: For builitn HSS, we are not sending purge request to HSS,
	 * returning dummy reply. Send request to builtin HSS and
	 * handle response.
	 */
	handle_perf_hss_purge_resp(ue_idx);
	return;
}

/**
* Stage specific message processing.
*/
static int
detach_processing()
{
	struct s6a_purge_Q_msg *purge_msg = (struct s6a_purge_Q_msg*)buf;
	char imsi[16] = {0};

	/*Parse and validate  the buffer*/
	imsi_bin_to_str(purge_msg->IMSI, imsi);
	log_msg(LOG_INFO, "IMSI recvd - %s\n", imsi);

	if (HSS_FD == g_s6a_cfg.hss_type)
		send_purge(purge_msg->ue_idx, imsi);
	else {
		log_msg(LOG_INFO, "Sending over IPC \n");
		send_rpc_purge(purge_msg->ue_idx, imsi);
	}

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
shutdown_detach()
{
	close_ipc_channel(g_Q_detachread_fd);
	log_msg(LOG_INFO, "Shutdown detach handler \n");
	pthread_exit(NULL);
	return;
}


/**
* Thread function for stage.
*/
void*
detach_handler(void *data)
{
	init_stage();

	sleep(5);

	log_msg(LOG_INFO, "Detach Q handler ready.\n");

	while(1){
		read_next_msg();

		detach_processing();

		post_to_next();
	}

	return NULL;
}

