#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "mme_app.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "s1ap_error.h"


static int g_Q_reset_s1ap_fd;

/**
Initialize the stage settings, Q,
destination communication etc.
*/

void
send_reset_s1ap_stage_init()
{
	/*Writing the detach signal to S11 Queue*/
	if ((g_Q_reset_s1ap_fd = open_ipc_channel(S1AP_GEN_RESET_QUEUE,
						IPC_WRITE)) == -1){
		log_msg(LOG_ERROR, "Error in opening write reset s1ap channel \n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Reset S1ap Channel for write opened \n");
	return;
}

static int
dispatch_reset_s1ap_channel_req(struct ue_reset_info *req)
{
	write_ipc_channel(g_Q_reset_s1ap_fd, (char *)&(req), UE_RESET_INFO_BUF_SIZE);
	log_msg(LOG_INFO, "Posted Reset S1ap channel to s1ap-app.\n");
	return SUCCESS;
}
