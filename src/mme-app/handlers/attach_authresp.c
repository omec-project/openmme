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
#include "stage3_info.h"

/************************************************************************
Current file : Stage 3 handler.
ATTACH stages :
	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
-->	Stage 3 : Auth resp-->[stage3 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage4 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage5 handler]-->create session
	Stage 6 : create session resp-->[stage6 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage7 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_authresp_fd;
static int g_Q_secmode_fd;
static int g_Q_s6a_resync_air_fd;

/*Making global just to avoid stack passing*/
static char buf[S1AP_AUTHRESP_STAGE3_BUF_SIZE];
static struct s6a_Q_msg s6a_air_resync_req;

extern uint32_t attach_stage3_counter;

/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((g_Q_authresp_fd  = open_ipc_channel(S1AP_AUTHRESP_STAGE3_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 3 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 3 reader - s1ap Authentication response : Connected\n");

	/*Open destination queue for writing. It is AIR, ULR Q in this stage*/
	log_msg(LOG_INFO, "Stage 3 writer  - s1ap Security mode cmd: waiting\n");
	g_Q_secmode_fd = open_ipc_channel(S1AP_SECREQ_STAGE3_QUEUE, IPC_WRITE);
	if (g_Q_secmode_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel:S1ap-Sec mode\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 3 writer - s1ap Security mode cmd: Connected\n");
	
    g_Q_s6a_resync_air_fd = open_ipc_channel(S6A_REQ_STAGE1_QUEUE, IPC_WRITE);

	if (g_Q_s6a_resync_air_fd == -1) {
		log_msg(LOG_ERROR, "Error in opening Writer IPC channel: S6A - AIR\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage1 writer - AIR: Connected\n");
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_AUTHRESP_STAGE3_BUF_SIZE );
	while (bytes_read < S1AP_AUTHRESP_STAGE3_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_authresp_fd, buf, S1AP_AUTHRESP_STAGE3_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Authentication response Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
stage3_processing()
{
	/*Parse and validate  the buffer*/
	struct authresp_Q_msg *auth_resp = (struct authresp_Q_msg *)buf;
	struct UE_info *ue_entry = GET_UE_ENTRY(auth_resp->ue_idx);

	ue_entry->ue_state = STAGE3_WAITING;
	/*Check the state*/
	if(SUCCESS != auth_resp->status) {
		log_msg(LOG_INFO, "eNB authentication failure for UE %d",
			auth_resp->ue_idx);
        if(auth_resp->auts.len == 0)
        {
            log_msg(LOG_ERROR,"No AUTS. Not Synch failure");
		    return E_FAIL;//report failure
        }
        else
        {
            log_msg(LOG_INFO,"AUTS recvd.  Synch failure. send AIR");
            memcpy(&(s6a_air_resync_req.imsi), &(ue_entry->IMSI), BINARY_IMSI_LEN);
            memcpy(&(s6a_air_resync_req.tai), &(ue_entry->tai), sizeof(struct TAI));
            memcpy(&(s6a_air_resync_req.auts), &(auth_resp->auts), sizeof(struct AUTS));
            s6a_air_resync_req.ue_idx = auth_resp->ue_idx;
            ue_entry->ue_state = ATTACH_STAGE1_RESYNC;
        }   
	}
#if 0
	log_msg(LOG_ERROR, "stage 3 processing memcmp - %d, %d, %d", &(ue_entry->aia_sec_info->xres.val),
                &(auth_resp->res.val),
                auth_resp->res.len);
	if(memcmp(&(ue_entry->aia_sec_info->xres.val),
		&(auth_resp->res.val),
		auth_resp->res.len) != 0) {
		log_msg(LOG_ERROR, "Invalid auth result received for UE %d",
			auth_resp->ue_idx);
		return E_FAIL;//report failure
	}
#endif
	log_msg(LOG_INFO, "Stage 3: Auth resp done for UE: %d\n",
		auth_resp->ue_idx);

	/*Ready post to next processing*/
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	struct sec_mode_Q_msg sec_mode_msg;
	struct authresp_Q_msg *authresp = (struct authresp_Q_msg *)buf;
	struct UE_info *ue_entry = GET_UE_ENTRY(authresp->ue_idx);

	if(STAGE3_WAITING == ue_entry->ue_state)
    {
        sec_mode_msg.ue_idx = authresp->ue_idx;
        sec_mode_msg.enb_s1ap_ue_id = ue_entry->s1ap_enb_ue_id;
        memcpy(&(sec_mode_msg.ue_network), &(ue_entry->ue_net_capab),
               sizeof(struct UE_net_capab));

        memcpy(&(sec_mode_msg.key), &(ue_entry->aia_sec_info->kasme),
               sizeof(struct KASME));

        memcpy(&(sec_mode_msg.int_key), &(ue_entry->ue_sec_info.int_key),
               NAS_INT_KEY_SIZE);

        sec_mode_msg.dl_seq_no = ue_entry->dl_seq_no++;

        sec_mode_msg.enb_fd = ue_entry->enb_fd;

        write_ipc_channel(g_Q_secmode_fd, (char *)&(sec_mode_msg), S1AP_SECREQ_STAGE3_BUF_SIZE);
        log_msg(LOG_INFO, "Sec mode msg posted to s1ap Q UE-%d.\n",
                authresp->ue_idx);

        attach_stage3_counter++;
    }
    else if(ATTACH_STAGE1_RESYNC == ue_entry->ue_state)
    {
        log_msg(LOG_INFO, "AIR Resync stage for UE-%d.\n", authresp->ue_idx);
        write_ipc_channel(g_Q_s6a_resync_air_fd, (char *)&(s6a_air_resync_req), S6A_REQ_Q_MSG_SIZE);
    }
    else
    {
        log_msg(LOG_ERROR, "Wrong stage for UE-%d.\n", authresp->ue_idx);
    }
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_stage3()
{
	close_ipc_channel(g_Q_secmode_fd);
	close_ipc_channel(g_Q_authresp_fd);
	close_ipc_channel(g_Q_s6a_resync_air_fd);
	log_msg(LOG_INFO, "Shutdown Stage 3 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
stage3_handler(void *data)
{
	char res[8]={0};
	init_stage();
	log_msg(LOG_INFO, "Stage 3 ready.\n");
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		if(!memcmp(buf, res, 8)){
			log_msg(LOG_ERROR, "empty msg recvd...continue\n");
			continue;
		}

		stage3_processing();

		post_to_next();
	}

	return NULL;
}
