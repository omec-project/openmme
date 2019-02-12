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

#ifndef __DETACH_STAGE3_INFO_H_
#define __DETACH_STAGE3_INFO_H_

struct ctx_release_complete_Q_msg {
	int ue_idx;
};

#define S1AP_CTXRELRESP_STAGE3_BUF_SIZE sizeof(struct ctx_release_complete_Q_msg)

#endif /*__DETACH_STAGE3_INFO_H_*/
