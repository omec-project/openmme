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


