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

#ifndef __SERVICEREQ_INFO_H_
#define __SERVICEREQ_INFO_H_

#include "err_codes.h"
#include "s1ap_structs.h"
#include "s1ap_ie.h"



struct service_req_Q_msg {
	int ue_idx;
	int s1ap_enb_ue_id;
	int enb_fd;
	unsigned int ksi;
	unsigned int seq_no;
	unsigned short mac;
	struct TAI tai;
	struct CGI utran_cgi;
	struct STMSI s_tmsi;
};

#define S1AP_SERVICEREQ_BUF_SIZE sizeof(struct service_req_Q_msg)


#endif /*__SERVICEREQ_INFO_H_*/
