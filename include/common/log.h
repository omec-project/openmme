/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
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
void init_backtrace(char *binary);

#ifdef __cplusplus
}
#endif

#endif /* __LOG_1_H_ */
