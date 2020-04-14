/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "thread_pool.h"
#include "tpool_queue.h"

/* allocates memory for node and initialize it */
static struct node *createnode(void *data)
{
	struct node *entry;

	entry = (struct node *)malloc(sizeof(struct node));
	if(entry == NULL) {
#ifdef DEBUG
		log_msg(LOG_ERROR, "failed to allocate memory\n");
#endif
		return NULL;
	}

	entry->data = data;
	entry->next = NULL;

	return entry;
}

/* push data to queue tail */
int queue_push_tail(struct Queue *queue, void *data)
{
	struct node *entry;

	if(queue == NULL)
		return -1;

	entry = createnode(data);
	if(entry == NULL) {
		return -ENOMEM;
	}

	/* For empty queue */
	if(queue->head == NULL)
		queue->head = entry;
	else
		queue->tail->next = entry;
	queue->tail = entry;

	/* atomic increment */
	__sync_fetch_and_add(&queue->length, 1);
	return 0;
}

/* removes head and return its data */
void *queue_pop_head(struct Queue *queue)
{
	void *data;
	struct node *entry;

	if(queue == NULL || queue->length == 0)
		return NULL;

	if(queue->head == NULL) {
		return NULL;
	}

	entry = queue->head;
	queue->head = queue->head->next;
	data = entry->data;
	/* atomic decrement */
	__sync_fetch_and_sub(&queue->length, 1);
	free(entry);

	return data;
}

int queue_get_length(struct Queue *queue)
{
	if (queue == NULL)
		return 0;

	return queue->length;
}

struct Queue *queue_new()
{
	struct Queue *queue;

	queue = (struct Queue *)malloc(sizeof(struct Queue));
	if(queue == NULL) {
#ifdef DEBUG
		log_msg(LOG_ERROR, "failed to allocate memory\n");
#endif
		return NULL;
	}

	queue->length = 0;
	queue->head = NULL;
	queue->tail = NULL;

	return queue;
}

void queue_destroy(struct Queue *queue, QueueDataFreeFunc function)
{
	struct node *tmp;

	if(queue == NULL || queue->length == 0)
	{
		free(queue);
		return;
	}

	if(queue->head == NULL)
		free(queue);
	else {
		tmp = queue->head;
		while(queue->head != NULL) {
			tmp = queue->head->next;
			if (function != NULL)
				function(queue->head->data);
			free(queue->head);
			queue->head=tmp;
		}
	}

}


