
/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __S1AP_STRUCTS_H_
#define __S1AP_STRUCTS_H_

#include <stdint.h>
#include <stdbool.h>

#include "sec.h"
#include "ProcedureCode.h"
#include "Criticality.h"
#include "S1AP-PDU.h"
#include "InitiatingMessage.h"

#define NAS_RAND_SIZE 16
#define NAS_AUTN_SIZE 16

#define AUTH_REQ_NO_OF_IES 3
#define SEC_MODE_NO_OF_IES 3
#define ESM_REQ_NO_OF_IES 3
#define EMM_INFO_REQ_NO_OF_IES 3
#define ICS_REQ_NO_OF_IES 6
#define DTCH_ACCEPT_NO_OF_IES 3
#define UE_CTX_RELEASE_NO_OF_IES 3
#define ATTACH_REJECT_NO_OF_IES 3 
#define SERVICE_REJECT_NO_OF_IES 3 
#define ATTACH_ID_REQUEST_NO_OF_IES 3
#define TAU_RSP_NO_OF_IES 3  /*mme s1ap id, enb s1ap id, nas pdu */

#define AUTH_REQ_NO_OF_NAS_IES 2
#define SEC_MODE_NO_OF_NAS_IES 1
#define ICS_REQ_NO_OF_NAS_IES 5
#define TAU_RSP_NO_OF_NAS_IES 2

#define AUTHREQ_NAS_SECURITY_PARAM 0x01
#define SERVICE_REQ_SECURITY_HEADER 12
#define SHORT_MAC_SIZE 2

/* Should we put this in NAS header ?*/
/* sec. 10.5.6.3 of 3GPP TS 24.008 has following statement:
 * The protocol configuration options is a type 4 information element with a minimum length of 3 octets and a maximum length of 253 octets.
 */

#define MAX_PCO_OPTION_SIZE 260

#define MSISDN_STR_LEN 10

#define EMM_MAX_TAI_LIST 16

#define SECURITY_KEY_SIZE 32

#define MAC_SIZE 4
#define AUTH_SYNC_FAILURE 21
#define AUTH_RESPONSE 53
/* ESM messages */
 #define ESM_MSG_ACTV_DEF_BEAR__CTX_REQ 0xc1

/*24.008 - 10.5.6.1
APN name can be in range of min 3 octets to max 102 octets
*/
#define MAX_APN_LEN 102


struct apn_name {
	unsigned char len;
	unsigned char val[MAX_APN_LEN];/*TODO: Make dynamic as range is big 3-102*/
};

/*TODO: Needed fro paging. Ignoring for now*/
struct proto_conf {
	int placeholder;
};

struct esm_sec_info {
	struct proto_conf proto_config;
};

/*NAS MSG IE CODES */
/* Message content : 
   3gpp 24.301
   Table 8.2.4.1: IEI Column.*/
typedef enum
{
    NAS_IE_TYPE_EPS_MOBILE_ID_IMSI=0x1,
    NAS_IE_TYPE_UE_NETWORK_CAPABILITY=0x2,
    NAS_IE_TYPE_ESM_MSG=0x3,
    NAS_IE_TYPE_TMSI_STATUS=0x09,
    NAS_IE_TYPE_MS_NETWORK_FEATURE_SUPPORT=0x0C,
    NAS_IE_TYPE_GUTI_TYPE=0x0E,
    NAS_IE_TYPE_ADDITIONAL_UPDATE_TYPE=0xF,
    NAS_IE_TYPE_MS_CLASSMARK_2=0x11,
    NAS_IE_TYPE_LAI=0x13,
    NAS_IE_TYPE_PTMSI_SIGNATURE=0x19,
    NAS_IE_TYPE_MS_CLASSMARK_3=0x20,
    NAS_IE_TYPE_APN=0x28,
    NAS_IE_TYPE_AUTH_FAIL_PARAM=0x30,
    NAS_IE_TYPE_MS_NETWORK_CAPABILITY=0x31,
    NAS_IE_TYPE_DRX_PARAM=0x5C,
    NAS_IE_TYPE_TAI=0x52,
    NAS_IE_TYPE_VOICE_DOMAIN_PREF_UE_USAGE_SETTING=0x5D,
    NAS_IE_TYPE_TX_FLAG=0xAA,
    NAS_IE_TYPE_PCO=0xAB,
    NAS_IE_TYPE_PTI=0xAC,
}nas_ie_type;

