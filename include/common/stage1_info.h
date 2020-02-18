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

#ifndef __STAGE1_INFO_H_
#define __STAGE1_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"
#include "3gpp_24008.h"

/**
 Message information used for Stage 1 : Initial UE attah. Form S1ap tp MME
*/

struct ue_attach_info {
	int s1ap_enb_ue_id;
	int criticality;
	unsigned char IMSI[BINARY_IMSI_LEN];
	struct TAI tai;
	struct CGI utran_cgi;
	struct MS_net_capab ms_net_capab;
	struct UE_net_capab ue_net_capab;
	enum ie_RRC_est_cause rrc_cause;
	int enb_fd;
	char esm_info_tx_required;
	unsigned char pti;
	unsigned int  flags; /* imsi - 0x00000001, GUTI - 0x00000002 */
	guti mi_guti;
    unsigned char seq_no;
    unsigned char dns_present;
    unsigned short int pco_length;
    unsigned char pco_options[MAX_PCO_OPTION_SIZE];
    
};

#define INITUE_STAGE1_BUF_SIZE sizeof(struct ue_attach_info)

struct commonRej_info 
{
  int IE_type; 
  int ue_idx; /*mme s1ap UE id*/
  int s1ap_enb_ue_id;
  int enb_fd;
  unsigned char cause; 
};

#define S1AP_REQ_REJECT_BUF_SIZE sizeof(struct commonRej_info) 

struct attachIdReq_info 
{
	int ue_idx; /*mme s1ap UE id*/
	int s1ap_enb_ue_id;
 	int enb_fd;
    unsigned char ue_type;
};

#define S1AP_ID_REQ_BUF_SIZE sizeof(struct attachIdReq_info) 

#endif /*STAGE1_INFO_H_*/
