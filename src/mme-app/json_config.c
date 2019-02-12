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

#include "json_data.h"
#include "mme_app.h"
#include "err_codes.h"

mme_config g_mme_cfg;

/**
 * @brief Initialize json parser
 * @param None
 * @return void
 */
void
init_parser(char *path)
{
	load_json(path);
}

/**
 * @brief parser mme-app input json file
 * @param None
 * @return int as SUCCESS or FAIL
 */
int
parse_mme_conf()
{
	/*mme own information*/
	g_mme_cfg.mme_name = get_string_scalar("mme.name");
	if(NULL == g_mme_cfg.mme_name) return E_PARSING_FAILED;

	g_mme_cfg.mme_ip_addr = get_ip_scalar("mme.ip_addr");
	if(E_PARSING_FAILED == g_mme_cfg.mme_ip_addr) return E_PARSING_FAILED;

	g_mme_cfg.mcc_dig1 = get_int_scalar("mme.mcc.dig1");
	if(E_PARSING_FAILED == g_mme_cfg.mcc_dig1) return E_PARSING_FAILED;
	g_mme_cfg.mcc_dig2 = get_int_scalar("mme.mcc.dig2");
	if(E_PARSING_FAILED == g_mme_cfg.mcc_dig1) return E_PARSING_FAILED;
	g_mme_cfg.mcc_dig3 = get_int_scalar("mme.mcc.dig3");
	if(E_PARSING_FAILED == g_mme_cfg.mcc_dig1) return E_PARSING_FAILED;
	g_mme_cfg.mcc_dig1 = get_int_scalar("mme.mnc.dig1");
	if(E_PARSING_FAILED == g_mme_cfg.mcc_dig1) return E_PARSING_FAILED;
	g_mme_cfg.mnc_dig2 = get_int_scalar("mme.mnc.dig2");
	if(E_PARSING_FAILED == g_mme_cfg.mcc_dig1) return E_PARSING_FAILED;
	g_mme_cfg.mnc_dig3 = get_int_scalar("mme.mnc.dig3");
	if(E_PARSING_FAILED == g_mme_cfg.mcc_dig1) return E_PARSING_FAILED;

	return SUCCESS;
}