typedef struct MS_net_capab {
        bool          pres;
	unsigned char element_id;
	unsigned char len;
	unsigned char capab[6];
}MS_net_capab;

#if 0
/* MS Network capability */
typedef struct MS_net_capab {
   unsigned char pres;
   unsigned char len;
   unsigned char gea1;
   unsigned char smCapViaDdctdChan;
   unsigned char smCapViaGprsChan;
   unsigned char ucs2Supp;
   unsigned char ssScrInd;
   unsigned char soLsaCap;
   unsigned char revLvlInd;
   unsigned char pfcFeatMode;
   unsigned char gea2;
   unsigned char gea3;
   unsigned char gea4;
   unsigned char gea5;
   unsigned char gea6;
   unsigned char gea7;
   unsigned char lcsVaCap;
   unsigned char psInterRATho2UtranIuModeCap;
   unsigned char psInterRATho2EutranS1ModeCap;
   unsigned char csfbCap;
   unsigned char isrSupp;
   unsigned char srvcc2UtranCap;
   unsigned char epcCap;
}MS_net_capab;
#endif

struct UE_net_capab {
	unsigned char len;
	unsigned char capab[6];
};
#if 0
/* UE Network capability */
typedef struct UE_net_capab {
   unsigned char pres;
   unsigned char len;

   unsigned char eea7;
   unsigned char eea6;
   unsigned char eea5;
   unsigned char eea4;
   unsigned char eea3;
   unsigned char eea2_128;
   unsigned char eea1_128;
   unsigned char eea0;

   unsigned char eia7;
   unsigned char eia6;
   unsigned char eia5;
   unsigned char eia4;
   unsigned char eia3;
   unsigned char eia2_128;
   unsigned char eia1_128;
   unsigned char eia0;

   unsigned char uea7;
   unsigned char uea6;
   unsigned char uea5;
   unsigned char uea4;
   unsigned char uea3;
   unsigned char uea2;
   unsigned char uea1;
   unsigned char uea0;

   unsigned char uia7;
   unsigned char uia6;
   unsigned char uia5;
   unsigned char uia4;
   unsigned char uia3;
   unsigned char uia2;
   unsigned char uia1;
   unsigned char ucs2;

   unsigned char vcc_1xsr;

} UE_net_capab;
#endif

enum drx_params {
	PAGINX_DRX32,
	PAGINX_DRX64,
	PAGINX_DRX128,
	PAGINX_DRX256,
	PAGINX_DRX512,
};

struct s1ap_header{
	unsigned short procedure_code;
	unsigned char criticality;
};

#pragma pack(1)

/*36.413: 9.2.3.8 - MCC, MCN : Only 3 bytes are used*/
struct PLMN {
	unsigned char  idx[3];
};

struct TAI {
	struct PLMN plmn_id;
	short tac; /*2 bytes. 36.413: 9.2.3.7*/
};


typedef struct tai_list {
	uint8_t spare :1;
	uint8_t type :2;
	uint8_t num_of_elements :4;
	struct TAI partial_list[EMM_MAX_TAI_LIST];
} tai_list;

typedef struct pdn_address {
	uint8_t spare :5;
	uint8_t type :3;
	uint32_t ipv4; /* TODO: Revisit 24.301 - 9.9.4.9.1 */
} pdn_address;

typedef struct linked_transcation_id {
	uint8_t flag :1;
	uint8_t val :7;
} linked_transcation_id;

