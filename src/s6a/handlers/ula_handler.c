/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdproto.h>
#include <freeDiameter/libfdcore.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "s6a_fd.h"
#include "s6a.h"
#include "stage1_s6a_msg.h"
#include "hss_message.h"

extern int g_Q_mme_ula_fd;
extern struct fd_dict_objects g_fd_dict_objs;
extern struct fd_dict_data g_fd_dict_data;

/**
 * @brief Parse subscription information for UE
 * @param[in] avp_ptr - POinter to subscription data avp
 * @param[out] ula information filled with parsed data
 * @return void
 */
static void
parse_ula_subscription_data(struct avp *avp_ptr, struct ula_Q_msg *ula)
{
	struct avp *next = NULL;
	struct avp_hdr *element = NULL;

	CHECK_FCT_DO(fd_msg_browse(avp_ptr, MSG_BRW_FIRST_CHILD, &next, NULL),
			return);

	/*Iterate through subscription data child avps*/
	CHECK_FCT_DO(fd_msg_browse(next, MSG_BRW_NEXT, &next, NULL),
			return);
	for(;
		NULL != next;
		fd_msg_browse(next, MSG_BRW_NEXT, &next, NULL)) {

		fd_msg_avp_hdr (next, &element);

		if(NULL == element) return;

		/*AVP: Access-Restriction-Data(1426)*/
		if(g_fd_dict_data.access_restriction_data.avp_code ==
				element->avp_code) {
			ula->access_restriction_data = element->avp_value->u32;
			continue;
		}

		/*AVP: Subscriber-Status(1424)*/
		if(g_fd_dict_data.subscriber_status.avp_code == element->avp_code) {
			ula->subscription_status = element->avp_value->i32;
			continue;
		}

		/*AVP: Network-Access-Mode(1417)*/
		if(g_fd_dict_data.net_access_mode.avp_code == element->avp_code) {
			ula->net_access_mode = element->avp_value->i32;
			continue;
		}

		/*AVP: Regional-Subscription-Zone-Code(1446)*/
		if(g_fd_dict_data.reg_subs_zone_code.avp_code ==
				element->avp_code) {
			//element->avp_value : 10 string values of len 4
			continue;
		}

		/*AVP: MSISDN(701)*/
		if(g_fd_dict_data.MSISDN.avp_code == element->avp_code) {
			memcpy(ula->MSISDN, element->avp_value->os.data, element->avp_value->os.len);
			continue;
		}

		/*AVP: AMBR(1435)*/
			/*AVP: Max-Requested-Bandwidth-UL(516)
			  AVP: Max-Requested-Bandwidth-DL(515*/
		if(g_fd_dict_data.AMBR.avp_code == element->avp_code) {
			/*AMBR has its own child elements, iterate through those*/
			struct avp *ambr_itr = NULL;
			struct avp_hdr *ambr_element = NULL;

			CHECK_FCT_DO(fd_msg_browse(next, MSG_BRW_FIRST_CHILD,
						&ambr_itr, NULL), return);

			/*Iterate through subscription data child avps*/
			while(NULL != ambr_itr) {
				fd_msg_avp_hdr(ambr_itr, &ambr_element);

				if(g_fd_dict_data.max_req_bandwidth_UL.avp_code ==
						ambr_element->avp_code) {
					ula->max_requested_bw_ul = ambr_element->avp_value->u32;
				}

				if(g_fd_dict_data.max_req_bandwidth_DL.avp_code ==
						ambr_element->avp_code) {
					ula->max_requested_bw_dl = ambr_element->avp_value->u32;
				}

				CHECK_FCT_DO(fd_msg_browse(ambr_itr, MSG_BRW_NEXT,
						&ambr_itr, NULL), return);
			}
			continue;
		}

		/*AVP: APN-Configuration-Profile(1429)*/
			/*AVP: Context-Identifier(1423)
			AVP: All-APN-Configurations-Included-Indicator(1428)
			AVP: APN-Configuration(1430)*/
		if(g_fd_dict_data.APN_config_profile.avp_code == element->avp_code) {
			/*APN profile has its own child elements, iterate through
			 * those*/
			struct avp *apn_cfg_prof_itr = NULL;
			struct avp_hdr *apn_cfg_prof_element = NULL;

			CHECK_FCT_DO(fd_msg_browse(next, MSG_BRW_FIRST_CHILD,
						&apn_cfg_prof_itr, NULL), return);

			/*Iterate through subscription data child avps*/
			while(NULL != apn_cfg_prof_itr) {
				fd_msg_avp_hdr(apn_cfg_prof_itr, &apn_cfg_prof_element);

				if(g_fd_dict_data.ctx_id.avp_code ==
						apn_cfg_prof_element->avp_code) {
					ula->apn_config_profile_ctx_id =
						apn_cfg_prof_element->avp_value->u32;
				} else
				if(g_fd_dict_data.all_APN_configs_included_ind.avp_code ==
						apn_cfg_prof_element->avp_code) {
					ula->all_APN_cfg_included_ind =
						apn_cfg_prof_element->avp_value->i32;
				} else
				if(g_fd_dict_data.APN_config.avp_code ==
						apn_cfg_prof_element->avp_code){

					//APN configuration list : There is list of elements to read
					struct avp *apn_cfg_itr = NULL;
					struct avp_hdr *apn_cfg_element = NULL;

					CHECK_FCT_DO(fd_msg_browse(apn_cfg_prof_itr,
							MSG_BRW_FIRST_CHILD, &apn_cfg_itr, NULL), return);

					while(NULL != apn_cfg_itr){

						fd_msg_avp_hdr(apn_cfg_itr, &apn_cfg_element);

						// TODO g_fd_dict_data does not have service_slection
						// will finish this part in the following patch
						// service_slection code is 493
						// if(g_fd_dict_data.service_slection ==
						if (493 == apn_cfg_element->avp_code){

							log_msg(LOG_INFO, "APN name recvd from hss - %s\n",
									apn_cfg_element->avp_value->os.data);
							log_msg(LOG_INFO, "APN length recvd from hss - %lu\n",
									apn_cfg_element->avp_value->os.len);

							// TODO will push another patch to extend
							// message Q to use the code blow
							/*
							memcpy(ula->apn.val,
									apn_cfg_element->avp_value->os.data,
									apn_cfg_element->avp_value->os.len);
							ula->apn.len = apn_cfg_element->avp_value->os.len;
							*/
						}

						apn_cfg_prof_itr = apn_cfg_itr;

						CHECK_FCT_DO(fd_msg_browse(apn_cfg_itr, MSG_BRW_NEXT,
								&apn_cfg_itr, NULL), return);

					}
					continue;

				}

				CHECK_FCT_DO(fd_msg_browse(apn_cfg_prof_itr, MSG_BRW_NEXT,
						&apn_cfg_prof_itr, NULL), return);
			}
			continue;
		}

		/*AVP: Subscribed-Periodic-RAU-TAU-Timer(1619)*/
		if(g_fd_dict_data.subsc_periodic_RAU_TAU_tmr.avp_code
				== element->avp_code) {
			ula->RAU_TAU_timer = element->avp_value->u32;
			continue;
		}

	}
}

