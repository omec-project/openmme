/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>
#include <freeDiameter/libfdproto.h>

#include "log.h"
#include "s6a.h"
#include "s6a_fd.h"

/**Globals and externs**/
extern struct fd_dict_objects g_fd_dict_objs;
extern struct fd_dict_data g_fd_dict_data;
extern bool g_nolog;
extern enum log_levels g_log_level;
/**Globals and externs**/

/**
 * @brief Add element to freediameter message
 * ready
 * @param[in] val - AVP value to be added
 * @param[in] obj - Disctionary object
 * @param[in/out] msg_buf
 * @return int Sucess or failure code
 */
int
add_fd_msg(union avp_value *val, struct dict_object * obj,
		struct msg **msg_buf)
{
	struct avp *avp_val = NULL;

	CHECK_FCT_DO(fd_msg_avp_new(obj, 0, &avp_val), return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_msg_avp_setvalue(avp_val, val), return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_msg_avp_add(*msg_buf, MSG_BRW_LAST_CHILD, avp_val),
				return S6A_FD_ERROR);

	return SUCCESS;
}

/**
 * @brief Dumo freediameter message buffer
 * ready
 * @param[in] Freediameter message to print
 * @return void
 */
void
dump_fd_msg(struct msg *msg)
{
	//char *buf = NULL;
	//int len = 0;

	g_nolog = true;

	if (g_nolog) return;

	//TODO: correct - fprintf(stderr, "%s\n", fd_msg_dump_treeview(&buf, &len, NULL, msg,
	//			fd_g_config->cnf_dict, 0, 1));
	//free(buf);
}

/**
 * @brief Extract last integeger representing ue index from session ID
 * @param[in] sid - session id
 * @param[in] sidlen - session id len
 * @return int - eror code
 */
int
get_ue_idx_from_fd_resp(unsigned char *sid, int sidlen)
{
	int index = -1;
	char *tmp = strrchr((char *)sid, ';');

	index = strtol(++tmp, NULL, 10);
	log_msg(LOG_INFO, "Received resp for index %d\n", index);
	return index;
}

/**
 * @brief Initialize free diameter vendor info
 * @param None
 * @return int - eror code
 */
int
s6a_fd_init()
{
	//TODO: check vendor id
	vendor_id_t vendor_id = 10415;

	FD_DICT_SEARCH(DICT_VENDOR, VENDOR_BY_ID, &vendor_id, g_fd_dict_objs.vendor_id);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.vendor_id, &g_fd_dict_data.vendor_data),
		return S6A_FD_ERROR);

	return SUCCESS;
}

/**
 * @brief Initialize freediameter dictionary objects
 * @param None
 * @return int - error code
 */
