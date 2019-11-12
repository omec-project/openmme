/*
* Copyright 2019-present Open Networking Foundation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#ifndef __LOCAL_TIMER_H__
#define __LOCAL_TIMER_H__
typedef void (*cbf)(void *);

void* start_timer(unsigned int timeout, cbf callback, void *callback_data);
int stop_timer(void *timer );
int timer_running(void *timer);
void init_timer_lib();

#endif