typedef struct esm_qos
{
	uint8_t reliability_class :3;
	uint8_t delay_class :3;
	uint8_t spare1 :2;
	uint8_t precedence_class :3;
	uint8_t spare2 :1;
	uint8_t peak_throughput :4;
	uint8_t mean_throughput :5;
	uint8_t spare3 :3;
	uint8_t delivery_err_sdu :3;
	uint8_t delivery_order :2;
	uint8_t traffic_class :3;
	uint8_t max_sdu_size;
	uint8_t mbr_ul;
	uint8_t mbr_dl;
	uint8_t sdu_err_ratio :4;
	uint8_t residual_ber :4;
	uint8_t trffic_prio :2;
	uint8_t transfer_delay :6;
	uint8_t gbr_ul;
	uint8_t gbr_dl;
	uint8_t src_stat_desc :4;
	uint8_t sig_ind :1;
	uint8_t spare4 :3;
	uint8_t mbr_dl_ext;
	uint8_t gbr_dl_ext;
	uint8_t mbr_ul_ext;
	uint8_t gbr_ul_ext;

} esm_qos;

/* TODO : Revisit 24.301 - 9.9.4.2.1 */
typedef struct ESM_APN_AMBR {
	uint8_t dl;
	uint8_t reserved;
	uint8_t dlext;
	uint8_t ulext;
	uint8_t dlext2;
	/* uint8_t dl_total; */
	uint8_t ulext2;
	/* uint8_t ul_total; */
} ESM_APN_AMBR;

typedef struct guti {
	uint8_t spare :4;
	uint8_t odd_even_indication :1;
	uint8_t id_type :3;
	struct PLMN plmn_id;
	uint16_t mme_grp_id;
	uint8_t mme_code;
	uint32_t m_TMSI;
} guti;

typedef struct esm_msg_container {
	uint8_t eps_bearer_id :4;
	uint8_t proto_discriminator :4;
	uint8_t procedure_trans_identity;
	uint8_t session_management_msgs;
	uint8_t eps_qos;  /* TODO: Revisit 24.301 - 9.9.4.3.1 */
	struct apn_name apn;
	struct apn_name selected_apn;
	pdn_address pdn_addr;
	linked_transcation_id linked_ti;
	esm_qos negotiated_qos;
	ESM_APN_AMBR apn_ambr;
} esm_msg_container;

typedef struct ue_sec_capabilities {
	uint8_t eea1 :1;
	uint8_t eea2 :1;
	uint8_t eea3 :1;
	uint8_t eea4 :1;
	uint8_t eea5 :1;
	uint8_t eea6_128 :1;
	uint8_t eea7_128 :1;
	uint8_t eea8 :1;

	uint8_t eia1 :1;
	uint8_t eia2 :1;
	uint8_t eia3 :1;
	uint8_t eia4 :1;
	uint8_t eia5 :1;
	uint8_t eia6_128 :1;
	uint8_t eia8_128 :1;
	uint8_t eia8 :1;

	uint8_t uea1 :1;
	uint8_t uea2 :1;
	uint8_t uea3 :1;
	uint8_t uea4 :1;
	uint8_t uea5 :1;
	uint8_t uea6 :1;
	uint8_t uea7 :1;
	uint8_t uea8 :1;

	uint8_t uia1 :1;
	uint8_t uia2 :1;
	uint8_t uia3 :1;
	uint8_t uia4 :1;
	uint8_t uia5 :1;
	uint8_t uia6 :1;
	uint8_t uia7 :1;
	uint8_t spare1 :1;

	uint8_t gea1 :1;
	uint8_t gea2 :1;
	uint8_t gea3 :1;
	uint8_t gea4 :1;
	uint8_t gea5 :1;
	uint8_t gea6 :1;
	uint8_t gea7 :1;
	uint8_t spare2 :1;
} ue_sec_capabilities;