int
s6a_fd_objs_init()
{
	//TODO: Check app id
	application_id_t app_s6a = 16777251;

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME, "Result-Code",
			g_fd_dict_objs.res_code);

	FD_DICT_SEARCH(DICT_APPLICATION, APPLICATION_BY_ID, &app_s6a,
			g_fd_dict_objs.s6a_app);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME, "Experimental-Result",
					g_fd_dict_objs.exp_res);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME, "Auth-Application-Id",
					g_fd_dict_objs.auth_app_id);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME, "Session-Id",
					g_fd_dict_objs.sess_id);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME, "Auth-Session-State",
					g_fd_dict_objs.auth_sess_state);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME, "Destination-Host",
					g_fd_dict_objs.dest_host);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME, "Destination-Realm",
					g_fd_dict_objs.dest_realm);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME, "User-Name",
					g_fd_dict_objs.user_name);

	/*seach and map avp names to elements*/
	FD_DICT_SEARCH(DICT_COMMAND, CMD_BY_NAME,
					"Authentication-Information-Request",
					g_fd_dict_objs.AIR);

	FD_DICT_SEARCH(DICT_COMMAND, CMD_BY_NAME,
					"Authentication-Information-Answer",
					g_fd_dict_objs.AIA);

	FD_DICT_SEARCH(DICT_COMMAND, CMD_BY_NAME, "Update-Location-Request",
				g_fd_dict_objs.ULR);

	FD_DICT_SEARCH(DICT_COMMAND, CMD_BY_NAME, "Update-Location-Answer",
					g_fd_dict_objs.ULA);

	FD_DICT_SEARCH(DICT_COMMAND, CMD_BY_NAME, "Purge-UE-Request",
					g_fd_dict_objs.PUR);

	FD_DICT_SEARCH(DICT_COMMAND, CMD_BY_NAME, "Purge-UE-Answer",
					g_fd_dict_objs.PUA);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Visited-PLMN-Id",
					g_fd_dict_objs.visited_PLMN_id);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Requested-EUTRAN-Authentication-Info",
					g_fd_dict_objs.req_EUTRAN_auth_info);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Number-Of-Requested-Vectors",
					g_fd_dict_objs.no_of_req_vectors);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Immediate-Response-Preferred",
					g_fd_dict_objs.immediate_resp_pref);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Re-Synchronization-Info",
					g_fd_dict_objs.resync_info);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Authentication-Info",
					g_fd_dict_objs.auth_info);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "E-UTRAN-Vector",
					g_fd_dict_objs.E_UTRAN_vector);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "RAND",
					g_fd_dict_objs.RAND);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "XRES",
					g_fd_dict_objs.XRES);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "AUTN",
					g_fd_dict_objs.AUTN);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "KASME",
					g_fd_dict_objs.KASME);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "RAT-Type",
					g_fd_dict_objs.RAT_type);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "ULR-Flags",
					g_fd_dict_objs.ULR_flags);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "ULA-Flags",
					g_fd_dict_objs.ULA_flags);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Subscription-Data",
					g_fd_dict_objs.subscription_data);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Subscriber-Status",
					g_fd_dict_objs.subscriber_status);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "MSISDN",
					g_fd_dict_objs.MSISDN);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Network-Access-Mode",
					g_fd_dict_objs.net_access_mode);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Access-Restriction-Data",
					g_fd_dict_objs.access_restriction_data);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "AMBR",
					g_fd_dict_objs.AMBR);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Max-Requested-Bandwidth-UL",
					g_fd_dict_objs.max_req_bandwidth_UL);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Max-Requested-Bandwidth-DL",
					g_fd_dict_objs.max_req_bandwidth_DL);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"APN-Configuration-Profile",
					g_fd_dict_objs.APN_config_profile);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Context-Identifier",
					g_fd_dict_objs.ctx_id);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Additional-Context-Identifier",
					g_fd_dict_objs.additional_ctx_id);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"All-APN-Configurations-Included-Indicator",
					g_fd_dict_objs.all_APN_configs_included_ind);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "APN-Configuration",
					g_fd_dict_objs.APN_config);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "PDN-Type",
					g_fd_dict_objs.PDN_type);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"PDN-GW-Allocation-Type",
					g_fd_dict_objs.PDN_GW_alloc_type);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Specific-APN-Info",
					g_fd_dict_objs.specific_APN_info);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Non-IP-PDN-Type-Indicator",
					g_fd_dict_objs.non_IP_PDN_type_ind);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Non-IP-Data-Delivery-Mechanism",
					g_fd_dict_objs.non_IP_data_delivery_mech);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "SCEF-ID",
					g_fd_dict_objs.SCEF_ID);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Priority-Level",
					g_fd_dict_objs.priority_Level);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Location-Area-Identity",
					g_fd_dict_objs.location_area_id);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "Tracking-Area-Identity",
					g_fd_dict_objs.tracking_area_id);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Subscribed-Periodic-RAU-TAU-Timer",
					g_fd_dict_objs.subsc_periodic_RAU_TAU_tmr);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS, "PUR-Flags",
					g_fd_dict_objs.PUR_flags);

	FD_DICT_SEARCH(DICT_AVP, AVP_BY_NAME_ALL_VENDORS,
					"Regional-Subscription-Zone-Code",
					g_fd_dict_objs.reg_subs_zone_code);

	return SUCCESS;
}

/**
 * @brief Initialize freediameter data objects for the dictionary object
 * initialized
 * @param None
 * @return int - error code
 */
