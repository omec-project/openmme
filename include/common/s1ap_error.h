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
	uint32_t s1ap_enb_ue_id;
    uint32_t s1ap_mme_ue_id;
};

#define UE_RESET_INFO_BUF_SIZE sizeof(struct ue_reset_info)

#endif /*__S1AP_ERROR_H_*/
