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
#include <string.h>

#include "json_data.h"
#include "s6a_config.h"
#include "err_codes.h"

/**Globals and externs**/
s6a_config g_s6a_cfg;
/**Globals and externs**/

/**
 * @brief Initialize json parser and file reading
 * @param  Path to json file
 * @return void
 */
void
init_parser(char *path)
{
	load_json(path);
}

/**
 * @brief Read s6a configuration parameters from input json
 * @param  None
 * @return int - Success or fail
 */
int
parse_s6a_conf()
{
	/*Read s11 config information*/
	char *tmp = get_string_scalar("s6a.hss_type");
	if(NULL == tmp) return E_FAIL;
	if(!strcmp(tmp, "freediameter")) g_s6a_cfg.hss_type = HSS_FD;
	else g_s6a_cfg.hss_type = HSS_PERF;
	free(tmp);

	g_s6a_cfg.hss_host_name = get_string_scalar("s6a.host_name");
	if( NULL == g_s6a_cfg.hss_host_name) return E_FAIL;

	g_s6a_cfg.realm = get_string_scalar("s6a.realm");
	if(NULL == g_s6a_cfg.realm) return E_FAIL;

	return SUCCESS;
}
