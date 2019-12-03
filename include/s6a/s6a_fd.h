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

#ifndef __S6A_FD_H__
#define __S6A_FD_H__

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdproto.h>
#include <freeDiameter/libfdcore.h>

#include "err_codes.h"
#include "s6a.h"

/*Update location request(ULR) flag bitfields*/
/* Single-Registration-Indication  -------1*/
#define ULR_FLAG_SINGLE_REG_IND (1)
/*S6a/S6d-Indicator:               ------1-*/
#define ULR_FLAG_S6AS6D_IND (1<<1)
/*Skip-Subscriber-Data:            -----1--*/
#define ULR_FLAGS_SKIP_SUB_DATA (1<<2)
/*GPRS-Subscription-Data-Indicator:----1---*/
#define ULR_FLAGS_GPRS_SUBS_DATA_IBND (1<<3)
/*Node-Type-Indicator:             ---1----*/
#define ULR_FLAGS_NODE_TYPE_IIND (1<<4)
/*Initial-Attach-Indicator:        --1-----*/
#define ULR_FLAG_INIT_ATCH_IND (1<<5)
/*PS-LCS-Not-Supported-By-UE:      -1------*/
#define ULR_FLAG_PS_LCS_NOT_SUPPORTED_BY_UE (1<<6)
/*SMS-Only-Indication:             1-------*/
#define ULR_FLAG_SMS_ONLY_IND (1<<7)

#define S6A_RAT_EUTRAN 1004

#define FD_DICT_SEARCH(dict, cond, id, obj) \
	CHECK_FCT_DO(fd_dict_search(fd_g_config->cnf_dict, dict, cond,\
		(void*)id, &obj, ENOENT),\
		return S6A_FD_DICTSRCH_FAILED)

/**
 * @brief Freediameter result
 */
struct fd_result {
	bool present;
	unsigned int vendor_id;
	unsigned int result_code;
};

/**
 * @brief Freediameter disctionary objects user in s6a transactions
 */
struct fd_dict_objects {
	/*s6a and app id*/
	struct dict_object *vendor_id;
	struct dict_object *s6a_app;

	/*Message types*/
	struct dict_object *AIR; /*Authentication-Information-Request*/
	struct dict_object *AIA; /*Authentication-information-Answer*/
	struct dict_object *ULR; /*Update-Location-Request*/
	struct dict_object *ULA; /*Update-Location-Answer*/
	struct dict_object *PUR; /*Purge-Request*/
	struct dict_object *PUA; /*Purge-Answer*/

	/*common s6a requst header*/
	struct dict_object *auth_app_id;
	struct dict_object *sess_id;
	struct dict_object *dest_host;
	struct dict_object *dest_realm;
	struct dict_object *auth_sess_state;
	struct dict_object *res_code;
	struct dict_object *exp_res;
	struct dict_object *user_name;

	/*AIR elements*/
	struct dict_object *visited_PLMN_id;
	struct dict_object *req_EUTRAN_auth_info;
	struct dict_object *no_of_req_vectors;
	struct dict_object *immediate_resp_pref;
	struct dict_object *resync_info;

	/*AIA elements*/
	struct dict_object *auth_info;
	struct dict_object *E_UTRAN_vector;
	struct dict_object *RAND;
	struct dict_object *XRES;
	struct dict_object *AUTN;
	struct dict_object *KASME;

	/*ULR elements*/
	struct dict_object *RAT_type;
	struct dict_object *ULR_flags;

	/*ULA elements*/
	struct dict_object *ULA_flags;
	struct dict_object *subscription_data;
	struct dict_object *subscriber_status;
	struct dict_object *MSISDN;
	struct dict_object *net_access_mode;
	struct dict_object *access_restriction_data;
	struct dict_object *AMBR;
	struct dict_object *max_req_bandwidth_UL;
	struct dict_object *max_req_bandwidth_DL;
	struct dict_object *APN_config_profile;
	struct dict_object *ctx_id;
	struct dict_object *additional_ctx_id;
	struct dict_object *all_APN_configs_included_ind;
	struct dict_object *APN_config;
	struct dict_object *PDN_type;
	struct dict_object *PDN_GW_alloc_type;
	struct dict_object *specific_APN_info;
	struct dict_object *non_IP_PDN_type_ind;
	struct dict_object *non_IP_data_delivery_mech;
	struct dict_object *SCEF_ID;
	struct dict_object *priority_Level;
	struct dict_object *location_area_id;
	struct dict_object *tracking_area_id;
	struct dict_object *subsc_periodic_RAU_TAU_tmr;

	/*PUR elements*/
	struct dict_object *PUR_flags;
	struct dict_object *reg_subs_zone_code;
};

/**
 * @brief Freediameter dictionary data storage
 */
struct fd_dict_data {
	/* S6A AVP data */
	struct dict_application_data app_s6a_data;
	struct dict_vendor_data vendor_data;

