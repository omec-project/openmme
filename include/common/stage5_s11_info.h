/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __STAGE5_S11_INFO_H_
#define __STAGE5_S11_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"

struct CS_Q_msg {
	int           ue_idx;
	unsigned char IMSI[BINARY_IMSI_LEN];
	struct        apn_name selected_apn;
	struct        TAI tai;
	struct        CGI utran_cgi;
	unsigned char MSISDN[MSISDN_STR_LEN];
	unsigned int max_requested_bw_dl;
	unsigned int max_requested_bw_ul;
	unsigned char pco_length;
	unsigned char pco_options[MAX_PCO_OPTION_SIZE];
	unsigned int  paa_v4_addr;
};

#define S11_CSREQ_STAGE5_BUF_SIZE sizeof(struct CS_Q_msg)

#endif /*STAGE5_S11_INFO_H_*/
