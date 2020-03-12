/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __UE_TABLE_H_
#define __UE_TABLE_H_

#include "stage1_info.h"
#include "stage1_s6a_msg.h"
#include "s1ap_structs.h"
#include "s11_structs.h"

extern int g_tmsi_allocation_array[];
extern struct UE_info* g_UE_list[]; 

/*allocate UEs in pool to save memory. Only when pool size is crossed then
allocate next pool */
/*5 pools*/
#define UE_POOL_SIZE 10
#define STR_IMSI_LEN 16
#define THREADPOOL_SIZE 10
/*Each pool to have 65535 UEs*/
#define UE_POOL_CNT 550000
#define TMSI_POOL_SIZE 10000

/*Macro to access UE element based on ue index*/
#define GET_UE_ENTRY(index) ((index >= UE_POOL_CNT) ? (NULL) : (&(g_UE_list[index/UE_POOL_CNT][index%UE_POOL_CNT])))

/**
* State table that UE attach and detach goes through.
*/
enum ue_stages{
  UNASSIGNED_ENTRY = 0,
  ATTACH_STAGE1,
  ATTACH_STAGE1_RESYNC,
  STAGE1_WAITING, /*STAGE1 processing is done. Keep waiting for events to move
		  in next stage*/
  STAGE1_ULA_DONE,
  STAGE1_AIA_DONE,
  STAGE1_AIA_FAIL,
  ATTACH_STAGE2,
  STAGE2_WAITING,
  ATTACH_STAGE3,
  STAGE3_WAITING,
  ATTACH_STAGE4,
  STAGE4_WAITING,
  STAGE4_FAIL,
  ATTACH_STAGE5,
  STAGE5_WAITING,
  ATTACH_STAGE6,
  STAGE6_WAITING,
  ATTACH_STAGE7,
  STAGE7_WAITING,
  ATTACH_STAGE8,
  STAGE8_WAITING,
  STAGE8_NAS_ATCH_DONE,
  STAGE8_MBR_DONE,
  ATTACH_DONE,
  DETACH_START=100,
  DETACH_STAGE1, /*Detach Received. Purge Req and DSR sent.*/
  DETACH_STAGE2_PURGE_DONE, /*Purge response received after detach.*/
  DETACH_STAGE2_DS_DONE,/*DSR response received after detach.*/
  DETACH_STAGE2,/*Purge and DSR response received after detach.*/
  DETACH_DONE,
  CTX_RELEASE_STAGE, /*Received Ctx release from ENB.*/
  S1AP_HANDLE_MESSAGE_STAGE,
  PAGING_START,
  PAGING_WF_SVC_REQ,
  SVC_REQ_WF_INIT_CTXT_RESP,
  SVC_REQ_WF_MODIFY_BEARER_RESP,
  UE_ERROR=200,
};

#define TOTAL_STAGES  20

enum ue_proc{
  UNKNOWN_PROC = 0,
  ATTACH_PROC,
  SERVICE_REQ_PROC,
  TAU_PROC,
  DETACH_PROC
};

/*After Ctx release handling UE will move to ECM idle state.
  After handling Attach or service request and establishing connection
  with ENB the UE state will be ECM Connected.*/
enum ecm_states{
 ECM_UNKNOWN=0,
 ECM_IDLE,
 ECM_CONNECTED
};
struct secinfo {
	uint8_t int_key[NAS_INT_KEY_SIZE];
	uint8_t kenb_key[KENB_SIZE];
};

/**
 * APN AMBR infornmation : received from ULA
 * Max requested bandwidth uplink and downlink
 */
struct AMBR {
	unsigned int max_requested_bw_dl;
	unsigned int max_requested_bw_ul;
};

#define UE_INFO_INVALID_MAGIC 0xffffffff
#define UE_INFO_VALID_MAGIC   0x12345678
#define IS_VALID_UE_INFO(ue_info) (ue_info->magic == UE_INFO_VALID_MAGIC)
struct UE_info{
	int             enb_fd;
	enum ue_stages  ue_state;
	enum ue_proc    ue_curr_proc;
	enum ecm_states ecm_state;
	int             s1ap_enb_ue_id;
	unsigned char   IMSI[BINARY_IMSI_LEN];
	struct TAI      tai;//TODO: will be list of 16 TAI's for UE.
	struct CGI      utran_cgi;
	struct STMSI 	s_tmsi;		//Service Request
	struct E_UTRAN_sec_vector *aia_sec_info; /*TODO: Check whether this
						info is needed after attach. If yes then make it static array.*/
	struct MS_net_capab  ms_net_capab;
	struct UE_net_capab  ue_net_capab;
	struct apn_name apn; /*TODO: Make it dynamic to save space. otherwise
								  required len will be 103 bytes*/
	struct apn_name selected_apn; /* For high priority apn selected by
					mme, also can be used as default apn
					when there is no apn from UE */

	// enum          RRC_est_cause rrc_cause;

	/**Information received from ULA*/
	char            MSISDN[MSISDN_STR_LEN];
	unsigned int    apn_config_profile_ctx_id;
	struct AMBR     ambr; /*24.301 : 9.9.4.2*/
	unsigned int    RAU_TAU_timer;
	int             subscription_status;
	int             net_access_mode;
	unsigned int    access_restriction_data;
	/**/

	/**Information received from Service Request*/
	unsigned int ksi;
	unsigned int seq_no;
	unsigned short mac;
	/**/

	unsigned short  dl_seq_no;
	unsigned short  ul_seq_no;

	struct         fteid s11_sgw_c_fteid;
	struct         fteid s5s8_pgw_c_fteid;
	struct         fteid s1u_sgw_u_fteid;
	struct         fteid s5s8_pgw_u_fteid;
	struct         fteid s1u_enb_u_fteid;

	struct         PAA pdn_addr;
	unsigned char  bearer_id;
	unsigned short eRAB_id;

	struct secinfo ue_sec_info;
	uint8_t cause;
	uint32_t flags;
	bool esm_info_tx_required;
	unsigned char pti;
  unsigned int  magic;
    unsigned int m_tmsi;
  unsigned short int ue_index;
  uint8_t arp;
  uint16_t pco_length;
  unsigned char pco_options[MAX_PCO_OPTION_SIZE];
  struct UE_info *next_ue; 
};

int allocate_ue_index();
int get_index_from_list();
int insert_index_into_list(int ue_index);
void imsi_bin_to_str(unsigned char *b_imsi, char *s_imsi);
void add_ue_entry(struct UE_info *ue_entry);
void release_ue_entry(struct UE_info *ue_entry);
void init_ue_tables();
int allocate_tmsi(struct UE_info *ue_entry);
int get_ue_index_from_tmsi(int tmsi);
void print_current_active_ue_info();

#endif /*ue_table*/
