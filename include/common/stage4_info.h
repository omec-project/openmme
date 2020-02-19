/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __STAGE4_INFO_H_
#define __STAGE4_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "stage1_s6a_msg.h"
#include "s1ap_ie.h"

struct secmode_resp_Q_msg {
	int ue_idx;
	int status;
};

struct esm_req_Q_msg {
	int ue_idx;
	int enb_s1ap_ue_id;
	uint8_t int_key[NAS_INT_KEY_SIZE];
	unsigned short dl_seq_no;
	int enb_fd;
	unsigned char pti;
};

#define S1AP_SECRESP_STAGE4_BUF_SIZE sizeof(struct secmode_resp_Q_msg)
#define S1AP_ESMREQ_STAGE4_BUF_SIZE sizeof(struct esm_req_Q_msg)

#endif /*STAGE4_INFO_H_*/
