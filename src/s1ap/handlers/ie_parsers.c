/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "s1ap_ie.h"

void* 
ie_parse_global_enb_id(char *msg, int len)
{
	/*8 bytes
	1- ignore
	2,3,4 - plmn
	5,6,7,8 - mactoeNBID*/
	static struct ie_global_enb_id global_enb_id;
	
	memcpy(&(global_enb_id.plmn), msg, sizeof(int));
	memcpy(&(global_enb_id.macro_enb_id), msg+(sizeof(int)), MACRO_ENB_ID_SIZE);
	global_enb_id.plmn = ntohl(global_enb_id.plmn);
	//global_enb_id.macro_enb_id = ntohl(global_enb_id.macro_enb_id);
	log_msg(LOG_INFO, "plmn %x\n", global_enb_id.plmn);
	log_msg(LOG_INFO, "Macro enb id %x-%x-%x-%x\n", global_enb_id.macro_enb_id[0],
		global_enb_id.macro_enb_id[4],global_enb_id.macro_enb_id[8],global_enb_id.macro_enb_id[12]);
	
	return (void*)&global_enb_id;
}

void* 
ie_parse_enb_name(char *msg, int len)
{
	return NULL;
}

void* 
ie_parse_supported_TAs(char *msg, int len)
{
	return NULL;
}

void* 
ie_parse_pagins_DRX(char *msg, int len)
{
	return NULL;
}