typedef struct nas_pdu_header {
	unsigned char security_header_type:4;
	unsigned char proto_discriminator:4;
	unsigned char message_type;
	unsigned char security_encryption_algo:4;
	unsigned char security_integrity_algo:4;
	unsigned char nas_security_param;
	unsigned char mac[MAC_SIZE];
	unsigned char short_mac[SHORT_MAC_SIZE];
	unsigned char ksi;
	unsigned char seq_no;
	unsigned char eps_bearer_identity;
	unsigned char procedure_trans_identity;
} nas_pdu_header;

#pragma pack()

/****Information elements presentations **/
#define BINARY_IMSI_LEN 8 /*same as packet capture. TODO: Write macros*/
#define BCD_IMSI_STR_LEN 15

/*36.413 - 9.2.1.38*/
struct CGI {
	struct PLMN plmn_id;
	int cell_id;
};

//Service Request
struct STMSI {
	uint8_t mme_code;
        uint32_t m_TMSI;

};

/*36.413: 9.2.1.37*/
#define MACRO_ENB_ID_SIZE 20
struct ie_global_enb_id {
	int plmn;
	char macro_enb_id[MACRO_ENB_ID_SIZE];
	/*TODO: make union of enb IDs*/
};

/*36.413: 9.1.8.4*/
#define ENB_NAME_SIZE 150
struct ie_enb_name {
	char enb_name[ENB_NAME_SIZE];
};

enum ie_fail_internal_cause {
	AIA_FAIL,
	SECURITY_MOD_REJECT_FAIL,
	MAX_FAIL_CAUSE
};

/*36.413: 9.2.1.3a*/
enum ie_RRC_est_cause {
	EMERGENCY,
	HIGHPRIORITYACCESS,
	MT_ACCESS,
	MO_SIGNALLING,
	MO_DATA,
	DELAYTOLERANTACCESS,
	MO_VOICECALL,
	MO_EXCEPTIONDATA
};

/**E-RAB structure declarations**/
struct eRAB_header { //TODO: making provision, chec -is it needed?
	unsigned char criticality;
};

struct eRAB_setup_ctx_SU {
	unsigned short eRAB_id;
	unsigned short dont_know_byte;
	unsigned int transp_layer_addr;
	unsigned int gtp_teid;
};

union eRAB_IE {
	struct eRAB_setup_ctx_SU su_res;
};

typedef struct eRAB_elements {
	struct eRAB_header header;
	unsigned char no_of_elements;
	union eRAB_IE *elements;
}eRAB_elements;
/**eRAB structures end**/

struct pco 
{
    unsigned short int pco_length;
    unsigned char pco_options[MAX_PCO_OPTION_SIZE];
};

/**Information elements structs end**/
typedef union nas_pdu_elements_union {
	unsigned char rand[NAS_RAND_SIZE];
	unsigned char autn[NAS_AUTN_SIZE];
	unsigned char IMSI[BINARY_IMSI_LEN];
	unsigned char short_mac[SHORT_MAC_SIZE];
	struct esm_sec_info esm_info;
	enum drx_params drx;
	struct MS_net_capab ms_network;
	struct UE_net_capab ue_network;

	struct XRES   auth_resp; /*Authentication response*/
	struct AUTS   auth_fail_resp; /*Authentication response*/

	struct apn_name apn;

	unsigned char attach_res;
	unsigned char t3412;
	tai_list tailist;
	esm_msg_container esm_msg;
	guti mi_guti;
	bool esm_info_tx_required;
	unsigned char pti;
	unsigned char eps_res;
	unsigned char spare;
    struct pco pco_opt;
}nas_pdu_elements_union;

typedef struct nas_pdu_elements {
   nas_ie_type msgType;
   nas_pdu_elements_union pduElement;
}nas_pdu_elements;

#define NAS_MSG_UE_IE_GUTI  0x00000001
#define NAS_MSG_UE_IE_IMSI  0x00000002
#define UE_ID_IMSI(flags)   ((flags & NAS_MSG_UE_IE_IMSI) == NAS_MSG_UE_IE_IMSI)
#define UE_ID_GUTI(flags)   ((flags & NAS_MSG_UE_IE_GUTI) == NAS_MSG_UE_IE_GUTI)

