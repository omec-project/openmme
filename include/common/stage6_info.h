/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __STAGE6_INFO_H_
#define __STAGE6_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s11_structs.h"

struct csr_Q_msg {
	int ue_idx;
	int status;
	struct fteid s11_sgw_fteid;
	struct fteid s5s8_pgwc_fteid;
	struct fteid s1u_sgw_fteid;
	struct fteid s5s8_pgwu_fteid;
	struct PAA pdn_addr;
	unsigned char pco_length;
	unsigned char pco_options[MAX_PCO_OPTION_SIZE];
	
	//ebi info??
	//apn restriction?
};

struct init_ctx_req_Q_msg {
	int ue_idx;
	int enb_s1ap_ue_id;
	unsigned long exg_max_ul_bitrate;
	unsigned long exg_max_dl_bitrate;
	struct fteid gtp_teid;
	struct TAI tai;
	struct apn_name apn;
	struct apn_name selected_apn;
	struct PAA pdn_addr;
	unsigned char sec_key[32];
	unsigned char bearer_id;
	uint8_t int_key[NAS_INT_KEY_SIZE];
	uint16_t dl_seq_no;
	int enb_fd;
	unsigned char pti;
        unsigned char pco_length;
        unsigned char pco_options[MAX_PCO_OPTION_SIZE];
	unsigned int m_tmsi;
};


#define S11_CSRESP_STAGE6_BUF_SIZE sizeof(struct csr_Q_msg)
#define S1AP_ICSREQ_STAGE6_BUF_SIZE sizeof(struct init_ctx_req_Q_msg)

#endif /*STAGE6_INFO_H_*/
