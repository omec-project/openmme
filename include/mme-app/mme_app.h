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

#ifndef __MME_APP_H_
#define __MME_APP_H_

#include <stdbool.h>

#include "s1ap_structs.h"
#include "log.h"

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

//for testing, delete it
void
send_dummy_mbr();
void stat_init();

/* Register for config change trigger */
void register_config_updates(void);
void mme_parse_config(mme_config *);

#endif /*__MME_APP_H_*/
