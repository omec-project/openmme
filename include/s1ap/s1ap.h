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

#ifndef __S1AP_H_
#define __S1AP_H_

#include <stdbool.h>

#include "s1ap_structs.h"
#include "log.h"
#include "s1ap_ie.h"
#include "InitiatingMessage.h"
#include "SuccessfulOutcome.h"
#include "UnsuccessfulOutcome.h"

int
s1_init_ctx_resp_handler(SuccessfulOutcome_t *msg);

int
parse_IEs(char *msg, struct proto_IE *proto_ies, unsigned short proc_code);

int convertToInitUeProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies);
int convertUplinkNasToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies);
int convertInitCtxRspToProtoIe(SuccessfulOutcome_t *msg, struct proto_IE* proto_ies);
int
s1_setup_handler(InitiatingMessage_t *msg, int enb_fd);

int
s1_init_ue_handler(struct proto_IE *s1_init_ies, int enb_fd);

void
handle_s1ap_message(void *message);

int
s1ap_mme_decode_initiating (InitiatingMessage_t *initiating_p, int enb_fd);

int
s1ap_mme_decode_successfull_outcome (SuccessfulOutcome_t *initiating_p);

int
s1ap_mme_decode_unsuccessfull_outcome (UnsuccessfulOutcome_t *initiating_p);

int
init_s1ap();

void
read_config();

void*
IAM_handler(void *data);

int s1_esm_resp_handler(struct proto_IE *s1_esm_resp_ies);

int s1_secmode_resp_handler(struct proto_IE *s1_sec_resp_ies);

int s1_auth_resp_handler(struct proto_IE *s1_auth_resp_ies);
int s1_auth_fail_handler(struct proto_IE *s1_auth_resp_ies);

int s1_attach_complete_handler(struct proto_IE *s1_esm_resp_ies);

int
detach_stage1_handler(struct proto_IE *detach_ies, bool retransmit);

int
s1_ctx_release_resp_handler(InitiatingMessage_t *msg);

int
copyU16(unsigned char *buffer, uint32_t val);

int
send_sctp_msg(int connSock, unsigned char *buffer, size_t len, uint16_t stream_no);

void
buffer_copy(struct Buffer *buffer, void *value, size_t size);

/**
 * @brief Decode int value from the byte array received in the s1ap incoming
 * packet.
 * @param[in] bytes - Array of bytes in packet
 * @param[in] len - Length of the bytes array from which to extract the int
 * @return Integer value extracted out of bytes array. 0 if failed.
 */
int
decode_int_val(unsigned char *bytes, short len);

char*
msg_to_hex_str(const char *msg, int len, char **buffer);

unsigned short
get_length(char **msg);

#endif /*__S1AP_H_*/
