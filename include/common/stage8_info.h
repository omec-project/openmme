/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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
