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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "log.h"
bool g_nolog = false;
enum log_levels g_log_level = LOG_WARNING;

static const char *log_level_name[] = { "INFO", "DEBUG", "WARN", "ERROR" };

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

