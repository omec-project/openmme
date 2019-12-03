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

#ifndef __S1AP_CONFIG_H_
#define __S1AP_CONFIG_H_

#include <stdbool.h>
#include "s1ap_structs.h"

#define MME_NAME_LEN 256

/**
 * s1ap interface configuration parameters
 */
typedef struct s1ap_config
{
	unsigned short sctp_port;
	char  *mme_name;
	unsigned int s1ap_local_ip;
	unsigned short mme_group_id;
	unsigned short max_enbs_cnt;
	unsigned char rel_cap;
	unsigned char mme_code;
	char  sctp_type; /* sctp, udp */
	struct PLMN mme_plmn_id;
	struct PLMN target_mme_plmn_id;
} s1ap_config;

void
init_parser(char *path);

int
parse_s1ap_conf();

#endif /*__S1AP_CONFIG_H_*/
