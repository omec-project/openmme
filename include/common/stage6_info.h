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

#ifndef __STAGE6_INFO_H_
#define __STAGE6_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s11_structs.h"

struct csr_Q_msg {
	int ue_idx;
	int status;
	struct fteid s11_sgw_fteid;
	struct fteid s5s8_pgwc_fteid;
	struct fteid s1u_sgw_fteid;
	struct fteid s5s8_pgwu_fteid;
	struct PAA pdn_addr;
	//ebi info??
	//apn restriction?
	//paa?
};

struct init_ctx_req_Q_msg {
	int ue_idx;
	int enb_s1ap_ue_id;
	unsigned long exg_max_ul_bitrate;
	unsigned long exg_max_dl_bitrate;
	struct fteid gtp_teid;
	struct TAI tai;
	struct apn_name apn;
	struct PAA pdn_addr;
	unsigned char sec_key[32];
	unsigned char bearer_id;
	uint8_t int_key[NAS_INT_KEY_SIZE];
	uint16_t dl_seq_no;
	int enb_fd;
	unsigned char pti;
};


#define S11_CSRESP_STAGE6_BUF_SIZE sizeof(struct csr_Q_msg)
#define S1AP_ICSREQ_STAGE6_BUF_SIZE sizeof(struct init_ctx_req_Q_msg)

#endif /*STAGE6_INFO_H_*/
