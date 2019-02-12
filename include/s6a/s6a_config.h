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

#define HSS_HOST_NAME_LEN 256
#define HSS_REALM_LEN 256
#define SS_IPC_ENDPT_FILE_LEN 256

/**
 * @brief: Whether HSS to be contacted is freediameter based real HSS or the
 * dummy designed for performance testing
 */
enum  e_HSS_HOST_TYPE {
	HSS_PERF,
	HSS_FD,
};

/**
 * @brief What type of RPC mechanism to use for communication with dummy HSS
 */
enum  e_HSS_RPC {
	HSS_IPC,
	HSS_RPC,
};

/**
 * @brief HSS configuration read from hss json file
 */
typedef struct s6a_config {
	/**Defines whether freediameter based hss to be used or inbuilt hss to be
	 * used.
	 */
	enum  e_HSS_HOST_TYPE hss_type;

	/*Applicable in case of in built HSS. Defines which type of communication
	 * to be used. This is for future provision to support RPC
	 */
	enum  e_HSS_RPC hss_rpc;
	char  *hss_ipc_endpt;
	char  *hss_host_name;
	char  *realm;
} s6a_config;

/**
 * @brief Initialize json parser for givn file
 * @param path to the hss json file
 */
void
init_parser(char *path);

/**
 * @brief Parser hss json file and store parameters in the structure
 * @params none
 * @return int as success/fail
 */
int
parse_s6a_conf();

#endif /*__S1AP_CONFIG_H_*/
