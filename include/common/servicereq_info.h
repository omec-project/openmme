/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SERVICEREQ_INFO_H_
#define __SERVICEREQ_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"



struct service_req_Q_msg {
	int ue_idx;
	int s1ap_enb_ue_id;
	int enb_fd;
	unsigned int ksi;
	unsigned int seq_no;
	unsigned short mac;
	struct TAI tai;
	struct CGI utran_cgi;
	struct STMSI s_tmsi;
};

#define S1AP_SERVICEREQ_BUF_SIZE sizeof(struct service_req_Q_msg)


#endif /*__SERVICEREQ_INFO_H_*/
