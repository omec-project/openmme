/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