int
s6a_fd_data_init()
{
	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.s6a_app,
				&g_fd_dict_data.app_s6a_data), return S6A_FD_ERROR);


	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.res_code,
				&g_fd_dict_data.res_code), return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.exp_res,
				&g_fd_dict_data.exp_res), return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.auth_app_id,
			&g_fd_dict_data.auth_app_id),
			return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.sess_id,
				&g_fd_dict_data.sess_id), return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.auth_sess_state,
			&g_fd_dict_data.auth_sess_state),
			return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.dest_host,
				&g_fd_dict_data.dest_host), return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.dest_realm,
				&g_fd_dict_data.dest_realm), return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.user_name,
				&g_fd_dict_data.user_name), return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.visited_PLMN_id,
				&g_fd_dict_data.visited_PLMN_id),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.req_EUTRAN_auth_info,
				&g_fd_dict_data.req_EUTRAN_auth_info),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.no_of_req_vectors,
				&g_fd_dict_data.no_of_req_vectors),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.immediate_resp_pref,
				&g_fd_dict_data.immediate_resp_pref),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.resync_info,
				&g_fd_dict_data.resync_info),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.auth_info,
				&g_fd_dict_data.auth_info),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.E_UTRAN_vector,
				&g_fd_dict_data.E_UTRAN_vector),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.RAND,
				&g_fd_dict_data.RAND),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.XRES,
				&g_fd_dict_data.XRES),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.AUTN,
				&g_fd_dict_data.AUTN),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.KASME,
				&g_fd_dict_data.KASME),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.RAT_type,
				&g_fd_dict_data.RAT_type),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.ULR_flags,
				&g_fd_dict_data.ULR_flags),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.ULA_flags,
				&g_fd_dict_data.ULA_flags),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.subscription_data,
				&g_fd_dict_data.subscription_data),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.subscriber_status,
				&g_fd_dict_data.subscriber_status),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.MSISDN,
				&g_fd_dict_data.MSISDN),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.net_access_mode,
				&g_fd_dict_data.net_access_mode),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.access_restriction_data,
				&g_fd_dict_data.access_restriction_data),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.AMBR,
				&g_fd_dict_data.AMBR),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.max_req_bandwidth_UL,
				&g_fd_dict_data.max_req_bandwidth_UL),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.max_req_bandwidth_DL,
				&g_fd_dict_data.max_req_bandwidth_DL),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.APN_config_profile,
				&g_fd_dict_data.APN_config_profile),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.ctx_id,
				&g_fd_dict_data.ctx_id),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.additional_ctx_id,
				&g_fd_dict_data.additional_ctx_id),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.all_APN_configs_included_ind,
				&g_fd_dict_data.all_APN_configs_included_ind),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.APN_config,
				&g_fd_dict_data.APN_config),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.PDN_type,
				&g_fd_dict_data.PDN_type),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.PDN_GW_alloc_type,
				&g_fd_dict_data.PDN_GW_alloc_type),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.specific_APN_info,
				&g_fd_dict_data.specific_APN_info),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.non_IP_PDN_type_ind,
				&g_fd_dict_data.non_IP_PDN_type_ind),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.non_IP_data_delivery_mech,
				&g_fd_dict_data.non_IP_data_delivery_mech),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.SCEF_ID,
				&g_fd_dict_data.SCEF_ID),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.priority_Level,
				&g_fd_dict_data.priority_Level),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.location_area_id,
				&g_fd_dict_data.location_area_id),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.tracking_area_id,
				&g_fd_dict_data.tracking_area_id),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.subsc_periodic_RAU_TAU_tmr,
				&g_fd_dict_data.subsc_periodic_RAU_TAU_tmr),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.PUR_flags,
				&g_fd_dict_data.PUR_flags),
				return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_dict_getval(g_fd_dict_objs.reg_subs_zone_code,
				&g_fd_dict_data.reg_subs_zone_code),
				return S6A_FD_ERROR);

	return SUCCESS;
}

