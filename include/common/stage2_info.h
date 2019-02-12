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

#ifndef __STAGE2_INFO_H_
#define __STAGE2_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"

#define NAS_RAND_SIZE 16
#define NAS_AUTN_SIZE 16
struct authreq_info {
	int ue_idx; /*mme s1ap UE id*/
	int enb_s1ap_ue_id;
	unsigned char rand[NAS_RAND_SIZE];
	unsigned char autn[NAS_AUTN_SIZE];
	 //struct TAI tai;
	int enb_fd;
};

#define S1AP_AUTHREQ_STAGE2_BUF_SIZE sizeof(struct authreq_info)

#endif /*__STAGE2_INFO_H_*/

