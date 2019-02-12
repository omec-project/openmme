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

#ifndef __S6A_H_
#define __S6A_H_

#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdproto.h>
#include <freeDiameter/libfdcore.h>

#include "log.h"
#include "hss_message.h"

#define S6A_FD_CONF "conf/s6a_fd.conf"
#define HSS_RESP_THREADPOOL_SIZE 10
#define STR_IMSI_LEN 16
#define SESS_ID_LEN 128

/**
 * brief: Structure to store s6a freediameter session information
 */
struct s6a_sess_info {
	unsigned char imsi[8];
	char sess_id[SESS_ID_LEN];
	int sess_id_len;
};

/**
 * @brief Handle HSS reponse message
 * @param[in] message buffer
 * @return void
 */
void
hss_resp_handler(void *message);

/**
 * @brief Handler thread for AIR/ULR request coming from mme-app
 * This function sends both AIR and ULR
 * @param[in] data- message buffer
 * @return void*
 */
void*
AIR_handler(void *data);

/**
 * @brief Handler thread for detach request coming from mme-app
 * @param[in] data- message buffer
 * @return void *
 */
void*
detach_handler(void *data);

/*Handler for AIA coming from built in perf HS*/
void
handle_perf_hss_aia(int ue_idx, struct hss_aia_msg *aia);

/*Handler for ULA coming from built in perf HS*/
void
handle_perf_hss_ula(int ue_idx, struct hss_ula_msg *ula);

/*Handler for AIA coming from built in perf HS*/
void
handle_perf_hss_purge_resp(int ue_idx);

/**
 * @brief convert binary imsi to string imsi
 * Binary imsi is stored in 8 bytes, each nibble representing each imsi char.
 * char imsi stroes each char in 1 byte.
 * @param[in] b_imsi : Binary imsi
 * @param[out] s_imsi : Converted string imsi
 * @return void
 */
void
imsi_bin_to_str(unsigned char *b_imsi, char *s_imsi);

#endif /*S6A*/
