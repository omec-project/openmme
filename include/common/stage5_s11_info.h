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

#ifndef __STAGE5_S11_INFO_H_
#define __STAGE5_S11_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"

struct CS_Q_msg {
	int           ue_idx;
	unsigned char IMSI[BINARY_IMSI_LEN];
	struct        apn_name apn;
	struct        TAI tai;
	struct        CGI utran_cgi;
	unsigned char MSISDN[MSISDN_STR_LEN];
	unsigned int max_requested_bw_dl;
	unsigned int max_requested_bw_ul;
};

#define S11_CSREQ_STAGE5_BUF_SIZE sizeof(struct CS_Q_msg)

#endif /*STAGE5_S11_INFO_H_*/
