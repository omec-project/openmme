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
#include <unistd.h>

#include "ue_table.h"
#include "log.h"


int g_index_list_queue[UE_POOL_CNT+1];

/*Counter UE list. Add each element sequentially when UE attaches*/
int g_UE_cnt = 0;
int g_out_index= 0;
int g_in_index = 1;

/* @get_index_from_list.
 * Input :
 * Output: Get the index of the detached UE from the list.
 */

int allocate_ue_index()
{
  int index = ++g_UE_cnt;
  if (index%UE_POOL_CNT == 0) {
  
  	log_msg(LOG_INFO, "UE Buffer Pool is full \n");
  	g_UE_cnt--;
  	index = get_index_from_list();
  
  	if (index != -1) {
  		log_msg(LOG_INFO, "Index is  received from the list\n");
  	} else {
  		log_msg(LOG_ERROR, "Error: No Index found in the list \n");
  	}
  
  }
  return index;
}


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

/**
 * @brief convert binary imsi to string imsi
 * Binary imsi is stored in 8 bytes, each nibble representing each imsi char.
 * char imsi stroes each char in 1 byte.
 * @param[in] b_imsi : Binary imsi
 * @param[out] s_imsi : Converted string imsi
 * @return void
 */
void
imsi_bin_to_str(unsigned char *b_imsi, char *s_imsi)
{
	if(NULL == b_imsi || NULL == s_imsi) return;
       
	memset(s_imsi, 0, STR_IMSI_LEN);

	/* Byte 'AB' in b_imsi, is converted to two bytes 'A', 'B' in s_imsi*/
	s_imsi[0] = '0' + ((b_imsi[0]>>4) & 0x0F);

	for(int i=1; i < BINARY_IMSI_LEN; ++i) {
		s_imsi[(i*2)-1] = '0' + (b_imsi[i] & 0x0F);
		s_imsi[(i*2)] = '0' + ((b_imsi[i]>>4) & 0x0F);
	}
	s_imsi[(BINARY_IMSI_LEN*2)-1] = '\0';
}

