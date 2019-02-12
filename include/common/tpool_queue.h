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

#ifndef __TPOOL_QUEUE_H
#define __TPOOL_QUEUE_H

struct node {
	void *data;
	struct node *next;
};

struct Queue {
	int length;
	struct node *head;
	struct node *tail;
};

struct thread_pool {
	struct Queue *thread_queue;	/* queue to store thread ids */
	struct Queue *job_queue;	/* for storing jobs */

	pthread_mutex_t queue_mutex;	/* protection to job_queue */
	pthread_cond_t job_received;	/* synchronisation with worker threads */
	
	pthread_t dispatch_thread;	/* signals threads if new work in job_queue*/

	int idle_threads;		/* count of idle threads */
};

struct Job {
	JobFunction function;
	void *arg;
};

struct Queue;

typedef void (* QueueDataFreeFunc)(void *data);

extern struct Queue *queue_new();
extern void queue_destroy(struct Queue *queue, QueueDataFreeFunc function);

extern int queue_push_tail(struct Queue *queue, void *data);
extern void *queue_pop_head(struct Queue *queue);
extern int queue_get_length(struct Queue *queue);

#endif

