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
#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>
#include <freeDiameter/libfdproto.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "s6a_fd.h"
#include "s6a.h"
#include "stage1_s6a_msg.h"
#include "hss_message.h"

#define DIAMETER_SUCCESS 2001

/** Global and externs**/
extern struct fd_dict_objects g_fd_dict_objs;
extern struct fd_dict_data g_fd_dict_data;

extern int g_Q_mme_aia_fd;
/**global and externs end**/

/**
 * @brief Parse authentication information avp recvd in AIA. This contains
 * important security information for the UE
 * @param [in] avp_data - AVP value received
 * @param [out] aia - Security info is filled in to aia msg Q
 * @return int - error code
 */
static int
get_aia_sec_vector(struct avp *avp_data, struct aia_Q_msg *aia)
{
	struct avp *sub_avp = NULL;
	struct avp_hdr *element = NULL;

	CHECK_FCT_DO(fd_msg_avp_hdr(avp_data, &element),
			return S6A_FD_ERROR);

	/*Authentication-Info*/
	if ((NULL == element) ||
			(element->avp_code != g_fd_dict_data.auth_info.avp_code))
		return S6A_FD_ERROR;

	/*Find first sub child of Authentication-Info*/
	CHECK_FCT_DO(fd_msg_browse(avp_data, MSG_BRW_FIRST_CHILD, &sub_avp,
			NULL),
			return S6A_FD_ERROR);

	/*Lookup for sub element "E-UTRAN-Vector" in loop*/
	while (NULL != sub_avp) {

		fd_msg_avp_hdr(sub_avp, &element);

		if ((NULL != element) && (element->avp_code ==
			g_fd_dict_data.E_UTRAN_vector.avp_code))
			/*Found the entry*/
			break;

		/*Iterate sub entries*/
		CHECK_FCT_DO(fd_msg_browse(sub_avp, MSG_BRW_NEXT, &sub_avp,
			NULL),
			return S6A_FD_ERROR);
	}

	/*Element "E-UTRAN-Vector" not found, then return*/
	if (NULL == sub_avp) return S6A_FD_ERROR;

	CHECK_FCT_DO(fd_msg_browse(sub_avp, MSG_BRW_FIRST_CHILD,
			&sub_avp, NULL),
			return S6A_FD_ERROR);

	/*Iterate all sub elements of E-UTRAN-Vector and filter sec vector params*/
	for (;
		NULL != sub_avp; /*Till null*/
//		CHECK_FCT_DO(fd_msg_browse(sub_avp, MSG_BRW_NEXT, &sub_avp, NULL),
//			return S6A_FD_ERROR) /*Iterate elements*/
		) {

		fd_msg_avp_hdr(sub_avp, &element);

		/*AVP: RAND(1447) l=28 f=VM- vnd=TGPP*/
		if (element->avp_code == g_fd_dict_data.RAND.avp_code) {

			//if (element->avp_value->os.len > sizeof(aia->sec.rand.val))
			if (element->avp_value->os.len > AIA_RAND_SIZE)
				return S6A_FD_ERROR;

			aia->sec.rand.len = element->avp_value->os.len;
			memcpy(aia->sec.rand.val, element->avp_value->os.data,
				aia->sec.rand.len);
		}

		/*AVP: XRES(1448) l=20 f=VM- vnd=TGPP*/
		if (element->avp_code == g_fd_dict_data.XRES.avp_code) {

			if (element->avp_value->os.len > AIA_RES_SIZE)
				return S6A_FD_ERROR;

			aia->sec.xres.len = element->avp_value->os.len;
			memcpy(aia->sec.xres.val, element->avp_value->os.data,
				aia->sec.xres.len);
		}

		/*AVP: AUTN(1449) l=28 f=VM- vnd=TGPP*/
		if (element->avp_code == g_fd_dict_data.AUTN.avp_code) {

			if (element->avp_value->os.len > AIA_AUTN_SIZE)
				return S6A_FD_ERROR;

			aia->sec.autn.len = element->avp_value->os.len;
			memcpy(aia->sec.autn.val, element->avp_value->os.data,
				aia->sec.autn.len);
		}

		/*AVP: KASME(1450) l=44 f=VM- vnd=TGPP*/
		if (element->avp_code == g_fd_dict_data.KASME.avp_code) {

			if (element->avp_value->os.len > AIA_KASME_SIZE)
				return S6A_FD_ERROR;

			aia->sec.kasme.len = element->avp_value->os.len;
			memcpy(aia->sec.kasme.val, element->avp_value->os.data,
				aia->sec.kasme.len);
		}

		CHECK_FCT_DO(fd_msg_browse(sub_avp, MSG_BRW_NEXT, &sub_avp, NULL),
			return S6A_FD_ERROR) /*Iterate elements*/

	}

	return SUCCESS;
}

