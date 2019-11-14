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

#ifndef __STAGE1_SEC_H_
#define __STAGE1_SEC_H_

/* Common to HSS and MME */
#define AIA_RES_SIZE         8
#define AIA_AUTS_SIZE        14
#define AIA_AUTN_SIZE        16
#define AIA_RAND_SIZE        16
#define AIA_KASME_SIZE       32
#define AIA_NEXT_HOP_SIZE    32

#define HASH_SALT_LEN        7
#define HASH_KEY_LEN         512

#define NAS_INT_KEY_SIZE     16
#define KENB_SIZE            32
#define HMAC_SIZE            1024

typedef struct RAND {
	unsigned char len;
	unsigned char val[AIA_RAND_SIZE];
} RAND;

typedef struct XRES {
	unsigned char len;
	unsigned char val[AIA_RES_SIZE];
} XRES;

typedef struct AUTS {
	unsigned char len;
	unsigned char val[AIA_AUTS_SIZE];
} AUTS;

typedef struct AUTN {
	unsigned char len;
	unsigned char val[AIA_AUTN_SIZE];
} AUTN;

typedef struct KASME {
	unsigned char len;
	unsigned char val[AIA_KASME_SIZE];
} KASME;

/**
 * @brief Create integrity key
 * @param[in] kasme key
 * @param[out] int_key generated integrity key
 * @return void
 */
void create_integrity_key(unsigned char *kasme, unsigned char *int_key);

/**
 * @brief Create eNodeB key to exchange in init ctx message
 * @param [in]kasme key
 * @param [out]kenb_key output the generated key
 * @return void
 */
void create_kenb_key(unsigned char *kasme, unsigned char *kenb_key,
		unsigned int seq_no);


void calculate_hmac_sha256(const unsigned char *input_data,
	    int input_data_len, const unsigned char *key,
		int key_length, void *output, unsigned int *out_len);

#endif
