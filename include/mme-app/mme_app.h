/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __MME_APP_H_
#define __MME_APP_H_

#include <stdbool.h>

#include "s1ap_structs.h"
#include "log.h"
#include "s1ap_emm_message.h"
#include "s1ap_error.h"
#include "ue_table.h"

/**
 * MME main application configuration parameters structures.
 * All fields in this will be filled in from input json file.
 */
typedef struct mme_config
{
	unsigned int mme_ip_addr;
	unsigned short mme_sctp_port;
	unsigned int s11_sgw_ip;
	unsigned int s11_pgw_ip;
	unsigned short mme_egtp_def_port;
	char  *mme_egtp_def_hostname;
	char  *mme_name;
    char  *logging;

	char  mcc_dig1;
	char  mcc_dig2;
	char  mcc_dig3;
	char  mnc_dig1;
	char  mnc_dig2;
	char  mnc_dig3;
	struct PLMN plmn_id;

	unsigned int mme_s1ap_ip;
	unsigned int mme_egtp_ip;
	unsigned short mme_group_id;
	unsigned char mme_code;
} mme_config;


/*Functions declarations*/
void
init_parser(char *path);

int
parse_mme_conf(mme_config *config);

int
start_mme();

void
check_mme_hdlr_status();

void* stage1_handler(void *);
void  handle_monitor_processing(void *);
void* stage2_handler(void *);
void* stage3_handler(void *);
void* stage4_handler(void *);
void* stage5_handler(void *);
void* stage6_handler(void *);
void* stage7_handler(void *);
void* stage8_handler(void *);
void* detach_stage1_mme_handler(void *);
void* detach_stage2_handler(void *);
void* detach_stage3_handler(void *);
void  guti_attach_post_to_next(int index);
void *identity_rsp_handler(void *);
int post_to_hss_stage(int idx);
int post_ctx_rel_and_clr_uectx(int idx);
int post_svc_reject(int idx);
int send_init_ctx_setup_req(int idx);
void* ddn_handler(void *);
void* service_request_handler(void *);
void* s1ap_req_common_mme_handler(void *);
void* s11_rsp_common_mme_handler(void *);
void* DDN_handler(void *);
void *tau_request_handler(void *);

//for testing, delete it
void
send_dummy_mbr();
void stat_init();

/* Register for config change trigger */
void register_config_updates(void);
void mme_parse_config(mme_config *);

int send_emm_info_s1ap_channel_req(struct ue_emm_info *req);

int send_reset_s1ap_channel_req(struct ue_reset_info *req);

int send_reset (struct UE_info *ue_entry, uint32_t cause, uint32_t reset_type);

#endif /*__MME_APP_H_*/