typedef struct nasPDU {
	nas_pdu_header header;
	unsigned char elements_len;
	nas_pdu_elements *elements;
        unsigned int flags; 
} nasPDU;

#pragma pack(1)
/* TODO : Change type */
typedef struct ue_aggregate_maximum_bitrate {
	uint32_t uEaggregateMaxBitRateDL;
	uint32_t uEaggregateMaxBitRateUL;
} ue_aggregate_maximum_bitrate;

typedef struct allocation_retention_prio {
	uint8_t prioLevel :4;
	uint8_t preEmptionCapab :1;
	uint8_t preEmptionVulnebility :1;
	uint8_t spare :2;
} allocation_retention_prio;

typedef struct E_RAB_Level_QoS_Params {
	uint8_t qci;
	//uint8_t ext;
    allocation_retention_prio arPrio;
} E_RAB_Level_QoS_Params;

typedef struct ERABSetup {
	uint8_t e_RAB_ID;
	E_RAB_Level_QoS_Params e_RAB_QoS_Params;
	uint32_t transportLayerAddress;
	uint32_t gtp_teid;
	struct nasPDU nas;
} ERABSetup;

#pragma pack()
/* Dependencies */
typedef enum s1apCause_PR {
    s1apCause_PR_NOTHING,   /* No components present */
    s1apCause_PR_radioNetwork,
    s1apCause_PR_transport,
    s1apCause_PR_nas,
    s1apCause_PR_protocol,
    s1apCause_PR_misc

} s1apCause_PR;

typedef enum s1apCause_PR_transporauseRadioNetwork {
    s1apCauseRadioNetwork_unspecified   = 0,
    s1apCauseRadioNetwork_tx2relocoverall_expiry    = 1,
    s1apCauseRadioNetwork_successful_handover   = 2,
    s1apCauseRadioNetwork_release_due_to_eutran_generated_reason    = 3,
    s1apCauseRadioNetwork_handover_cancelled    = 4,
    s1apCauseRadioNetwork_partial_handover  = 5,
    s1apCauseRadioNetwork_ho_failure_in_target_EPC_eNB_or_target_system = 6,
    s1apCauseRadioNetwork_ho_target_not_allowed = 7,
    s1apCauseRadioNetwork_tS1relocoverall_expiry    = 8,
    s1apCauseRadioNetwork_tS1relocprep_expiry   = 9,
    s1apCauseRadioNetwork_cell_not_available    = 10,
    s1apCauseRadioNetwork_unknown_targetID  = 11,
    s1apCauseRadioNetwork_no_radio_resources_available_in_target_cell   = 12,
    s1apCauseRadioNetwork_unknown_mme_ue_s1ap_id    = 13,
    s1apCauseRadioNetwork_unknown_enb_ue_s1ap_id    = 14,
    s1apCauseRadioNetwork_unknown_pair_ue_s1ap_id   = 15,
    s1apCauseRadioNetwork_handover_desirable_for_radio_reason   = 16,
    s1apCauseRadioNetwork_time_critical_handover    = 17,
    s1apCauseRadioNetwork_resource_optimisation_handover    = 18,
    s1apCauseRadioNetwork_reduce_load_in_serving_cell   = 19,
    s1apCauseRadioNetwork_user_inactivity   = 20,
    s1apCauseRadioNetwork_radio_connection_with_ue_lost = 21,
    s1apCauseRadioNetwork_load_balancing_tau_required   = 22,
    s1apCauseRadioNetwork_cs_fallback_triggered = 23,
    s1apCauseRadioNetwork_ue_not_available_for_ps_service   = 24,
    s1apCauseRadioNetwork_radio_resources_not_available = 25,
    s1apCauseRadioNetwork_failure_in_radio_interface_procedure  = 26,
    s1apCauseRadioNetwork_invalid_qos_combination   = 27,
    s1apCauseRadioNetwork_interrat_redirection  = 28,
    s1apCauseRadioNetwork_interaction_with_other_procedure  = 29,
    s1apCauseRadioNetwork_unknown_E_RAB_ID  = 30,
    s1apCauseRadioNetwork_multiple_E_RAB_ID_instances   = 31,
    s1apCauseRadioNetwork_encryption_and_or_integrity_protection_algorithms_not_supported   = 32,
    s1apCauseRadioNetwork_s1_intra_system_handover_triggered    = 33,
    s1apCauseRadioNetwork_s1_inter_system_handover_triggered    = 34,
    s1apCauseRadioNetwork_x2_handover_triggered = 35,
    s1apCauseRadioNetwork_redirection_towards_1xRTT = 36,
    s1apCauseRadioNetwork_not_supported_QCI_value   = 37,
    s1apCauseRadioNetwork_invalid_CSG_Id    = 38,
    s1apCauseRadioNetwork_release_due_to_pre_emption    = 39
} e_s1apCauseRadioNetwork;

