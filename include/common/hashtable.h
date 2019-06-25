/*
 * Copyright (c) 2003-2019, Great Software Laboratory Pvt. Ltd.
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

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "stdbool.h"
#define ONF_HT_PRIME_1 151
#define ONF_HT_PRIME_2 163
#define ONF_HT_INITIAL_BASE_SIZE 53

typedef struct {
	int key_len;
	int val_len;
	char* key;
	char* value;
} onf_ht_item;

typedef struct {
    int base_size;
    int size;
    int count;
    onf_ht_item** items;
} onf_ht_hash_table;

int         onf_ht_insert(
               onf_ht_hash_table* ht, int k_len, int v_len, 
	       const char* key, const char* value);
bool        onf_key_compare(
               int k_len, int key_len, 
	       const char* k, const char* key);
char*       onf_ht_search(onf_ht_hash_table* ht, 
                   const char* key, int key_len);
int         onf_ht_delete(onf_ht_hash_table* h, 
                   const char* key, int key_len);
int         onf_ht_hash(const char* s, int len_s, 
                          const int a, const int m);
int         onf_ht_get_hash(
               const char* s, int key_len,
	       const int num_buckets, const int attempt);
void        onf_ht_del_item(onf_ht_item* i);
void        onf_ht_del_hash_table(onf_ht_hash_table* ht);
onf_ht_hash_table*        onf_ht_new();
onf_ht_item*       onf_ht_new_item(int k_len, int s_len,
                             const char* k, const char* v);
onf_ht_hash_table* onf_ht_new_sized(const int base_size);
int onf_ht_resize(
            onf_ht_hash_table* ht, const int base_size);
int onf_ht_resize_up(onf_ht_hash_table* ht);
int onf_ht_resize_down(onf_ht_hash_table* ht);

#endif /* HASHTABLE_H__*/
