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

#ifndef __STAGE8_INFO_H_
#define __STAGE8_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s11_structs.h"

struct MB_resp_Q_msg {
	int 		ue_idx;
	struct fteid 	s1u_sgw_fteid;
};

struct attach_complete_Q_msg {
	int		ue_idx;
	unsigned short	status;
};

#define S11_MBRESP_STAGE8_BUF_SIZE sizeof(struct MB_resp_Q_msg)
#define S1AP_ATT_COMP_STAGE8_BUF_SIZE sizeof(struct attach_complete_Q_msg)

#endif /*STAGE8_INFO_H_*/
