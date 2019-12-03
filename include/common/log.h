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

#ifndef __LOG_1_H_
#define __LOG_1_H_

#ifdef __cplusplus
extern "C"{
#endif

enum log_levels{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
    LOG_NEVER
};

void log_message(int l, const char *file, int line, const char *fmt, ...);
//#define log_msg(LOG_LEVEL, ARGS) set_log(#LOG_LEVEL, __FILE__, __LINE__, __VA_ARGS__)
#define log_msg(LOG_LEVEL, ...) log_message( LOG_LEVEL, __FILE__, __LINE__,  __VA_ARGS__)
//#define log_msg(LOG_LEVEL, ...) ;
void enable_logs();
void disable_logs();
void set_logging_level(char *level);

#ifdef __cplusplus
}
#endif

#endif /* __LOG_1_H_ */
