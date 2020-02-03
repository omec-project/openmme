
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "log.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "s11_structs.h"
#include "ddn_info.h"
#include "gtpv2c.h"
#include "gtpv2c_ie.h"
#include "gtpV2StackWrappers.h"


/****Globals and externs ***/

static int g_Q_DDN_fd;
extern int g_s11_fd;

extern struct sockaddr_in g_s11_cp_addr;
extern socklen_t g_s11_serv_size;

/*Making global just to avoid stack passing*/
static char buf[S11_DDN_ACK_BUF_SIZE];

/*TODO: S11 protocol sequence number - need to make it atomic. multiple thread to access this*/
extern volatile uint32_t g_s11_sequence;


/****Global and externs end***/
extern struct GtpV2Stack* gtpStack_gp;
struct MsgBuffer*  ddnAckMsgBuf_p = NULL;

/**
Initialize the stage settings, Q, 
destination communication etc.
*/
static void
init_stage()
{
	log_msg(LOG_INFO, "Stag 7 modify bearer initializer\n");
	if ((g_Q_DDN_fd  = open_ipc_channel(S11_DDN_ACK_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error starting reader Downlink data Notification Acknowledge "\
			" request IPC.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "S11 reader - Downlink data Notification Acknowledge: Opened\n");

	/*Open destination queue for writing. It is AIR, ULR Q in this stage*/
	log_msg(LOG_INFO, "S11 interface writer: waiting\n");
	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S11_DDN_ACK_BUF_SIZE);
	MsgBuffer_reset(ddnAckMsgBuf_p);

	while (bytes_read < S11_DDN_ACK_BUF_SIZE) {//TODO : Recheck condition
		if ((bytes_read = read_ipc_channel(
			g_Q_DDN_fd, buf, 
			S11_DDN_ACK_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Downlink data Notification Acknowledge received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
ddn_ack_processing()
{
	struct ddn_ack_Q_msg *ddn_msg = (struct ddn_ack_Q_msg *)buf;

	GtpV2MessageHeader gtpHeader;
	gtpHeader.msgType = GTP_DOWNLINK_DATA_NOTIFICATION_ACK;
	gtpHeader.sequenceNumber = g_s11_sequence;
	gtpHeader.teidPresent = true;
	gtpHeader.teid = ddn_msg->ue_idx;

	g_s11_sequence++;

	DownlinkDataNotificationAcknowledgeMsgData msgData;
	memset(&msgData, 0, sizeof(DownlinkDataNotificationAcknowledgeMsgData));

	msgData.causeIePresent = true;
	msgData.cause.causeValue = ddn_msg->cause;

	GtpV2Stack_buildGtpV2Message(gtpStack_gp, ddnAckMsgBuf_p, &gtpHeader, &msgData);

	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int 
post_to_next()
{
	sendto(g_s11_fd,
			MsgBuffer_getDataPointer(ddnAckMsgBuf_p),
			MsgBuffer_getBufLen(ddnAckMsgBuf_p), 0,
			(struct sockaddr*)&g_s11_cp_addr, g_s11_serv_size);

	log_msg(LOG_INFO, "Downlink data Notification Acknowledge send, len - %d bytes.\n", MsgBuffer_getBufLen(ddnAckMsgBuf_p));

	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_ddn_ack()
{
	close_ipc_channel(g_Q_DDN_fd);
	log_msg(LOG_INFO, "Shutdown Downlink data Notification Acknowledge handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
ddn_ack_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Downlink data Notification Acknowledge initialized\n");
	
	while(1){
		read_next_msg();

		ddn_ack_processing();

		post_to_next();
	}

	return NULL;
}
