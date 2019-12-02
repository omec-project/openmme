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

#ifndef __S11_COMMON_PROC_INFO_H_
#define __S11_COMMON_PROC_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"
#include "s11_structs.h"

enum s1ap_cn_domain
{
    CN_DOMAIN_PS,
    CN_DOMAIN_CS,
    CN_DOMAIN_NONE
};

struct s1ap_common_req_Q_msg {
    int             IE_type; 
	int ue_idx;
	int enb_fd;
	int enb_s1ap_ue_id;
	int mme_s1ap_ue_id;
    enum s1ap_cn_domain cn_domain;
    unsigned char imsi[BINARY_IMSI_LEN];
	struct TAI      tai;//TODO: will be list of 16 TAI's for UE.
	s1apCause_t cause;
};

struct s11_req_Q_msg {
    int         IE_type; 
	struct fteid s11_sgw_c_fteid;
};

struct s11_resp_Q_msg {
    int         IE_type; 
	int 		ue_idx;
};

enum s1ap_common_req_type
{
    S1AP_CTX_REL_REQ,
    S1AP_CTX_REL_CMD,
    S1AP_PAGING_REQ,
    S1AP_REQ_UNKNOWN
};

enum s11_common_req_type
{
    S11_RABR_REQ,
    S11_REQ_UNKNOWN
};

enum s11_common_resp_type
{
    S11_RABR_RESP,
    S11_RESP_UNKNOWN
};

#define S1AP_COMMON_REQ_BUF_SIZE sizeof(struct s1ap_common_req_Q_msg)

#define S11_COMM_REQ_STAGE_BUF_SIZE sizeof(struct s11_req_Q_msg)
#define S11_COMM_RES_STAGE_BUF_SIZE sizeof(struct s11_resp_Q_msg)

#endif /*__S11_COMMON_PROC_INFO_H_*/
