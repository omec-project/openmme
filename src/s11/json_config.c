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
#include "s11_config.h"
#include "err_codes.h"

s11_config g_s11_cfg;

void
init_parser(char *path)
{
	load_json(path);
}

int
parse_s11_conf()
{
	/*s1ap information*/
	g_s11_cfg.local_egtp_ip = get_ip_scalar("s11.egtp_local_addr");
	if(-1 == g_s11_cfg.local_egtp_ip) return -1;
	g_s11_cfg.egtp_def_port = get_int_scalar("s11.egtp_default_port");
	if(-1 == g_s11_cfg.egtp_def_port) return -1;

	g_s11_cfg.sgw_ip = get_ip_scalar("s11.sgw_addr");
	if(-1 == g_s11_cfg.sgw_ip) return -1;
	g_s11_cfg.pgw_ip = get_ip_scalar("s11.pgw_addr");
	if(-1 == g_s11_cfg.pgw_ip) return -1;

	return SUCCESS;
}
