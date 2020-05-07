/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __GTPV2C_H_
#define __GTPV2C_H_

#include <stdint.h>

#include "s11_structs.h"

#define MAX_GTPV2C_UDP_LEN                                   4096

#define GTP_VERSION_GTPV2C                                   2

/* GTP Message Type */
#define GTP_CREATE_SESSION_REQ                               32
#define GTP_CREATE_SESSION_RSP                               33
#define GTP_MODIFY_BEARER_REQ                                34
#define GTP_MODIFY_BEARER_RSP                                35
#define GTP_DELETE_SESSION_REQ                               36
#define GTP_DELETE_SESSION_RSP                               37
#define GTP_RABR_REQ                                        170
#define GTP_RABR_RSP                                        171
#define GTP_DOWNLINK_DATA_NOTIFICATION_ACK 					177
#define GTP_DOWNLINK_DATA_NOTIFICATION_FAILURE_IND 			178


enum gtpv2c_interfaces {
	GTPV2C_IFTYPE_S1U_ENODEB_GTPU = 0,
};


void
set_gtpv2c_header(struct gtpv2c_header *gtpv2c_tx, uint8_t type,
		uint32_t teid, uint32_t seq);

#endif /* __GTPV2C_H_ */
