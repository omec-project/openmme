/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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
	int ue_m_tmsi;
	int s1ap_enb_ue_id;
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
