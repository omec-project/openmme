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

#ifndef __STAGE3_INFO_H_
#define __STAGE3_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "stage1_s6a_msg.h"
#include "s1ap_ie.h"

struct authresp_Q_msg {
	int ue_idx;
	int status;
	struct XRES res;
	struct AUTS auts;
	//struct TAI tai;
	//TODO: need to pass enb ue id for validation?
};

struct sec_mode_Q_msg {
	int ue_idx;
	int enb_s1ap_ue_id;
	struct UE_net_capab ue_network;
	struct KASME key;
	uint8_t int_key[NAS_INT_KEY_SIZE];
	uint32_t dl_seq_no;
	int enb_fd;
};

#define S1AP_AUTHRESP_STAGE3_BUF_SIZE sizeof(struct authresp_Q_msg)
#define S1AP_SECREQ_STAGE3_BUF_SIZE sizeof(struct sec_mode_Q_msg)

#endif /*STAGE3_INFO_H_*/
