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

#ifndef __MONITOR_MSG_H_
#define __MONITOR_MSG_H_

#include "ue_table.h"
#include "s1ap_structs.h"
#include "s11_structs.h"

/*Information needed for AIR*/
enum e_BUF_HDR {
	MONITOR_IMSI_REQ,
	MONITOR_IMSI_RSP,
};

#define IMSI_STR_LEN 16
/*AIR  - request. Struct is same for ULR*/
struct monitor_imsi_req {
    int  req_type;
	char imsi[IMSI_STR_LEN];
};

/*AIA  - response*/
struct monitor_imsi_rsp {
        int             result;
	unsigned char   imsi[IMSI_STR_LEN];
	unsigned char   bearer_id;
	struct TAI      tai;//TODO: will be list of 16 TAI's for UE.
	struct AMBR     ambr; /*24.301 : 9.9.4.2*/
/*	struct fteid    s11_sgw_c_fteid;
	struct fteid    s5s8_pgw_c_fteid;
	struct fteid    s1u_sgw_u_fteid;
	struct fteid    s5s8_pgw_u_fteid;
	struct fteid    s1u_enb_u_fteid;*/
};

struct monitor_imsi_list_rsp {
    int             no_of_ue;
	unsigned char   **imsi_list;
};

struct monitor_req_msg {
	enum e_BUF_HDR hdr;
	union req_data {
		struct monitor_imsi_req mir;
	}data;
};

struct monitor_resp_msg {
	enum e_BUF_HDR hdr;
	int result;
	union resp_data {
		struct monitor_imsi_rsp mia;
	}data;
};

#define MONITOR_RCV_BUF_SIZE  128
#define MONITOR_REQ_MSG_SIZE  sizeof(struct monitor_req_msg)
#define MONITOR_RESP_MSG_SIZE sizeof(struct monitor_resp_msg)

#endif /*__MONITOR_MSG_H_*/

