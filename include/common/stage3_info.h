/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __STAGE3_INFO_H_
#define __STAGE3_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "stage1_s6a_msg.h"
#include "s1ap_ie.h"

struct authresp_Q_msg {
	int ue_idx;
	int status;
	struct XRES res;
	struct AUTS auts;
	//struct TAI tai;
	//TODO: need to pass enb ue id for validation?
};

struct sec_mode_Q_msg {
	int ue_idx;
	int enb_s1ap_ue_id;
	struct UE_net_capab  ue_network;
	struct MS_net_capab  ms_net_capab;
	struct KASME key;
	uint8_t int_key[NAS_INT_KEY_SIZE];
	uint32_t dl_seq_no;
	int enb_fd;
};

#define S1AP_AUTHRESP_STAGE3_BUF_SIZE sizeof(struct authresp_Q_msg)
#define S1AP_SECREQ_STAGE3_BUF_SIZE sizeof(struct sec_mode_Q_msg)

#endif /*STAGE3_INFO_H_*/
