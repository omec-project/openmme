

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "err_codes.h"
#include "options.h"
#include "ipc_api.h"
#include "message_queues.h"
#include "s11.h"
#include "s11_config.h"
#include "ddn_info.h"
#include "gtpV2StackWrappers.h"

/*Globals and externs*/
extern int g_Q_Ddn_fd;
extern struct GtpV2Stack* gtpStack_gp;

/*End : globals and externs*/

int
s11_Ddn_handler(MsgBuffer* message, GtpV2MessageHeader* hdr)
{
	struct ddn_Q_msg ddn_info;

	DownlinkDataNotificationMsgData msgData;
	memset(&msgData, 0, sizeof(DownlinkDataNotificationMsgData));

	/*****Message structure***
	*/

	//TODO : check cause foor the result verification
	
	/*Check whether has teid flag is set. Also check whether this check is needed for CSR.*/
	ddn_info.ue_idx = hdr->teid;

	bool rc = GtpV2Stack_decodeMessage(gtpStack_gp, hdr, message, &msgData);
	if(rc == false)
	{
			log_msg(LOG_ERROR, "s11_CS_resp_handler: "
					"Failed to decode Downlink Data Notification Msg %d\n",
					hdr->teid);
			return E_PARSING_FAILED;
	}
	if (msgData.epsBearerIdIePresent)
		ddn_info.eps_bearer_id = msgData.epsBearerId.epsBearerId;

	if (msgData.causeIePresent)
		ddn_info.cause = msgData.cause.causeValue;

	if (msgData.allocationRetentionPriorityIePresent) {
		ddn_info.pci = msgData.allocationRetentionPriority.pci;
		ddn_info.pl = msgData.allocationRetentionPriority.pl;
		ddn_info.pvi = msgData.allocationRetentionPriority.pvi;
	}

	/*Send CS response msg*/
	write_ipc_channel(g_Q_Ddn_fd, (char *)&ddn_info, S11_DDN_BUF_SIZE);
	log_msg(LOG_INFO, "Send DDN to mme-app \n");

	return SUCCESS;
}

