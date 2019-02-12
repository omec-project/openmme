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
