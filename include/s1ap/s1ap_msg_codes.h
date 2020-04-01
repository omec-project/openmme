/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __S1AP_MSG_CODES_H_
#define __S1AP_MSG_CODES_H_

/* Section 9.3.6. Spec 36.413 */
/****S1AP Procedude codes****/
#define S1AP_SETUP_REQUEST_CODE 17
#define S1AP_INITIAL_UE_MSG_CODE 12
#define S1AP_HANDOVER_REQUIRED_CODE 0
#define S1AP_HANDOVER_ACKNOWLEDGE_CODE 1
#define S1AP_HANDOVER_NOTIFY_CODE 2
#define S1AP_ENB_STATUS_TRANSFER_CODE 24
/*uplink NAS Transport*/
#define S1AP_UL_NAS_TX_MSG_CODE 13
#define S1AP_INITIAL_CTX_RESP_CODE 9

#define S1AP_UE_CTX_RELEASE_CODE 23
#define S1AP_UE_CTX_RELEASE_REQ_CODE 18

/*S1AP Protocol IE types*/
#define S1AP_IE_GLOBAL_ENB_ID 59
#define S1AP_IE_ENB_NAME 60
#define S1AP_IE_SUPPORTED_TAS 64
#define S1AP_IE_DEF_PAGING_DRX 137
#define S1AP_IE_MMENAME 61
#define S1AP_IE_SERVED_GUMMEIES 105
#define S1AP_IE_REL_MME_CAPACITY 87

#define S1AP_IE_MME_UE_ID 0
#define S1AP_IE_CAUSE 2
#define S1AP_IE_ENB_UE_ID 8
#define S1AP_IE_NAS_PDU  26
#define S1AP_IE_TAI  67
#define S1AP_IE_UTRAN_CGI  100
#define S1AP_IE_S_TMSI  96
#define S1AP_IE_RRC_EST_CAUSE  134
#define S1AP_ERAB_SETUP_CTX_SUR 51
#define S1AP_IE_HANDOVER_TYPE  1
#define S1AP_IE_TARGET_ID 4
#define S1AP_IE_SOURCE_TOTARGET_TRANSPARENTCONTAINER	104
#define S1AP_IE_E_RABAdmitted	18
#define S1AP_IE_Target_ToSource_TransparentContainer	123
#define S1AP_IE_ENB_Status_Transfer_TransparentContainer	90

/*NAS message type codes*/
#define NAS_ATTACH_REQUEST 0x41
#define NAS_SERVICE_REQUEST 0x4D
#define NAS_ATTACH_COMPLETE 0x43
#define NAS_ATTACH_REJECT 0x44
#define NAS_DETACH_REQUEST 0x45
#define NAS_TAU_REQUEST    0x48
#define NAS_TAU_COMPLETE   0x4a
#define NAS_AUTH_RESP 0x53
#define NAS_AUTH_REJECT 0x54
#define NAS_AUTH_FAILURE 0x5c
#define NAS_IDENTITY_REQUEST 0x55
#define NAS_IDENTITY_RESPONSE 0x56
#define NAS_SEC_MODE_COMPLETE 0x5e
#define NAS_SEC_MODE_REJECT  0x5f
#define NAS_ESM_RESP 0xda
#endif /*__S1AP_MSG_CODES*/
