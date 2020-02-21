/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "json_data.h"
#include "s1ap_config.h"
#include "err_codes.h"

s1ap_config g_s1ap_cfg;

void
init_parser(char *path)
{
	load_json(path);
}

int
parse_s1ap_conf()
{
	char  mcc_dig1;
	char  mcc_dig2;
	char  mcc_dig3;
	char  mnc_dig1;
	char  mnc_dig2;
	char  mnc_dig3;

	/*s1ap information*/
	g_s1ap_cfg.mme_name = get_string_scalar("mme.name");
	if(NULL == g_s1ap_cfg.mme_name) return -1;

	g_s1ap_cfg.s1ap_local_ip = get_ip_scalar("s1ap.s1ap_local_addr");
	if(-1 == g_s1ap_cfg.s1ap_local_ip) return -1;
	g_s1ap_cfg.sctp_port = get_int_scalar("s1ap.sctp_port");
	if(-1 == g_s1ap_cfg.sctp_port) return -1;

        /* TODO : should i get rid of this config (mme group id & mme code)  from s1-ap ? */
	g_s1ap_cfg.mme_group_id = get_int_scalar("mme.group_id");
	if(-1 == g_s1ap_cfg.mme_group_id) return -1;

	g_s1ap_cfg.mme_code = get_int_scalar("mme.code");
	if(-1 == g_s1ap_cfg.mme_code) return -1;

	mcc_dig1 = get_int_scalar("mme.mcc.dig1");
	if(E_PARSING_FAILED == mcc_dig1) return E_PARSING_FAILED;
	mcc_dig2 = get_int_scalar("mme.mcc.dig2");
	if(E_PARSING_FAILED == mcc_dig1) return E_PARSING_FAILED;
	mcc_dig3 = get_int_scalar("mme.mcc.dig3");
	if(E_PARSING_FAILED == mcc_dig1) return E_PARSING_FAILED;
	mnc_dig1 = get_int_scalar("mme.mnc.dig1");
	if(E_PARSING_FAILED == mcc_dig1) return E_PARSING_FAILED;
	mnc_dig2 = get_int_scalar("mme.mnc.dig2");
	if(E_PARSING_FAILED == mcc_dig1) return E_PARSING_FAILED;
	mnc_dig3 = get_int_scalar("mme.mnc.dig3");
	if(E_PARSING_FAILED == mcc_dig1) return E_PARSING_FAILED;

	/*Carefuly note the s1ap protocol mcc+mnc coding 
	 * if mcc = 123, mnc 456 then plmnId - 214365. 
	 * this is octed string encodingas per 36.413 Section - 9.2.3.8  
	*/
	g_s1ap_cfg.mme_plmn_id.idx[0] = mcc_dig2 << 4 | mcc_dig1;
	g_s1ap_cfg.mme_plmn_id.idx[1] = mnc_dig1 << 4 | mcc_dig3;
	g_s1ap_cfg.mme_plmn_id.idx[2] = mnc_dig3 << 4 | mnc_dig2;

	return SUCCESS;
}
