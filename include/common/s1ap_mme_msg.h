#ifndef __S1AP_MME_MSG_H__
#define __S1AP_MME_MSG_H__ 
#include "s1ap_structs.h"

struct identityResp_Q_msg {
	int ue_idx;
	int status;
	unsigned char IMSI[BINARY_IMSI_LEN];
};

#define S1AP_IDRESP_BUF_SIZE sizeof(struct identityResp_Q_msg)
#endif
