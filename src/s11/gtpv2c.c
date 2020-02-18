/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <arpa/inet.h>
#include "gtpv2c.h"

void
set_gtpv2c_header(struct gtpv2c_header *gtpv2c_tx, uint8_t type, uint32_t teid,
		uint32_t seq)
{

	gtpv2c_tx->gtp.message_type = type;

	gtpv2c_tx->gtp.version = GTP_VERSION_GTPV2C;
	gtpv2c_tx->gtp.piggyback = 0;
	gtpv2c_tx->gtp.teidFlg = 1;
	gtpv2c_tx->gtp.spare = 0;

	gtpv2c_tx->teid.has_teid.teid = htonl(teid);
	gtpv2c_tx->teid.has_teid.seq = htonl(seq) >> 8;
	gtpv2c_tx->teid.has_teid.spare = 0;

	gtpv2c_tx->gtp.len = htons(8);

	return;
}
