/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
