/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <log.h>
#include "ue_table.h"

pthread_t thread_id;

uint32_t attach_stage1_counter = 0;
uint32_t attach_stage2_counter = 0;
uint32_t attach_stage3_counter = 0;
uint32_t attach_stage4_counter = 0;
uint32_t attach_stage5_counter = 0;
uint32_t attach_stage6_counter = 0;
uint32_t attach_stage7_counter = 0;
uint32_t attach_stage8_counter = 0;
uint32_t attach_reject_counter = 0;
uint32_t attach_identity_req_counter = 0;
uint32_t attach_identity_rsp_counter = 0;

uint32_t detach_stage1_counter = 0;
uint32_t detach_stage2_counter = 0;
uint32_t detach_stage3_counter = 0;

uint32_t paging_counter = 0;


uint32_t tau_req_counter;
uint32_t tau_response_accept_counter;
uint32_t tau_response_reject_counter;

void* stat_report(void *data)
{
	while(0)  {

		printf("\033[H\033[J");

		printf("Atch_Stg1       Atch_Stg2       Atch_Stg3       Atch_Stg4       Atch_Stg5       Atch_Stg6       Atch_Stg7       Atch_Stg8\n\n");

		printf("%8u        %8u        %8u        %8u        %8u        %8u        %8u        %8u\n\n",
		attach_stage1_counter,attach_stage2_counter, \
		attach_stage3_counter,attach_stage4_counter,attach_stage5_counter, \
		attach_stage6_counter,attach_stage7_counter,attach_stage8_counter);


		printf("Dtch_Stg1       Dtch_Stg2       Dtch_Stg3\n\n");
		printf("%8u        %8u        %8u\n",detach_stage1_counter,detach_stage2_counter,detach_stage3_counter);
		printf("paging\n\n");
		printf("%8u\n",paging_counter);
		printf("Identification Request %u Identification Response %u Attach Reject %u\n\n", attach_identity_req_counter, attach_identity_rsp_counter, attach_reject_counter);
		sleep(3);
	}

	return NULL;
}


void stat_init()
{
	int  ret = 0;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	/* set the thread detach state */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	ret = pthread_create(&thread_id, &attr, &stat_report, NULL);
	if(ret <0) {
		log_msg(LOG_ERROR,"Stats Thread Creation Failed\n");
		exit(-1);
	}
	pthread_attr_destroy(&attr);
}
