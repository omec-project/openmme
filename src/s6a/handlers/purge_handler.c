/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
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
#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>
#include <freeDiameter/libfdproto.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "s6a_fd.h"
#include "s6a.h"
#include "detach_stage2_info.h"
#include "hss_message.h"

/** Global and externs**/
extern struct fd_dict_objects g_fd_dict_objs;
extern struct fd_dict_data g_fd_dict_data;
extern int g_Q_mme_purge_fd;
/**global and externs end**/

static
void send_to_stage2(struct purge_resp_Q_msg *aia)
{
	/*Send to stage2 queue*/
	write_ipc_channel(g_Q_mme_purge_fd, (char*)aia,
			S1AP_PURGERESP_STAGE2_BUF_SIZE);
}

/**
 * @brief callback handler for purge answer recvd from hss
 * Parse purge answer, state and do cleanup for freediameter
 * @params callback std
 * @return error/success
 */
int
purge_resp_callback(struct msg **buf, struct avp *avps, struct session *sess,
			void *data, enum disp_action *action)
{
	struct msg *resp = NULL;
	struct avp *avp_ptr = NULL;
	struct purge_resp_Q_msg purge_resp;
	struct avp_hdr *avp_header = NULL;
	unsigned int sess_id_len;
	unsigned char *sess_id= NULL;

	resp = *buf;

	dump_fd_msg(resp);

	/*read session id and extract ue index*/
	CHECK_FCT_DO(fd_sess_getsid(sess, &sess_id, (size_t*)&sess_id_len),
			return S6A_FD_ERROR);
	log_msg(LOG_INFO, "\nPurge callback ----- >session id=%s \n",sess_id);

	purge_resp.ue_idx = get_ue_idx_from_fd_resp(sess_id, sess_id_len);

	/*AVP: Result-Code*/
	avp_ptr = NULL;
	fd_msg_search_avp(resp, g_fd_dict_objs.res_code, &avp_ptr);

	if(NULL != avp_ptr) {
		fd_msg_avp_hdr(avp_ptr, &avp_header);
		purge_resp.status = avp_header->avp_value->u32;

		if (SUCCESS != purge_resp.status) {
			purge_resp.status = S6A_FD_ERROR;
		}
	} else {
		struct fd_result res;
		avp_ptr = NULL;

		fd_msg_search_avp(resp, g_fd_dict_objs.exp_res,
			&avp_ptr);

		if (NULL != avp_ptr) {
			purge_resp.status = S6A_FD_ERROR;
		}

		if (parse_fd_result(avp_ptr, &res) != SUCCESS) {
			purge_resp.status = S6A_FD_ERROR;
		}
		purge_resp.status =res.result_code;
	}

	/*Inform response to mme-app*/
	send_to_stage2(&purge_resp);

	/*Do cleanup for freediameter*/
	fd_msg_free(*buf);

	*buf = NULL;

	return SUCCESS;
}

/*Handler for AIA coming from built in perf HS*/
void
handle_perf_hss_purge_resp(int ue_idx)
{
	struct purge_resp_Q_msg purge_resp;

	purge_resp.ue_idx = ue_idx;
	purge_resp.status = 0;

	send_to_stage2(&purge_resp);
}
