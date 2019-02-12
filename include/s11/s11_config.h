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

#ifndef __S11_CONFIG_H_
#define __S11_CONFIG_H_

#include <stdbool.h>

typedef struct s11_config
{
	unsigned int sgw_ip;
	unsigned int pgw_ip;
	unsigned int egtp_def_port;
	unsigned int local_egtp_ip;
} s11_config;

void
init_parser(char *path);

int
parse_s11_conf();

#endif /*__S11_CONFIG_H*/
