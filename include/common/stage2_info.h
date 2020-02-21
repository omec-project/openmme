/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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