typedef enum s1apCauseTransport {
    s1apCauseTransport_transport_resource_unavailable   = 0,
    s1apCauseTransport_unspecified  = 1
} e_s1apCauseTransport;

typedef enum s1apCauseNas {
    s1apCauseNas_normal_release = 0,
    s1apCauseNas_authentication_failure = 1,
    s1apCauseNas_detach = 2,
    s1apCauseNas_unspecified    = 3,
    s1apCauseNas_csg_subscription_expiry    = 4
} e_s1apCauseNas;

typedef enum s1apCauseProtocol {
    s1apCauseProtocol_transfer_syntax_error = 0,
    s1apCauseProtocol_abstract_syntax_error_reject  = 1,
    s1apCauseProtocol_abstract_syntax_error_ignore_and_notify   = 2,
    s1apCauseProtocol_message_not_compatible_with_receiver_state    = 3,
    s1apCauseProtocol_semantic_error    = 4,
    s1apCauseProtocol_abstract_syntax_error_falsely_constructed_message = 5,
    s1apCauseProtocol_unspecified   = 6
} e_s1apCauseProtocol;

typedef enum s1apCauseMisc {
    s1apCauseMisc_control_processing_overload   = 0,
    s1apCauseMisc_not_enough_user_plane_processing_resources    = 1,
    s1apCauseMisc_hardware_failure  = 2,
    s1apCauseMisc_om_intervention   = 3,
    s1apCauseMisc_unspecified   = 4,
    s1apCauseMisc_unknown_PLMN  = 5
} e_s1apCauseMisc;

typedef enum emmCause {
    emmCause_ue_id_not_derived_by_network   = 9,
} e_emmCause;

/* s1apCauseMisc */
typedef long     s1apCauseMisc_t;
/* s1apCauseProtocol */
typedef long     s1apCauseProtocol_t;
/* s1apCauseNas */
typedef long     s1apCauseNas_t;
/* s1apCauseTransport */
typedef long     s1apCauseTransport_t;
/* s1apCauseRadioNetwork */
typedef long     s1apCauseRadioNetwork_t;

typedef struct s1apCause {
    s1apCause_PR present;
    union s1apCause_u {
        s1apCauseRadioNetwork_t  radioNetwork;
        s1apCauseTransport_t     transport;
        s1apCauseNas_t   nas;
        s1apCauseProtocol_t  protocol;
        s1apCauseMisc_t  misc;
    } choice;
} s1apCause_t;

typedef struct proto_IE_data {
	int 			IE_type;
    union value{
        struct ie_enb_name 	enb_name;
        struct ie_global_enb_id global_enb_id;
        long			enb_ue_s1ap_id;
        long			mme_ue_s1ap_id;
        struct 			nasPDU nas;
        struct s1apCause cause;
        struct TAI 		 tai;
        struct CGI 		 utran_cgi;
        struct STMSI	 s_tmsi;
        enum ie_RRC_est_cause 	rrc_est_cause;
        struct eRAB_elements 	erab;
        ue_aggregate_maximum_bitrate ue_aggrt_max_bit_rate;
        ERABSetup E_RABToBeSetupItemCtxtSUReq;
        ue_sec_capabilities ue_sec_capab;
        uint8_t sec_key[SECURITY_KEY_SIZE];
    }val;
}proto_IEs;

