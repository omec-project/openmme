#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "mme_app.h"
#include "ue_table.h"
#include "err_codes.h"
#include "message_queues.h"
#include "ipc_api.h"
#include "stage3_info.h"
#include "s1ap_mme_msg.h"

/****Globals and externs ***/

extern struct UE_info * g_UE_list[];
extern int g_mme_hdlr_status;

static int g_Q_identityresp_fd;

/*Making global just to avoid stack passing*/
static char buf[S1AP_IDRESP_BUF_SIZE];

/* Add counter */
/****Global and externs end***/

/**
Initialize the stage settings, Q,
destination communication etc.
*/
static void
init_stage()
{
	if ((g_Q_identityresp_fd  = open_ipc_channel(S1AP_ID_RSP_QUEUE,
						IPC_READ)) == -1){
		log_msg(LOG_ERROR, "Error in opening reader stage 3 IPC channel.\n");
		pthread_exit(NULL);
	}
	log_msg(LOG_INFO, "Stage 3 reader - s1ap Authentication response : Connected\n");

	return;
}

/**
* Read next message from stage Q for processing.
*/
static int
read_next_msg()
{
	int bytes_read=0;

	memset(buf, 0, S1AP_IDRESP_BUF_SIZE );
	while (bytes_read < S1AP_IDRESP_BUF_SIZE) {
		if ((bytes_read = read_ipc_channel(
			g_Q_identityresp_fd, buf, S1AP_IDRESP_BUF_SIZE))
			 == -1) {
			log_msg(LOG_ERROR, "Error in reading \n");
			/* TODO : Add proper error handling */
		}
		log_msg(LOG_INFO, "Authentication response Received - Len: %d\n",
			bytes_read);
	}

	return bytes_read;
}

/**
* Stage specific message processing.
*/
static int
stage3_processing()
{
	/*Parse and validate  the buffer*/
	struct identityResp_Q_msg *id_resp = (struct identityResp_Q_msg *)buf;
	struct UE_info *ue_entry = GET_UE_ENTRY(id_resp->ue_idx);

	ue_entry->ue_state = STAGE3_WAITING;
	/*Check the state*/
	if(SUCCESS != id_resp->status) 
    {
	  return E_FAIL; 
	}
	log_msg(LOG_INFO, "Stage 3: Auth resp done for UE: %d\n",
		id_resp->ue_idx);

    /* validate IMSI ?? */
	/*Ready post to next processing*/
	return SUCCESS;
}

/**
* Post message to next handler of the stage
*/
static int
post_to_next()
{
	struct identityResp_Q_msg *idresp = (struct identityResp_Q_msg *)buf;
	struct UE_info *ue_entry = GET_UE_ENTRY(idresp->ue_idx);
	log_msg(LOG_ERROR, "Stich the fsm and pass this identity response to UE fsm. UE-%d.\n", idresp->ue_idx);
	return SUCCESS;
}

/**
* Thread exit function for future reference.
*/
void
shutdown_idRsp_stage()
{
	close_ipc_channel(g_Q_identityresp_fd);
	log_msg(LOG_INFO, "Shutdown Stage 3 handler \n");
	pthread_exit(NULL);
	return;
}

/**
* Thread function for stage.
*/
void*
identity_rsp_handler(void *data)
{
	init_stage();
	log_msg(LOG_INFO, "Stage 3 ready.\n");
    /* TODO :WE need to check these bitmaps */
	g_mme_hdlr_status <<= 1;
	g_mme_hdlr_status |= 1;
	check_mme_hdlr_status();

	while(1){
		read_next_msg();

		int ret = stage3_processing();

        if(ret == SUCCESS)
        {
		  post_to_next();
        }
	}

	return NULL;
}
