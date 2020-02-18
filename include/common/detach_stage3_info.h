/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DETACH_STAGE3_INFO_H_
#define __DETACH_STAGE3_INFO_H_

struct ctx_release_complete_Q_msg {
	int ue_idx;
};

#define S1AP_CTXRELRESP_STAGE3_BUF_SIZE sizeof(struct ctx_release_complete_Q_msg)

#endif /*__DETACH_STAGE3_INFO_H_*/
