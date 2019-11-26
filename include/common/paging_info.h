/*
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
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

#ifndef __PAGING_INFO_H_
#define __PAGING_INFO_H_

struct paging_Q_msg {
	int ue_idx;
	unsigned char IMSI[BINARY_IMSI_LEN];
	struct TAI tai;
};

#define S1AP_PAGING_INFO_BUF_SIZE sizeof(struct paging_Q_msg)

#endif /*_PAGING_INFO_H_*/
