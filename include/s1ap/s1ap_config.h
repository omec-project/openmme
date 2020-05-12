/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __S1AP_CONFIG_H_
#define __S1AP_CONFIG_H_

#include <stdbool.h>
#include "s1ap_structs.h"
#include "defines.h"

#define MME_NAME_LEN 256

/**
 * s1ap interface configuration parameters
 */
typedef struct s1ap_config
{
	unsigned short sctp_port;
	char  *mme_name;
	char  *logging;
	unsigned int s1ap_local_ip;
	unsigned short mme_group_id;
	unsigned short max_enbs_cnt;
	unsigned char rel_cap;
	unsigned char mme_code;
	char  sctp_type; /* sctp, udp */
	struct PLMN mme_plmn_id;
	uint16_t num_plmns;
	struct PLMN plmns[MAX_PLMN];
	struct PLMN_C plmn_mcc_mnc[MAX_PLMN];
} s1ap_config_t;

void
init_parser(char *path);

int
parse_s1ap_conf(s1ap_config_t *config);

void 
s1ap_parse_config(s1ap_config_t *config);

void 
set_s1ap_config(s1ap_config_t *cfg);

void 
switch_config(s1ap_config_t *new_config);

s1ap_config_t *get_s1ap_config();

void register_config_updates(void);

#endif /*__S1AP_CONFIG_H_*/
