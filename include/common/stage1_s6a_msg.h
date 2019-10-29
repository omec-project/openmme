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
/*Information to send from mme app to s6a for AIR and ULR*/
#ifndef __STAGE1_S6A_MSG_H_
#define __STAGE1_S6A_MSG_H_

#include "sec.h"
#include "s1ap_structs.h"


/*Information needed for AIR and ULR*/
/*From mme-app --> to--> s6a*/
struct s6a_Q_msg {
	unsigned char imsi[BINARY_IMSI_LEN];
	struct TAI tai;
    struct AUTS auts;
	//struct PLMN visited_plmn;
	/*e-utran auth info??*/
	unsigned int ue_idx;
};

typedef struct E_UTRAN_sec_vector {
	struct RAND   rand;
	struct XRES   xres;
	struct AUTN   autn;
	struct KASME  kasme;
} E_UTRAN_sec_vector;

/*AIA response from s6a -->to--> mme-app*/
struct aia_Q_msg {
	unsigned int ue_idx;
	int res;
	E_UTRAN_sec_vector sec;
};

/*ULA response from s6a -->to--> mme-app*/
struct ula_Q_msg {
	unsigned int ue_idx;
	unsigned int access_restriction_data;
	int subscription_status;
	int net_access_mode;
	unsigned int RAU_TAU_timer;
	int res;
	unsigned int max_requested_bw_dl;
	unsigned int max_requested_bw_ul;
	unsigned int apn_config_profile_ctx_id;
	int all_APN_cfg_included_ind;
	char MSISDN[MSISDN_STR_LEN];
};

#define S6A_REQ_Q_MSG_SIZE sizeof(struct s6a_Q_msg)
#define S6A_AIA_STAGE2_BUF_SIZE sizeof(struct aia_Q_msg)
#define S6A_ULA_STAGE2_BUF_SIZE sizeof(struct ula_Q_msg)

#endif /*__STAGE6_S6A_MSG_H_*/

