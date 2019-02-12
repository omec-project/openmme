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
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include "thread_pool.h"
#include "tpool_queue.h"

struct Job *create_job(JobFunction function, void *arg)
{
	struct Job *job;
	job = (struct Job *)malloc(sizeof(struct Job));
	if(job == NULL) {
#ifdef DEBUG
		log_msg(LOG_ERROR, "failed to allocate memory\n");
#endif
		return NULL;
	}
	job->function = function;
	job->arg = arg;
	return job;
}

static void *worker_thread(void *userdata)
{
	void *arg;
	struct Job *job;
	JobFunction function;
	struct thread_pool *pool;

	pool = (struct thread_pool *)userdata;

	while(1) {
		pthread_mutex_lock(&pool->queue_mutex);

		/* waiting until dispatch thread signals for new job */
		pthread_cond_wait(&pool->job_received, &pool->queue_mutex);
		job = queue_pop_head(pool->job_queue);
		pthread_mutex_unlock(&pool->queue_mutex);

		if(job != NULL) {
			function = job->function;
			arg = job->arg;
			free(job);

			/* atomically updating idle_threads */
			__sync_fetch_and_sub(&pool->idle_threads, 1);

			function(arg);

			__sync_fetch_and_add(&pool->idle_threads, 1);
		}
	}
	return NULL;
}

/* If queue has pending jobs and 
 * thread is idle then signal the thread
 * to process the job
 */
static void *dispatch_if_idle(void *userdata)
{
	struct thread_pool *pool;

	pool = (struct thread_pool *)userdata;

	while(1) {
		if((pool->idle_threads > 0) &&
			pool->job_queue->length > 0 ) {
			pthread_cond_signal(&pool->job_received);
		} else usleep(10);
	}
	return NULL;
}

/* creates a thread and pushes into queue */
static int spawn_thread(struct thread_pool *pool)
{
	int status;
	pthread_t thread;

	status = pthread_create(&thread, NULL, worker_thread, pool);
	if(status < 0)
		return status;

	queue_push_tail(pool->thread_queue, &thread);

	return 0;
}

/* pushes job into queue */
int insert_job(struct thread_pool *pool, JobFunction function, void *userdata)
{
	struct Job *job;
	
	if(pool == NULL)
		return -1;

	job = create_job(function, userdata);
	if(job == NULL)
		return -ENOMEM;

	pthread_mutex_lock(&pool->queue_mutex);
	queue_push_tail(pool->job_queue, job);
	pthread_mutex_unlock(&pool->queue_mutex);

	return 0;
}

struct thread_pool *thread_pool_new(int count)
{
	int i, status;
	pthread_t thread;
	struct thread_pool *pool;

	pool = (struct thread_pool *)malloc(sizeof(struct thread_pool));
	if(pool == NULL) {
#ifdef DEBUG
		log_msg(LOG_ERROR, "failed to allocate memory\n");
#endif
		errno = ENOMEM;
		return NULL;
	}
	pool->idle_threads = count;
	pool->job_queue = queue_new();
	pool->thread_queue = queue_new();

	pthread_mutex_init(&pool->queue_mutex, NULL);
	pthread_cond_init(&pool->job_received, NULL);

	status = pthread_create(&thread, NULL, dispatch_if_idle, pool);
	if(status < 0) {
#ifdef DEBUG
		log_msg(LOG_ERROR, "failed to spawn dispatch thread, stopping\n");
#endif
		return NULL;
	}
	pool->dispatch_thread = thread;

	i = 0;
	while(i < count)
		if (spawn_thread(pool) == 0)
			i++;

	return pool;
}

int thread_pool_destroy(struct thread_pool *pool)
{
	pthread_t *thread;

	if(pool == NULL)
		return -1;

	pthread_cancel(pool->dispatch_thread);
	while((thread = queue_pop_head(pool->job_queue)) != NULL) {
		pthread_cancel(*thread);	
	}

	queue_destroy(pool->job_queue, free);
	queue_destroy(pool->thread_queue, NULL);
	pthread_mutex_destroy(&pool->queue_mutex);
	pthread_cond_destroy(&pool->job_received);

	free(pool);
	return 0;
}


