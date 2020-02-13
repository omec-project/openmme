/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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

