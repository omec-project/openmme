/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
*
*/

#ifndef __MONITOR_MSG_H_
#define __MONITOR_MSG_H_

#include "ue_table.h"
#include "s1ap_structs.h"
#include "s11_structs.h"

/*Monitoring msg header*/
enum e_BUF_HDR {
	MONITOR_IMSI_REQ,
	MONITOR_IMSI_RSP,
};

#define IMSI_STR_LEN 16

/*Monitor IMSI Request*/
struct monitor_imsi_req {
    uint32_t  req_type;
	char imsi[IMSI_STR_LEN];
};

/*Monitor IMSI Response*/
struct monitor_imsi_rsp {
    uint32_t             result;
    uint32_t             ue_state;
    uint32_t             paa;
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

/*Monitor IMSI List Response*/
struct monitor_imsi_list_rsp {
    uint32_t             no_of_ue;
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

#define MONITOR_REQ_MSG_SIZE  sizeof(struct monitor_req_msg)
#define MONITOR_RESP_MSG_SIZE sizeof(struct monitor_resp_msg)

#endif /*__MONITOR_MSG_H_*/

