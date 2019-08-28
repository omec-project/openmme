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
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>

#include "log.h"
#include "options.h"
#include "hashtable.h"
#include "s1ap_structs.h"
#include "sctp_conn.h"

extern onf_ht_hash_table* g_enbfd_hash_table;
extern pthread_mutex_t s1ap_hashtable_lock;

void parse_args(int argc, char **argv)
{
	int args_set = 0;
	int c = 0;

	const struct option long_options[] = {
	  {"config_file",  required_argument, NULL, 'f'},
	  {0, 0, 0, 0}
	};

	do {
		int option_index = 0;

		c = getopt_long(argc, argv, "f:", long_options,
				&option_index);

		if (c == -1)
			break;

		switch (c) {
		case 'f':
			break;
		default:
			log_msg(LOG_ERROR, "Unknown argument - %s.", argv[optind]);
			exit(0);
		}
	} while (c != -1);

	if ((args_set & REQ_ARGS) != REQ_ARGS) {
		log_msg(LOG_ERROR, "Usage: %s\n", argv[0]);
		for (c = 0; long_options[c].name; ++c) {
			log_msg(LOG_ERROR, "\t[ -%s | -%c ] %s\n",
					long_options[c].name,
					long_options[c].val,
					long_options[c].name);
		}
		exit(0);
	}
}

/**
* Post sctp message with streamid
*/
int
send_sctp_msg_upd(int enb_fd, unsigned char *buffer, size_t len)
{
        int send_streamId = 0;
        pthread_mutex_lock(&s1ap_hashtable_lock);
	struct enb_assoc_info* enbAssoc
	     = (struct enb_assoc_info*)onf_ht_search(
	         g_enbfd_hash_table, 
		 (const char*)&enb_fd, sizeof(int));
        pthread_mutex_unlock(&s1ap_hashtable_lock);
        if(NULL == enbAssoc)
	{
	    log_msg(LOG_ERROR, "No entry found in hash table for enbfd %d", enb_fd);
	}
	else
	{
	    send_streamId = enbAssoc->outStreamId;
        }

	return send_sctp_req_msg(
	           enb_fd, send_streamId, buffer, len);
}

