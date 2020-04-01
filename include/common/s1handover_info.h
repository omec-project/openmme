

#ifndef _S1HANDOVER_INFO_H_
#define _S1HANDOVER_INFO_H_
#include "s1ap_structs.h"
struct handover_required_Q_msg {

	int s1ap_enb_ue_id;
	int s1ap_mme_ue_id;
	enum handoverType handoverType;
	struct s1apCause cause;
	struct targetId target_id;
	unsigned char srcToTargetTranspContainer[TRANS_CONT_SIZE];
	
};
#define S1AP_HO_REQUIRED_BUF_SIZE sizeof(struct handover_required_Q_msg )
struct handover_req_acknowledge_Q_msg{

	int s1ap_enb_ue_id;
	int s1ap_mme_ue_id;
	struct ERAB_admitted_list erab_admitted_list;
	unsigned char targetToSrcTranspContainer[TRANS_CONT_SIZE];
};
#define S1AP_HO_REQ_ACK_BUF_SIZE sizeof(struct handover_req_acknowledge_Q_msg)
struct handover_notify_Q_msg{

	int s1ap_enb_ue_id;
	int s1ap_mme_ue_id;
	struct CGI utran_cgi;
	struct TAI tai;
};
#define S1AP_HO_NOTIFY_BUF_SIZE sizeof(struct handover_notify_Q_msg)
struct enb_status_transfer_Q_msg {

	int s1ap_mme_ue_id;
	int s1ap_enb_ue_id;
	struct enB_status_transfer_transparent_container_list enB_status_transfer_transparent_containerlist;
};
#define S1AP_HO_ENB_STATUS_TRANS_BUF_SIZE sizeof(struct enb_status_transfer_Q_msg )
struct handover_request_Q_msg {
	int s1ap_mme_ue_id;
	enum handoverType handoverType;
	s1apCause_t cause;
	unsigned char srcToTargetTranspContainer[TRANS_CONT_SIZE];
	ue_aggregate_maximum_bitrate ue_aggrt_max_bit_rate;
	struct ERABSetupList eRABSetupList;
	ue_sec_capabilities ue_sec_capab;
	struct security_context security_context;
	int enb_fd;
	struct fteid gtp_teid;
	unsigned char sec_key[32];
};

#define S1AP_HO_REQUEST_BUF_SIZE sizeof(struct handover_request_Q_msg)

struct handover_command_Q_msg {
	int s1ap_mme_ue_id;
	int s1ap_enb_ue_id;
	enum handoverType handoverType;
	unsigned short 	eRAB_id;
	unsigned char targetToSrcTranspContainer[TRANS_CONT_SIZE];
	int enb_fd;
	
};
#define S1AP_HO_COMMAND_BUF_SIZE sizeof(struct handover_command_Q_msg)

struct mme_status_transfer_Q_msg {
	int s1ap_mme_ue_id;
	int s1ap_enb_ue_id;
	struct enB_status_transfer_transparent_container_list enB_status_transfer_transparent_containerlist;
	int enb_fd;
};
#define S1AP_MME_STATUS_TRANSFER_BUF_SIZE sizeof(struct mme_status_transfer_Q_msg)
#endif /*_S1HANDOVER_INFO_H_*/