	/*Common s6a elements*/
	struct dict_avp_data res_code;
	struct dict_avp_data exp_res;
	struct dict_avp_data exp_res_code;
	struct dict_avp_data vendor_specific_app_id;
	struct dict_avp_data auth_app_id;
	struct dict_avp_data acct_app_id;
	struct dict_avp_data vendor_id;
	struct dict_avp_data sess_id;
	struct dict_avp_data auth_sess_state;
	struct dict_avp_data org_host;
	struct dict_avp_data org_realm;
	struct dict_avp_data dest_host;
	struct dict_avp_data dest_realm;
	struct dict_avp_data user_name;
	struct dict_avp_data visited_PLMN_id;
	struct dict_avp_data req_EUTRAN_auth_info;
	struct dict_avp_data no_of_req_vectors;
	struct dict_avp_data immediate_resp_pref;
	struct dict_avp_data resync_info;

	/*AIA data*/
	struct dict_avp_data auth_info;
	struct dict_avp_data E_UTRAN_vector;
	struct dict_avp_data RAND;
	struct dict_avp_data XRES;
	struct dict_avp_data AUTN;
	struct dict_avp_data KASME;

	/*ULR data*/
	struct dict_avp_data RAT_type;
	struct dict_avp_data ULR_flags;

	/*ULA data*/
	struct dict_avp_data ULA_flags;
	struct dict_avp_data subscription_data;
	struct dict_avp_data subscriber_status;
	struct dict_avp_data MSISDN;
	struct dict_avp_data net_access_mode;
	struct dict_avp_data access_restriction_data;
	struct dict_avp_data AMBR;
	struct dict_avp_data max_req_bandwidth_UL;
	struct dict_avp_data max_req_bandwidth_DL;
	struct dict_avp_data APN_config_profile;
	struct dict_avp_data ctx_id;
	struct dict_avp_data additional_ctx_id;
	struct dict_avp_data all_APN_configs_included_ind;
	struct dict_avp_data APN_config;
	struct dict_avp_data PDN_type;
	struct dict_avp_data PDN_GW_alloc_type;
	struct dict_avp_data specific_APN_info;
	struct dict_avp_data non_IP_PDN_type_ind;
	struct dict_avp_data non_IP_data_delivery_mech;
	struct dict_avp_data SCEF_ID;
	struct dict_avp_data priority_Level;
	struct dict_avp_data location_area_id;
	struct dict_avp_data tracking_area_id;
	struct dict_avp_data subsc_periodic_RAU_TAU_tmr;

	/*PUR flags*/
	struct dict_avp_data PUR_flags;
	struct dict_avp_data reg_subs_zone_code;
};

/**
 * @brief Initialize freediameter parser, callbacks, dictionary etc.
 * @params none
 * @return int as success/fail
 */
int
s6a_fd_init();

/**
 * @brief Initialize freediameter dictionary
 * @param none
 * @return int as success/fail
 */
int
s6a_fd_objs_init();

/**
 * @brief Initialize freediameter dictionary data objects
 * @param none
 * @return int as success/fail
 */
int
s6a_fd_data_init();

/**
 * @brief Initialize freediameter API callbacks for response handling
 * @param none
 * @return int as success/fail
 */
int
s6a_fd_cb_reg();

/**
 * @brief extract ue index from session id of freediameter
 * @param[in] sid - session id
 * @param[in] sidlen - Session Id length
 * @return UE index extracted out of session id
 */
int
get_ue_idx_from_fd_resp(unsigned char *sid, int sidlen);

/**
 * @brief Cression session id, append ue index to session id
 * @param[in, out] s6a_sess - session information
 * @param[in] ue_idx to append to session id
 * @return int as success/fail
 */
short
create_fd_sess_id(struct s6a_sess_info *s6a_sess, int ue_idx);

int
aia_resp_callback(struct msg **msg, struct avp *avp, struct session *sess,
		void *data, enum disp_action *act);

int
ula_resp_callback(struct msg **msg, struct avp *avp, struct session *sess,
		void *data, enum disp_action *act);

int
purge_resp_callback(struct msg **msg, struct avp *avp, struct session *sess,
		void *data, enum disp_action *act);

/**
 * @brief Dumo freediameter message on console
 * @param msg - Freediameter message structure
 * @return void
 */
void
dump_fd_msg(struct msg *msg);

/**
 * brief add AVl object to freediameter message
 * @param[in] avp value to add
 * @param[in] ditionary object for reference
 * @param[out] frediameter message where avp is added
 * @return int as success/fail
 */
int
add_fd_msg(union avp_value *val, struct dict_object * obj,
struct msg **msg_buf);

void
handle_perf_hss_aia(int ue_idx, struct hss_aia_msg *aia);

void
handle_perf_hss_ula(int ue_idx, struct hss_ula_msg *ula);

void
handle_perf_hss_purge_resp(int ue_idx);

short
parse_fd_result(struct avp *avp, struct fd_result *res);

#endif /* __S6A_FD_H__ */
