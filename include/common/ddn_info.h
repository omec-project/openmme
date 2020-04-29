/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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
