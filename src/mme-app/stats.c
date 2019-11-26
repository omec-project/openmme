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
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <log.h>

pthread_t thread_id;

uint32_t attach_stage1_counter = 0;
uint32_t attach_stage2_counter = 0;
uint32_t attach_stage3_counter = 0;
uint32_t attach_stage4_counter = 0;
uint32_t attach_stage5_counter = 0;
uint32_t attach_stage6_counter = 0;
uint32_t attach_stage7_counter = 0;
uint32_t attach_stage8_counter = 0;

uint32_t detach_stage1_counter = 0;
uint32_t detach_stage2_counter = 0;
uint32_t detach_stage3_counter = 0;


void* stat_report(void *data)
{
	while(1)  {
#if 0
// want to disable stats for time being..Its taking all log space

		printf("\033[H\033[J");

		printf("Atch_Stg1       Atch_Stg2       Atch_Stg3       Atch_Stg4       Atch_Stg5       Atch_Stg6       Atch_Stg7       Atch_Stg8\n\n");

		printf("%8u        %8u        %8u        %8u        %8u        %8u        %8u        %8u\n\n",
		attach_stage1_counter,attach_stage2_counter, \
		attach_stage3_counter,attach_stage4_counter,attach_stage5_counter, \
		attach_stage6_counter,attach_stage7_counter,attach_stage8_counter);


		printf("Dtch_Stg1       Dtch_Stg2       Dtch_Stg3\n\n");
		printf("%8u        %8u        %8u\n",detach_stage1_counter,detach_stage2_counter,detach_stage3_counter);
#endif
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
