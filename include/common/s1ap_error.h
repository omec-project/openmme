/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __S1AP_ERROR_H_
#define __S1AP_ERROR_H_

/**
 When MME wants to reject to s1ap message due to unknown UE context 
 Refer - 36.413 . 9.1.8.1
*/


struct ue_reset_info {
	uint32_t enb_fd;
    uint16_t failure_layer;
    uint16_t cause;
    uint32_t reset_type; 
	uint32_t enb_s1ap_ue_id;
    uint32_t mme_s1ap_ue_id;
};

#define UE_RESET_INFO_BUF_SIZE sizeof(struct ue_reset_info)

#endif /*__S1AP_ERROR_H_*/