static
void send_to_stage2(struct aia_Q_msg *aia)
{
	/*Send to stage2 queue*/
	write_ipc_channel(g_Q_mme_aia_fd, (char*)aia, S6A_AIA_STAGE2_BUF_SIZE);
}

int aia_resp_callback(struct msg **buf, struct avp *_avp,
		struct session *session, void *data,
		enum disp_action * action)
{
	int res = SUCCESS, sess_id_len;
	struct msg *resp = *buf;
	struct avp *avp_ptr = NULL;
	unsigned char *sess_id= NULL;
	struct aia_Q_msg aia;
	struct avp_hdr *avp_hdr = NULL;

	log_msg(LOG_INFO, "\nCallback ----- >AIA recvd\n");

	dump_fd_msg(resp);
	//TODO - workaround for dump call. Remove this.
	{
		char * buf = NULL;
		size_t len = 0;
		printf("%s\n", fd_msg_dump_treeview(&buf, &len, NULL, resp,
					fd_g_config->cnf_dict, 0, 1));
		free(buf);
	}

	CHECK_FCT_DO(fd_sess_getsid(session, &sess_id, (size_t*)&sess_id_len),
		return S6A_FD_ERROR);

	log_msg(LOG_INFO, "\nCallback ----- >session id=%s \n",sess_id);

	/*Retrieve UE index embedded in to session ID string at AIR time*/
	aia.ue_idx = get_ue_idx_from_fd_resp(sess_id, sess_id_len);

	/*AVP: Result-Code(268)*/
	fd_msg_search_avp(resp, g_fd_dict_objs.res_code, &avp_ptr);

	if (NULL != avp_ptr) {
		fd_msg_avp_hdr(avp_ptr, &avp_hdr);
		res = avp_hdr->avp_value->u32;

		if (DIAMETER_SUCCESS != res) {
			log_msg(LOG_ERROR, "Diameter error with HSS\n");
		}
		//Vikram: chk res = SUCCESS;

	} else {
		struct fd_result fd_res;

		avp_ptr = NULL;
		fd_msg_search_avp(resp, g_fd_dict_objs.exp_res,
			&avp_ptr);

		if (NULL == avp_ptr) {
			res = S6A_FD_ERROR;
		} else if (parse_fd_result(avp_ptr, &fd_res) != 0) {
			res = S6A_FD_ERROR;
		} else res = fd_res.result_code;
	}

	if (DIAMETER_SUCCESS == res) {
		/*AVP: Authentication-Info*/
		fd_msg_search_avp(resp, g_fd_dict_objs.auth_info,
			&avp_ptr);

		if (NULL != avp_ptr) {
			if (get_aia_sec_vector(avp_ptr, &aia) != SUCCESS)
				res = S6A_FD_ERROR;
		} else {
			res = S6A_FD_ERROR;
		}
	}

	/*Handled fd msg, do cleanup*/
	fd_msg_free(*buf);

	*buf = NULL;

	if (DIAMETER_SUCCESS != res) aia.res = S6A_AIA_FAILED;

	send_to_stage2(&aia);

	return SUCCESS;
}

void
handle_perf_hss_aia(int ue_idx, struct hss_aia_msg *aia)
{
	struct aia_Q_msg msg;

	msg.ue_idx = ue_idx;
	msg.res= 0;
	memcpy(&(msg.sec.rand), &(aia->rand), sizeof(RAND));
	memcpy(&(msg.sec.xres), &(aia->xres), sizeof(XRES));
	memcpy(&(msg.sec.autn), &(aia->autn), sizeof(AUTN));
	memcpy(&(msg.sec.kasme), &(aia->kasme), sizeof(KASME));

	send_to_stage2(&msg);/*handle diameter error*/
}