int
s6a_fd_cb_reg(void)
{
	struct disp_when data;

	memset(&data, 0, sizeof(data));
	data.app = g_fd_dict_objs.s6a_app;

	/* Register resp callbacks */
	data.command = g_fd_dict_objs.AIA;
	CHECK_FCT_DO(fd_disp_register(aia_resp_callback, DISP_HOW_CC, &data,
			NULL, NULL),
			return S6A_FD_ERROR);

	data.command = g_fd_dict_objs.ULA;
	CHECK_FCT_DO(fd_disp_register(ula_resp_callback, DISP_HOW_CC, &data,
			NULL, NULL),
			return S6A_FD_ERROR);

	data.command = g_fd_dict_objs.PUA;
	CHECK_FCT_DO(fd_disp_register(purge_resp_callback, DISP_HOW_CC, &data,
	                     NULL, NULL),
	                     return S6A_FD_ERROR);

	CHECK_FCT_DO(fd_disp_app_support(g_fd_dict_objs.s6a_app,
			g_fd_dict_objs.vendor_id, 1, 0),
			return S6A_FD_ERROR);

	return SUCCESS;
}

/**
 * @brief Create session ID for every HSS request. Append UE ID to session ID
 * initialized
 * @param [out] session ID created
 * @param [in] UE index to append to session ID
 * @return int - error code
 */
short
create_fd_sess_id(struct s6a_sess_info *s6a_sess,
	int ue_idx)
{
	struct session *sess = NULL;
	unsigned char *sess_id;
	size_t sess_id_len;
	char idx[10] = {0};

	/* clear the session id if exists */
	if (s6a_sess->sess_id_len > 0) {
		int exist = false;
		CHECK_FCT_DO(fd_sess_fromsid((unsigned char*)s6a_sess->sess_id,
			s6a_sess->sess_id_len, &sess, &exist),
			return S6A_FD_ERROR);

		if (exist == 0) {
			CHECK_FCT_DO(fd_sess_destroy(&sess), return S6A_FD_ERROR);
			sess = NULL;
		}
	}

	sprintf(idx, "%d", ue_idx);
	if (sess == NULL) {
		CHECK_FCT_DO(fd_sess_new(&sess, fd_g_config->cnf_diamid,
		fd_g_config->cnf_diamid_len, (unsigned char*)idx, strlen(idx)),
		return S6A_FD_ERROR);
	}
	CHECK_FCT_DO(fd_sess_getsid(sess, &sess_id, &sess_id_len),
			return S6A_FD_ERROR);

	s6a_sess->sess_id_len = (unsigned char)sess_id_len;
	memcpy(s6a_sess->sess_id, sess_id, s6a_sess->sess_id_len);
	s6a_sess->sess_id[s6a_sess->sess_id_len] = '\0';

	return SUCCESS;
}

/**
 * @brief Parse AVP received in freediameter response
 * initialized
 * @param [in]avp - AVP value receivned
 * @param [out] result value parserd out of avp
 * @return int - error code
 */
short
parse_fd_result(struct avp *avp, struct fd_result *res)
{
	struct avp_hdr *hdr;
	struct avp *child_avp = NULL;

	CHECK_FCT_DO(fd_msg_avp_hdr(avp, &hdr), return S6A_FD_ERROR);
	if (hdr->avp_code != g_fd_dict_data.exp_res.avp_code)
	   return S6A_FD_ERROR;

	CHECK_FCT_DO(fd_msg_browse(avp, MSG_BRW_FIRST_CHILD, &child_avp, NULL),
			return S6A_FD_ERROR);

	while (child_avp) {
	   fd_msg_avp_hdr (child_avp, &hdr);

	   if (hdr->avp_code ==
		g_fd_dict_data.exp_res_code.avp_code) {
			res->result_code = hdr->avp_value->u32;
			res->present = true;
		} else if (hdr->avp_code == g_fd_dict_data.vendor_id.avp_code) {
			res->vendor_id = hdr->avp_value->u32;
		}

		CHECK_FCT_DO(fd_msg_browse(child_avp, MSG_BRW_NEXT, &child_avp,
				NULL),
				return S6A_FD_ERROR);
	}

	return SUCCESS;
}
