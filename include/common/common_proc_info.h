/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __S11_COMMON_PROC_INFO_H_
#define __S11_COMMON_PROC_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"
#include "s11_structs.h"

enum s1ap_cn_domain
{
    CN_DOMAIN_PS,
    CN_DOMAIN_CS,
    CN_DOMAIN_NONE
};

struct s1ap_common_req_Q_msg {
    int             IE_type;
    e_emmCause      emm_cause;
	int ue_idx;
	int enb_fd;
	unsigned short mme_group_id;
	unsigned char rel_cap;
	unsigned char mme_code;
	char  mme_name[MME_NAME_STR_LEN];
	struct PLMN mme_plmn_id;
	int enb_s1ap_ue_id;
	int mme_s1ap_ue_id;
    enum s1ap_cn_domain cn_domain;
    unsigned char imsi[BINARY_IMSI_LEN];
	struct TAI      tai;//TODO: will be list of 16 TAI's for UE.
	s1apCause_t cause;

	unsigned long ueag_max_ul_bitrate;
	unsigned long ueag_max_dl_bitrate;
	struct fteid gtp_teid;
	unsigned char sec_key[32];
	unsigned char bearer_id;
};

struct s11_req_Q_msg {
    int         IE_type; 
	struct fteid s11_sgw_c_fteid;
};

struct s11_resp_Q_msg {
    int         IE_type; 
	int 		ue_idx;
};

enum s1ap_common_req_type
{
    S1AP_CTX_REL_REQ,
    S1AP_CTX_REL_CMD,
    S1AP_INIT_CTXT_SETUP_REQ,
    S1AP_PAGING_REQ,
    S1AP_ATTACH_REJ,
    S1AP_SERVICE_REJ,
    S1AP_SETUP_FAILURE,
    S1AP_SETUP_RESPONSE,
    S1AP_REQ_UNKNOWN
};

enum s1ap_common_rej_type
{
    S1AP_ATTACH_REJECT,
    S1AP_SERVICE_REJECT,
    S1AP_REJ_UNKNOWN
};

enum s11_common_req_type
{
    S11_RABR_REQ,
    S11_REQ_UNKNOWN
};

enum s11_common_resp_type
{
    S11_RABR_RESP,
    S11_RESP_UNKNOWN
};

#define S1AP_COMMON_REQ_BUF_SIZE sizeof(struct s1ap_common_req_Q_msg)

#define S11_COMM_REQ_STAGE_BUF_SIZE sizeof(struct s11_req_Q_msg)
#define S11_COMM_RES_STAGE_BUF_SIZE sizeof(struct s11_resp_Q_msg)

#endif /*__S11_COMMON_PROC_INFO_H_*/
