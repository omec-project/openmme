/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "log.h"
#include "hss_message.h"
#include "s6a.h"

/**Global and externs **/

/*Handle all messages coming from in built perf hss*/
void
hss_resp_handler(void *message)
{
	struct hss_resp_msg *msg = (struct hss_resp_msg*)message;

	log_msg(LOG_INFO, "HSS response msg handler for ue_idx %d\n",
			msg->ue_idx);

	switch(msg->hdr){
	case HSS_AIA_MSG:
		handle_perf_hss_aia(msg->ue_idx,
				(struct hss_aia_msg *)&(msg->data.aia));
		break;

	case HSS_ULA_MSG:
		handle_perf_hss_ula(msg->ue_idx,
				(struct hss_ula_msg *)&(msg->data.ula));
		break;

	case HSS_PURGE_RESP_MSG:
		handle_perf_hss_purge_resp(msg->ue_idx);
		break;

	default:
		log_msg(LOG_ERROR, "Unknown message received from HSS - %d\n",
			msg->hdr);
	}
	return;

	/*free allocated message buffer*/
	free(message);
}
