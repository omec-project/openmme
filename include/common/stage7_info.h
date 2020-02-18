/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __STAGE7_INFO_H_
#define __STAGE7_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s11_structs.h"

struct initctx_resp_Q_msg{
	int 		ue_idx;
	unsigned short 	eRAB_id;
	unsigned int 	transp_layer_addr;
	unsigned int 	gtp_teid;
};

#define S11_MB_INDICATION_FLAG_SIZE 3
struct MB_Q_msg {
	int 	ue_idx;
	unsigned short indication[S11_MB_INDICATION_FLAG_SIZE];/*Provision*/
	unsigned char bearer_id;
	struct fteid s11_sgw_c_fteid;
	struct fteid s1u_enb_fteid;
};

#define S1AP_ICSRESP_STAGE7_BUF_SIZE sizeof(struct initctx_resp_Q_msg)
#define S11_MBREQ_STAGE7_BUF_SIZE sizeof(struct MB_Q_msg)

#endif /*STAGE6_INFO_H_*/
