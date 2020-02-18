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

#ifndef __DDN_INFO_H_
#define __DDN_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s11_structs.h"

struct ddn_Q_msg {
	int ue_idx;
	uint8_t	cause;
	unsigned char eps_bearer_id;
	uint8_t pci;
	uint8_t pl;
	uint8_t pvi;
};

struct ddn_ack_Q_msg {
	int ue_idx;
	uint8_t	cause;
};

struct ddn_fail_Q_msg {
	int ue_idx;
        uint8_t cause;
};


#define S11_DDN_BUF_SIZE sizeof(struct ddn_Q_msg)
#define S11_DDN_ACK_BUF_SIZE sizeof(struct ddn_ack_Q_msg)
#define S11_DDN_FAIL_BUF_SIZE sizeof(struct ddn_fail_Q_msg)

#endif /*__DDN_INFO_H_*/
