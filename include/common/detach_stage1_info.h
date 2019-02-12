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

#ifndef __DETACH_STAGE1_INFO_H_
#define __DETACH_STAGE1_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"
#include "s11_structs.h"

#define S11_DS_INDICATION_FLAG_SIZE 3

struct detach_req_Q_msg {
	int ue_idx;
};

struct DS_Q_msg {
	unsigned char indication[S11_DS_INDICATION_FLAG_SIZE];/*Provision*/
	unsigned char bearer_id;
	struct fteid s11_sgw_c_fteid;
};

struct s6a_purge_Q_msg {
	int ue_idx;
	unsigned char IMSI[BINARY_IMSI_LEN];
};

#define S1AP_DETACHREQ_STAGE1_BUF_SIZE sizeof(struct detach_req_Q_msg)

#define S11_DTCHREQ_STAGE1_BUF_SIZE sizeof(struct DS_Q_msg)
#define S6A_PURGEREQ_STAGE1_BUF_SIZE sizeof(struct s6a_purge_Q_msg)

#endif /*__DETACH_STAGE1_INFO_H_*/
