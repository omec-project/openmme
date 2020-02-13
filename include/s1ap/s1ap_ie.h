/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __S1AP_IE_H_
#define __S1AP_IE_H_

#include "stage1_info.h"
#include "s1ap_msg_codes.h"
#include "s1ap_structs.h"


#define S1AP_INITUE_IEs 5

/*** IE parsing functions ***/
typedef void * (ie_parser_function)(char *msg, int len);

//ie_parser_function ie_parser[32];//={};

void* ie_parse_global_enb_id(char *msg, int len);
void* ie_parse_enb_name(char *msg, int len);
void* ie_parse_supported_TAs(char *msg, int len);
void* ie_parse_pagins_DRX(char *msg, int len);

/*** IE parsing functions end***/

#endif /*S1AP_IE_H_*/
