#ifndef __S1AP_MME_MSG_H__
#define __S1AP_MME_MSG_H__ 
#include "s1ap_structs.h"

struct identityResp_Q_msg {
	int ue_idx;
	int status;
	unsigned char IMSI[BINARY_IMSI_LEN];
};

#define S1AP_IDRESP_BUF_SIZE sizeof(struct identityResp_Q_msg)

struct tauReq_Q_msg {
	int ue_idx;
	int s1ap_enb_ue_id;
    int seq_num;
};
#define S1AP_TAUREQ_BUF_SIZE sizeof(struct tauReq_Q_msg)


struct tauResp_Q_msg {
	int ue_idx;
    int enb_fd;
	int s1ap_enb_ue_id;
	int status;
    int dl_seq_no;
    uint8_t int_key[NAS_INT_KEY_SIZE];
	struct TAI tai;
};
#define S1AP_TAURESP_BUF_SIZE sizeof(struct tauResp_Q_msg)

#endif
