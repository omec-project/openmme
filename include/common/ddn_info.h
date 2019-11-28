/*
 * Copyright (c) 2003-2019, Great Software Laboratory Pvt. Ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
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

#ifndef __DDN_INFO_H_
#define __DDN_INFO_H_

/*Reference - 29.274 - section 7.2.11*/
struct DDN_Q_msg {
	int ue_idx;
	unsigned char eps_bearer_identity;

	/*Allocation/retntion policy*/
	/*Paging and service informatin*/
};

#define S11_DDN_INFO_BUF_SIZE sizeof(struct DDN_Q_msg)

#endif /*_DDN_INFO_H_*/