/**
 * @brief Call back registered to handle ULA from hss
 * @param callback requiremd arguments
 * @return int error code as success or failure
 */
int
ula_resp_callback(struct msg **buf, struct avp *avp_ptr, struct session *sess,
			void *data, enum disp_action *action)
{
	int sess_id_len, ue_idx;
	unsigned char *sess_id= NULL;
	struct ula_Q_msg ula;
	struct avp *subsc_ptr = NULL;

	CHECK_FCT_DO(fd_sess_getsid(sess, &sess_id, (size_t*)&sess_id_len),
		return S6A_FD_ERROR);

	log_msg(LOG_INFO, "\nCallback ----- >session id=%s \n", sess_id);

	ula.res = SUCCESS;
	ue_idx = get_ue_idx_from_fd_resp(sess_id, sess_id_len);

	/*AVP: Subscription-Data(1400)*/
	fd_msg_search_avp(*buf, g_fd_dict_objs.subscription_data, &subsc_ptr);

	/*Parse fd message and extract ula information*/
	if(NULL != subsc_ptr) parse_ula_subscription_data(subsc_ptr, &ula);

	fd_msg_free(*buf);
	*buf = NULL;

	ula.ue_idx = ue_idx;

	/*Send to stage2 queue*/
	write_ipc_channel(g_Q_mme_ula_fd, (char*)&ula, S6A_ULA_STAGE2_BUF_SIZE);
	return SUCCESS;
}

/*Handler for ULA coming from built in perf HS*/
void
handle_perf_hss_ula(int ue_idx, struct hss_ula_msg *ula)
{
	struct ula_Q_msg ula_msg;

	ula_msg.ue_idx = ue_idx;
	ula_msg.res = ula->subscription_state;
	/*Send to stage2 queue*/
	write_ipc_channel(g_Q_mme_ula_fd, (char*)&ula_msg, S6A_ULA_STAGE2_BUF_SIZE);
}
