/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
*/


#include <stdio.h>

#include "ue_table.h"
#include "log.h"


int g_index_list_queue[UE_POOL_CNT+1];

int g_out_index= 0;
int g_in_index = 1;

/* @get_index_from_list.
 * Input :
 * Output: Get the index of the detached UE from the list.
 */


int get_index_from_list()
{
	++g_out_index;

	if ((g_out_index %= (UE_POOL_CNT+1)) == (g_in_index %= (UE_POOL_CNT+1))) {
		g_out_index--;
		log_msg(LOG_INFO,"List is Empty\n");
		return -1;
	}

	return g_index_list_queue[g_out_index %= (UE_POOL_CNT+1)];
}


/* @insert_index_into_list
 * Input : Index Number of the detached UE from the Pool.
 * Output: Return -1 if list is full else add the detached index number
 *         to the list .
 */

int insert_index_into_list(int index)
{
	if ((g_in_index %= (UE_POOL_CNT+1)) == (g_out_index %= (UE_POOL_CNT+1))) {
		log_msg(LOG_INFO, "LIST is FULL\n");
		return -1;
	}
	g_index_list_queue[g_in_index++] = index;
	return 0;
}

