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


#ifndef __UE_S11_H_
#define __UE_S11_H_

#include <stdint.h>
#include "log.h"
#include "s11_structs.h"

/*No of threads handling S11 GTPv2 messages coming in*/
#define S11_THREADPOOL_SIZE 5

#define S11_GTPV2C_BUF_LEN	4096

/*GTPv2c message types*/
#define S11_GTP_CREATE_SESSION_REQ	32
#define S11_GTP_CREATE_SESSION_RESP	33
#define S11_GTP_MODIFY_BEARER_RESP	35
#define S11_GTP_DELETE_SESSION_RESP	37

/*GTPv2c IE message types*/
#define S11_IE_CAUSE		2
#define S11_IE_FTEID_C		87
#define S11_IE_PAA		79
#define S11_IE_APN_RESTRICTION	127
#define S11_IE_BEARER_CTX	93
#define S11_IE_EPS_BEARER_ID	73

int
init_s11();

void
handle_s11_message(void *message);

int
init_s11();

void
handle_s11_message(void *message);

int
s11_transation(char * buf, unsigned int len);

void* create_session_handler(void *);
void* modify_bearer_handler(void *);

void* delete_session_handler(void *);

int s11_CS_resp_handler(char *message);
int s11_MB_resp_handler(char *message);
int s11_DS_resp_handler(char *message);

void
bswap8_array(uint8_t *src, uint8_t *dest, uint32_t len);

int parse_gtpv2c_IEs(char *msg, int len, struct s11_proto_IE *proto_ies);

#endif /*S11_H*/
