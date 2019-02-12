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

#include <string.h>
#include <stdint.h>

#include <openssl/x509.h>
#include <openssl/hmac.h>

#include "sec.h"

/**
 * @brief Create integrity key
 * @param[in] kasme key
 * @param[out] int_key generated integrity key
 * @return void
 */
void create_integrity_key(unsigned char *kasme, unsigned char *int_key)
{
	/*TODO : Handle appropriate security values in salt. Remove
	 * hardcoding*/
	uint8_t salt[HASH_SALT_LEN] = {
		0x15,
		0x02, /*sec algo code*/
		0,
		1,
		1,
		0,
		1
	};

	unsigned char out_key[HMAC_SIZE] = {0};
	unsigned int out_len = 0;
	calculate_hmac_sha256(salt, HASH_SALT_LEN, kasme, AIA_KASME_SIZE, out_key, &out_len);

	memcpy(int_key, &out_key[AIA_KASME_SIZE - NAS_INT_KEY_SIZE],
			NAS_INT_KEY_SIZE);
}

/**
 * @brief Create eNodeB key to exchange in init ctx message
 * @param [in]kasme key
 * @param [out]kenb_key output the generated key
 * @return void
 */
void create_kenb_key(unsigned char *kasme, unsigned char *kenb_key,
		unsigned int seq_no)
{
	uint8_t salt[HASH_SALT_LEN] = {
		0x11, /*TODO : Sec algo. handle properly instead of harcoding here*/
		(seq_no >> 24) & 0xFF, /*Byte 1 of seq no*/
		(seq_no >> 16) & 0xFF, /*Byte 2 of seq no*/
		(seq_no >> 8 ) & 0xFF, /*Byte 3 of seq no*/
		(seq_no      ) & 0xFF, /*Byte 4 of seq no*/
		0x00,
		0x04
	};

	uint8_t out_key[HMAC_SIZE];
	unsigned int out_len = 0;
	calculate_hmac_sha256(salt, HASH_SALT_LEN, kasme, AIA_KASME_SIZE, out_key, &out_len);
	memcpy(kenb_key, out_key, KENB_SIZE);

}


/**
* @brief Create MAC(message authentication code)
* @param [in]input data and  key
* @param [out]output MAC, out_len size of MAC
* @return void
*/


void calculate_hmac_sha256(const unsigned char *input_data,
				int input_data_len, const unsigned char *key,
				int key_length, void *output, unsigned int *out_len)
{

	unsigned int mac_length = 0;
	unsigned char mac_buffer[EVP_MAX_MD_SIZE] = {0};
	HMAC(EVP_sha256(), key, key_length, input_data, input_data_len, mac_buffer, &mac_length);
	memcpy(output, mac_buffer, mac_length);
	*out_len = mac_length;

}
