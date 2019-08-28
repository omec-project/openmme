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

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "prime.h"
#include "err_codes.h"
#include "hashtable.h"

static onf_ht_item ONF_HT_DELETED_ITEM = {0,0,NULL, NULL};

/*****************************************
Name:  onf_ht_new_item
brief: Create new hash item
return: onf_ht_item
*****************************************/
onf_ht_item* onf_ht_new_item(
     int k_len, int v_len, 
     const char* k, const char* v) 
{
    onf_ht_item* i = malloc(sizeof(onf_ht_item));
    if(NULL == i)
    {
       return NULL; 
    }

    i->key_len = k_len;
    i->val_len = v_len;
    i->key = (char*)malloc(k_len);
    if(NULL == i->key)
    {
       free(i);
       return NULL;
    }
    memcpy(i->key, k, k_len);
    i->value = (char*)malloc(v_len);
    if(NULL == i->value)
    {
       free(i->key);
       free(i);
       return NULL;
    }
    memcpy(i->value, v, v_len);
    return i;
}

/*****************************************
Name:  onf_ht_new
brief: Create new hash table
return: onf_ht_hash_table
*****************************************/
onf_ht_hash_table* onf_ht_new() {
    return onf_ht_new_sized(ONF_HT_INITIAL_BASE_SIZE);
}


/*****************************************
Name:  onf_ht_new_sized
brief: Create new hash table with new size
return: onf_ht_hash_table
*****************************************/
onf_ht_hash_table* onf_ht_new_sized(const int base_size) {
    onf_ht_hash_table* ht = malloc(sizeof(onf_ht_hash_table));
    if(NULL == ht)
    {
        return NULL;
    }

    ht->base_size = base_size;
    ht->size = onf_next_prime(ht->base_size);

    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(onf_ht_item*));
    if(NULL == ht->items)
    {
        free(ht);
	return NULL;
    }

    return ht;
}

/*****************************************
Name:  onf_ht_resize
brief: resize hash table with new size
return: 
*****************************************/
int onf_ht_resize(
         onf_ht_hash_table* ht, const int base_size) 
{
    if (base_size < ONF_HT_INITIAL_BASE_SIZE) {
        return E_FAIL;
    }

    onf_ht_hash_table* new_ht = onf_ht_new_sized(base_size);
    if(NULL == new_ht)
    {
        return E_ALLOC_FAILED;
    }

    for (int i = 0; i < ht->size; i++) {
        onf_ht_item* item = ht->items[i];
        if (item != NULL && item != &ONF_HT_DELETED_ITEM) {
            if(SUCCESS != onf_ht_insert(new_ht, item->key_len,
	      item->val_len, item->key, item->value))
	    {
                onf_ht_del_hash_table(new_ht);
	        return E_FAIL;
	    }
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // To delete new_ht, we give it ht's size and items 
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    onf_ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    onf_ht_del_hash_table(new_ht);
    return SUCCESS;
}

/*****************************************
Name:  onf_ht_resize_up
brief: resize up 
return: 
*****************************************/
int onf_ht_resize_up(onf_ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    return onf_ht_resize(ht, new_size);
}

/*****************************************
Name:  onf_ht_resize_down
brief: resize down
return: 
*****************************************/
int onf_ht_resize_down(onf_ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    return onf_ht_resize(ht, new_size);
}

/*****************************************
Name:  onf_ht_del_item
brief: delete hash item
return: 
*****************************************/
void onf_ht_del_item(onf_ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

/*****************************************
Name:  onf_ht_del_hash_table
brief: delete hash table
return: 
*****************************************/
void onf_ht_del_hash_table(onf_ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        onf_ht_item* item = ht->items[i];
        if (item != NULL) {
            onf_ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}

/*****************************************
Name:  onf_ht_hash
brief: Calculate hash value.
return: 
*****************************************/
int onf_ht_hash(
      const char* s, int len_s, const int a, const int m) 
{
    long hash = 0;
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

/*****************************************
Name:  onf_ht_get_hash
brief: get hash table index from key
return: 
*****************************************/
int onf_ht_get_hash(
    const char* s, int key_len, 
    const int num_buckets, const int attempt) 
{
    const int hash_a = onf_ht_hash(
                        s, key_len, ONF_HT_PRIME_1, num_buckets);
    const int hash_b = onf_ht_hash(
                        s, key_len, ONF_HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

/*****************************************
Name:  onf_ht_insert
brief: insert into hash table
return: 
*****************************************/
int onf_ht_insert(
      onf_ht_hash_table* ht, int key_len,  
      int val_len, const char* key, const char* value) 
{
    const int load = (ht->count * 100) / ht->size;
    if (load > 70) {
        if(SUCCESS != onf_ht_resize_up(ht))
	{
	    return E_FAIL;
	}
    }
    onf_ht_item* item = onf_ht_new_item(
                         key_len, val_len,key, value);
    if(NULL == item)
    {
       return E_ALLOC_FAILED;
    }
    int index = onf_ht_get_hash(item->key, 
                   item->key_len,ht->size, 0);
    onf_ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
        if(cur_item != &ONF_HT_DELETED_ITEM) {
            if (onf_key_compare(
	          cur_item->key_len, key_len,
		      cur_item->key, key)) {
                onf_ht_del_item(cur_item);
                ht->items[index] = item;
                return SUCCESS;
            }
            else
            {
		index = onf_ht_get_hash(item->key, 
		           item->key_len, ht->size, i);
		cur_item = ht->items[index];
		i++;
            }
        }
    } 
    ht->items[index] = item;
    ht->count++;
    return SUCCESS;
}

/*****************************************
Name:  onf_htsearch
brief: search key in hash table
return: 
*****************************************/
char* onf_ht_search(onf_ht_hash_table* ht, const char* key, int key_len) {
    int index = onf_ht_get_hash(key, key_len, ht->size, 0);
    onf_ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if(item != &ONF_HT_DELETED_ITEM) {
            if (onf_key_compare(
	          item->key_len, key_len, item->key, key)) 
            {
                return item->value;
            }
        }
        index = onf_ht_get_hash(key, key_len, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    return NULL;
}

/*****************************************
Name:  onf_ht_delete
brief: delete from hash table
return: 
*****************************************/
int onf_ht_delete(
        onf_ht_hash_table* ht, 
	const char* key, int key_len) 
{
    const int load = (ht->count * 100) / ht->size;
    if (load <= 10) {
        if(SUCCESS != onf_ht_resize_down(ht))
	{
	    return E_FAIL;
	}
    }
    int index = onf_ht_get_hash(key, key_len, ht->size, 0);
    onf_ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &ONF_HT_DELETED_ITEM) {
            if (onf_key_compare(
	          item->key_len, key_len, item->key, key))
	    {
                onf_ht_del_item(item);
                ht->items[index] = &ONF_HT_DELETED_ITEM;
		break;
            }
        }
        index = onf_ht_get_hash(key, key_len, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    ht->count--;
    return SUCCESS;
}

/*****************************************
Name:  onf_key_compare
brief: compare keys hash table
return: 
*****************************************/
bool onf_key_compare(
               int k_len, int key_len, 
	       const char* k, const char* key)
{
    if((k_len != key_len) || 
         (memcmp(k, key, key_len) != 0))
    {
        return false;
    }

    return true;
}
