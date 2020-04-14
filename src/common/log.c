/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "log.h"
bool g_nolog = false;
enum log_levels g_log_level = LOG_DEBUG;

static const char *log_level_name[] = { "DEBUG", "INFO", "WARN", "ERROR" };

inline void enable_logs()
{
    g_nolog = false;
}

inline void disable_logs()
{
    g_nolog = true;
}

void set_logging_level(char *log_level)
{
    if(strcmp(log_level, "debug") == 0)
    {
        g_log_level = LOG_DEBUG;
        enable_logs();
    }
    else if(strcmp(log_level, "info") == 0)
    {
        g_log_level = LOG_INFO;
        enable_logs();
    }
    else if(strcmp(log_level, "warn") == 0)
    {
        g_log_level = LOG_WARNING;
        enable_logs();
    }
    else if(strcmp(log_level, "error") == 0)
    {
        g_log_level = LOG_ERROR;
        enable_logs();
    }
    else
    {
	    log_msg(LOG_INFO, "logging disabled ");
        disable_logs();
        g_log_level = LOG_NEVER;
    }
}

void log_message(int l, const char *file, int line, const char *fmt, ...)
{
	va_list arg;
	if (g_nolog) return;
	if(g_log_level > l) return;

	fprintf(stderr,"%s-%s:%d:", log_level_name[l], file, line);
	va_start(arg, fmt);
	vfprintf(stderr, fmt, arg);
	va_end(arg);
//	fprintf(stderr, "\n");
}

