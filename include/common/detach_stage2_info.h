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

#ifndef __DETACH_STAGE2_INFO_H_
#define __DETACH_STAGE2_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"
#include "s11_structs.h"

struct DS_resp_Q_msg {
	int 		ue_idx;
};

struct detach_accept_Q_msg {
	int ue_idx;
	int enb_s1ap_ue_id;
	uint8_t int_key[NAS_INT_KEY_SIZE];
	uint16_t dl_seq_no;
	int enb_fd;
};

struct purge_resp_Q_msg {
	int ue_idx;
	int status;
};

#define S1AP_DTCHRES_STAGE2_BUF_SIZE sizeof(struct DS_resp_Q_msg)

#define S1AP_DTCHACCEPT_STAGE2_BUF_SIZE sizeof(struct detach_accept_Q_msg)

#define S1AP_PURGERESP_STAGE2_BUF_SIZE sizeof(struct purge_resp_Q_msg)

#endif /*__DETACH_STAGE2_INFO_H_*/
