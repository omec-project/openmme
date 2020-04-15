/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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
