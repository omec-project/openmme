/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __PAGING_INFO_H_
#define __PAGING_INFO_H_

struct paging_Q_msg {
	int ue_idx;
	unsigned char IMSI[BINARY_IMSI_LEN];
	struct TAI tai;
};

#define S1AP_PAGING_INFO_BUF_SIZE sizeof(struct paging_Q_msg)

#endif /*_PAGING_INFO_H_*/
