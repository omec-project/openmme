/*
 * Copyright 2019-present Open Networking Foundation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __S1AP_EMM_MESSAGE_H_ 
#define __S1AP_EMM_MESSAGE_H_

/**
 When MME wants to send EMM information Request to UE
 Refer - 24.301 refer 8.2.13 
*/
struct ue_emm_info {
	uint32_t enb_fd;
	uint32_t enb_s1ap_ue_id;
	uint32_t mme_s1ap_ue_id;
	char     short_network_name[16];
	char     full_network_name[128];
	uint8_t int_key[NAS_INT_KEY_SIZE];
	unsigned short dl_seq_no;
};

#define UE_EMM_INFO_BUF_SIZE sizeof(struct ue_emm_info)

#endif /*__S1AP_EMM_MESSAGE_H_*/
