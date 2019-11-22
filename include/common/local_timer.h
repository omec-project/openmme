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

/* Timeout callback function signature */
typedef void (*cbf)(void *);

/* API to start timer. For now we are supporting timers only in seconds. ms timers can be 
 * added but does not seem to be requirement for now.
 * Callback data is completely transparent to timerlib. Timer lib never dereferrences the
 * content of it 
 * Return : keep the pointer safe. Dont mess it up. Its timer handle. Which is link list node 
 * as of now. But can be changed in future if performance becomes issue */

void* start_timer(unsigned int timeout, cbf callback, void *callback_data);

/* Pass the timer handle to stop the timer. Dont expect any callback once this event is
 * called. There is possibility of race condition, which can be handled if timerstop is called
 * at the same time when timer is expired.  */
int stop_timer(void *timer );

/* If app wish to check if timer is running and valid then it can call this API. */
int timer_running(void *timer);

/* One time activity. Can be called from any thread once. Typically main thread should initialize it 
 * before any thread calls any of the other timer APIs */

void init_timer_lib();

#endif
