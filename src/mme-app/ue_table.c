/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "pthread.h"

#include "ue_table.h"
#include "log.h"


/*List of UEs attached to MME*/
struct UE_info* g_UE_list[UE_POOL_SIZE];
int g_index_list_queue[UE_POOL_CNT+1];
int g_tmsi_allocation_array[TMSI_POOL_SIZE];
struct UE_info *ue_list_head = NULL;

/* Mutex to lock ue_list */
pthread_mutex_t ue_link_list_mutex;

/*Counter UE list. Add each element sequentially when UE attaches*/
int g_UE_cnt = 0;
int g_total_UE_count=0;
int g_out_index= 0;
int g_in_index = 1;

/* @get_index_from_list.
 * Input :
 * Output: Get the index of the detached UE from the list.
 */

int allocate_ue_index()
{
  int index =  ++g_UE_cnt;
  g_total_UE_count++;

  if (index%UE_POOL_CNT == 0) {
  
  	log_msg(LOG_INFO, "UE Buffer Pool is full \n");
  	index = get_index_from_list();
    g_UE_cnt--; 
  	if (index != -1) {
  		log_msg(LOG_INFO, "Index is  received from the list\n");
  	} else {
  		log_msg(LOG_ERROR, "Error: No Index found in the list \n");
        g_total_UE_count--;
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
  	if(g_total_UE_count)
    {
        g_total_UE_count--;
    }
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

void init_ue_tables()
{
    pthread_mutex_init(&ue_link_list_mutex, NULL);
	/* init UEs arra to 65535 initially */
	g_UE_list[0] = (struct UE_info*)calloc(sizeof(struct UE_info), UE_POOL_CNT);
	if(NULL == g_UE_list[0]) {
		log_msg(LOG_ERROR, "Allocation failed.\n");
		exit(-1);
	}
    ue_list_head = g_UE_list[0];
/*
	g_UE_list[1] = (struct UE_info*)calloc(sizeof(struct UE_info), UE_POOL_CNT);
	if(NULL == g_UE_list[1]) {
		log_msg(LOG_ERROR, "Allocation failed.\n");
		exit(-1);
	}
	g_UE_list[2] = (struct UE_info*)calloc(sizeof(struct UE_info), UE_POOL_CNT);
	if(NULL == g_UE_list[2]) {
		log_msg(LOG_ERROR, "Allocation failed.\n");
		exit(-1);
	}
*/
    for(int i=0;i<TMSI_POOL_SIZE;i++)
        g_tmsi_allocation_array[i] = -1;
}

void add_ue_entry(struct UE_info *ue_entry)
{
   pthread_mutex_lock(&ue_link_list_mutex);
   ue_entry->next_ue = ue_list_head; 
   ue_list_head = ue_entry;
   pthread_mutex_unlock(&ue_link_list_mutex);
   char imsi[16] = {'\0'}; 
   imsi_bin_to_str(ue_entry->IMSI, imsi);
   log_msg(LOG_INFO, "Adding IMSI = %s in the active UE list \n", imsi);
   return; 
}

/* Mark UE invalid, release UE index and release TMSI assigned to UE */
void release_ue_entry(struct UE_info *ue_entry)
{
    struct UE_info **indirect;

    /* Critical Section to manage link list */
    pthread_mutex_lock(&ue_link_list_mutex);

    indirect = &ue_list_head;
    while((*indirect) != ue_entry)
    {
        indirect = &(*indirect)->next_ue;
        if(*indirect == NULL)
        {
           pthread_mutex_unlock(&ue_link_list_mutex);
           return;
        }
    }
    *indirect = ue_entry->next_ue;
    pthread_mutex_unlock(&ue_link_list_mutex);

    ue_entry->ue_state = UNASSIGNED_ENTRY;
    ue_entry->magic = UE_INFO_INVALID_MAGIC;
    ue_entry->next_ue = NULL;

    /* Mark tmsi free */
    g_tmsi_allocation_array[ue_entry->m_tmsi] = -1;

    /* add UE to to Pool which can be used later */
    int ret = insert_index_into_list(ue_entry->ue_index);
    if (ret == -1) {
        log_msg(LOG_INFO, "List is full. More indexes cannot be added\n");
    } else {
        log_msg(LOG_INFO, "Index with %d is added to list\n",ue_entry->ue_index);
    }
}

// on success return > 0 tmsi
// on error return -1. Should never fail under fair reasonale UE load  
// TODO : area of improvement 
int allocate_tmsi(struct UE_info *ue_entry)
{
    int32_t tmsi;
    while(1)
    {
      tmsi = rand() % TMSI_POOL_SIZE;
      if(g_tmsi_allocation_array[tmsi] == -1)
      {
        g_tmsi_allocation_array[tmsi] = ue_entry->ue_index; 
        ue_entry->m_tmsi = tmsi;
        break; // Successfully allocated 
      }
      // continue..select new 
    }
    return tmsi;
}

inline int get_ue_index_from_tmsi(int tmsi)
{
  // if TMSI is out of range or if TMSI is unallocated ( -1) then return error 
  if((tmsi > TMSI_POOL_SIZE) || (g_tmsi_allocation_array[tmsi] ==  -1))
    return -1; 

  return g_tmsi_allocation_array[tmsi];
 
}

void print_current_active_ue_info()
{
    struct UE_info *temp;
    int count=1;
    for(temp = ue_list_head; temp != NULL && IS_VALID_UE_INFO(temp); temp = temp->next_ue, count++)
    {
      char imsi[16] = {'\0'}; 
      imsi_bin_to_str(temp->IMSI, imsi);
      log_msg(LOG_INFO, "(%d) - IMSI = %s \n", count, imsi);
    } 
    return;
}
