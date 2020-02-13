/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __S1AP_MSG_CODES_H_
#define __S1AP_MSG_CODES_H_

/****S1AP Procedude codes****/
#define S1AP_SETUP_REQUEST_CODE 17
#define S1AP_INITIAL_UE_MSG_CODE 12
/*uplink NAS Transport*/
#define S1AP_UL_NAS_TX_MSG_CODE 13
#define S1AP_INITIAL_CTX_RESP_CODE 9

#define S1AP_UE_CTX_RELEASE_CODE 23

/*S1AP Protocol IE types*/
#define S1AP_IE_GLOBAL_ENB_ID 59
#define S1AP_IE_ENB_NAME 60
#define S1AP_IE_SUPPORTED_TAS 64
#define S1AP_IE_DEF_PAGING_DRX 137
#define S1AP_IE_MMENAME 61
#define S1AP_IE_SERVED_GUMMEIES 105
#define S1AP_IE_REL_MME_CAPACITY 87

#define S1AP_IE_MME_UE_ID 0
#define S1AP_IE_ENB_UE_ID 8
#define S1AP_IE_NAS_PDU  26
#define S1AP_IE_TAI  67
#define S1AP_IE_UTRAN_CGI  100
#define S1AP_IE_RRC_EST_CAUSE  134
#define S1AP_ERAB_SETUP_CTX_SUR 51

/*NAS message type codes*/
#define NAS_ESM_RESP 0xda
#define NAS_AUTH_RESP 0x53
#define NAS_AUTH_FAILURE 0x5c
#define NAS_SEC_MODE_COMPLETE 0x5e
#define NAS_ATTACH_REQUEST 0x41
#define NAS_ATTACH_COMPLETE 0x43
#define NAS_DETACH_REQUEST 0x45

#endif /*__S1AP_MSG_CODES*/
