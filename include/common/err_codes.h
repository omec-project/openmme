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

#ifndef ERROR_CODES_H_
#define ERROR_CODES_H_

/***
Common error codes across MME
*/

enum ERROR_CODES{
	SUCCESS = 0,
        SUCCESS_1 = 1, 
	/*Generic error codes 101-200*/
	E_FAIL = 101,
	E_FAIL_INIT, /*Failed in initialization*/
	E_ALLOC_FAILED,
	E_PARSING_FAILED,
    E_MAPPING_FAILED,

	/*S1AP error codes 201-300 */
	S1AP_AUTH_FAILED = 201,
	S1AP_SECMODE_FAILED,
	S1AP_IDENTITY_FAILED,

	/*S6a error codes 301-500*/
	S6A_AIA_FAILED = 301,
	S6A_FD_ERROR,
	S6A_FD_CORE_INIT_FAILED,
	S6A_FD_CORE_PARSECONF_FAILED,
	S6A_FD_CORE_START_FAILED,
	S6A_FD_GET_DICTVAL_FAILED,
	S6A_FD_DICTSRCH_FAILED,
};

#endif /* ERROR_CODES_H__*/
