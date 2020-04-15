/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __STAGE5_INFO_H_
#define __STAGE5_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"

struct esm_resp_Q_msg {
	int ue_idx;
	int status;
	struct apn_name apn;
};

#define S1AP_ESMRESP_STAGE5_BUF_SIZE sizeof(struct esm_resp_Q_msg)

#endif /*STAGE5_INFO_H_*/
