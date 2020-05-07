/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * main.h
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <time.h>
#include <stdint.h>

#include "stimer.h"

#define THREADPOOL_SIZE 10

#define SCTP_BUF_SIZE 1024

/*Timer and stat calculations*/
struct time_stat {
	stimer_t init_ue;
	stimer_t esm_in;
	stimer_t esm_out;
	stimer_t auth_in;
	stimer_t auth_to_mme;
	stimer_t secreq_in;
	stimer_t secreq_out;
	stimer_t secresp_in;
	stimer_t secresp_to_mme;
	stimer_t esmreq_in;
	stimer_t esmreq_out;
	stimer_t espresp_in;
	stimer_t espresp_to_mme;
	stimer_t initctx_out;
	stimer_t initctx_resp;
	stimer_t att_done;
};

void
*authreq_handler(void *);

void
*secreq_handler(void *);

void
*esmreq_handler(void *);

void
*icsreq_handler(void *);

void
*detach_accept_handler(void *);

void
*s1ap_reject_handler(void *);

void 
*s1ap_attach_id_req_handler(void *);

void 
*tau_response_handler (void *);

void
*emm_info_req_handler(void *);

void
*gen_reset_request_handler(void *);

void
*paging_handler(void *);

void
*mme_to_s1ap_msg_handler(void *);

void
calculate_mac(uint8_t *int_key, uint32_t seq_no, uint8_t direction,
		uint8_t bearer, uint8_t *data, uint16_t data_len,
		uint8_t *mac);

typedef long long int stimer_t;

#define STIMER_GET_CURRENT_TP(__now__)                                                 \
	({                                                                                     \
	    struct timespec __ts__;                                                             \
	    __now__ = clock_gettime(CLOCK_REALTIME,&__ts__) ?                                   \
	          -1 : (((stimer_t)__ts__.tv_sec) * 1000000000) + ((stimer_t)__ts__.tv_nsec);   \
	    __now__;                                                                            \
	 })

#define STIMER_GET_ELAPSED_NS(_start_)                                                 \
	({                                                                                     \
	    stimer_t __ns__;                                                                    \
	    STIMER_GET_CURRENT_TP(__ns__);                                                      \
	    if (__ns__ != -1)                                                                   \
	       __ns__ -= _start_;                                                               \
	    __ns__;                                                                             \
	 })

#endif /* MAIN_H_ */
