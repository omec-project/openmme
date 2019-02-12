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

#ifndef __THREAD_POOL_H
#define __THREAD_POOL_H

#ifdef __cplusplus
extern "C"{
#endif

struct thread_pool;
typedef void (* JobFunction) (void *);

/*
 * Creates new thread pool
 * on success return pointer to thread_pool
 * on failure return NULL
 */
extern struct thread_pool *thread_pool_new(int count);

/*
 * Stops all threads and
 * destroy the thread pool
 * on success return 0
 * on failure return -1
 */
extern int thread_pool_destroy(struct thread_pool *pool);

/*
 * Queues the job to thread pool
 * idle threads will pick the job
 * on success it return 0
 * on failure returns -ve values
 */
extern int insert_job(struct thread_pool *pool, JobFunction function,
		void *userdata);

#ifdef __cplusplus
}
#endif

#endif