struct proto_IE {
    ProcedureCode_t  procedureCode;
    Criticality_t    criticality;
	short 		no_of_IEs;
	proto_IEs	*data;
    uint8_t     ie_nas_index;
    uint8_t     ie_tai_index;
    uint8_t     ie_cgi_index;
};

// refer 36.413 . Section 9.3.6 
enum protocolie_id {
	id_MME_UE_S1AP_ID = 0,
	id_Cause = 2,
	id_eNB_UE_S1AP_ID = 8,
	id_ERABToBeSetupListCtxtSUReq = 24,
	id_NAS_PDU = 26,
	id_ERABToBeSetupItemCtxtSUReq = 52,
	id_uEaggregatedMaximumBitrate = 66,
	id_SecurityKey = 73,
    id_ueAssociatedLogicalS1Conn = 91,
    id_ResetType = 92, 
	id_UE_S1AP_IDs = 99,
	id_UESecurityCapabilities = 107,
};

enum protocol_discriminator{
	EPSSessionManagementMessage = 2,
    EPSMobilityManagementMessages = 7,
};

enum criticality{
	CRITICALITY_REJECT = 0x0,
	CRITICALITY_IGNORE = 0x40,
	CRITICALITY_NOTIFY,
};

enum eps_nas_mesage_type {
	AttachAccept = 0x42,
	AttachReject = 0x44,
	DetachAccept = 0x46,
    TauAccept    = 0x49,
    TauReject    = 0x4b,
	ServiceReject = 0x4e,
	AuthenticationRequest = 0x52,
    IdentityRequest       = 0x55,
	SecurityModeCommand = 0x5d,
    EMMInformation = 0x61,
	ESMInformationRequest = 0xd9,
};

/* Refer 36.413 section - 9.3.6 */
enum procedure_code {
	id_InitialContextSetup = 9,
	id_downlinkNASTransport = 11,
    id_reset           = 14,
	id_errorIndication = 15,
	id_UEContexRelease = 23,
};

typedef struct s1ap_PDU {
	unsigned char procedurecode;
	unsigned char criticality;
	struct proto_IE value;
}s1ap_PDU;

/* NAS Security Header */
typedef enum security_header_type {
    Plain = 0,
    IntegrityProtected,
    IntegrityProtectedCiphered,
    IntegrityProtectedEPSSecCntxt,
}security_header_type;

typedef struct nas_pdu_header_sec {
        unsigned char security_header_type:4;
        unsigned char proto_discriminator:4;
        unsigned char mac[MAC_SIZE];
        unsigned char seq_no;
}nas_pdu_header_sec;

typedef struct nas_pdu_header_short {
        unsigned char security_header_type:4;
        unsigned char proto_discriminator:4;
        unsigned char message_type;
}nas_pdu_header_short;

typedef struct nas_pdu_header_long {
        unsigned char security_header_type:4;
        unsigned char proto_discriminator:4;
        unsigned char procedure_trans_identity;
        unsigned char message_type;
}nas_pdu_header_long;

/* NAS Security Encryption Algorithm */
typedef enum security_encryption_algo {
	Algo_EEA0 = 0,

}security_encryption_algo;

/* NAS Security Integrity Algorithm */
typedef enum security_integrity_algo {
	Algo_EIA0 = 0,
	Algo_128EIA1 = 1,
}security_integrity_algo;


#define BUFFER_SIZE 1000 /* S1AP packet max size */

typedef struct Buffer {
	unsigned char buf[BUFFER_SIZE];
	unsigned char pos;
}Buffer;

#endif /*__S1AP_STRUCTS_H*/
