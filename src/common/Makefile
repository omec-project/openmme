#
# Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
# Copyright (c) 2017 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

ifeq ($(ROOT),)
include ../../build-config
ROOT=../..
endif

ifeq ($(DEBUG),true)
	CFLAGS += -g
endif

ifeq ($(DEBUG),false)
	CFLAGS += -O3
endif

IF_LIBNAME = libinterface.so
JSON_PARSER_LIBNAME = libjson.so
LOG_LIBNAME = liblog.a
TPOOL_LIBNAME = libthreadpool.a
UTIL_LIBNAME = libsecutil.so
MONITOR_CONFIG_LIBNAME = libmonitor_config.so

IF_SRC=ipc_api.c
LOG_SRC = log.c
TPOOL_SRC = thread_pool.c tpool_queue.c
JSON_PARSER_SRC = json_parser.c
UTIL_SRC = snow_3g.c f8.c f9.c
MONITOR_CONFIG = monitor_config.c

build_s6a:
	$(CC) $(CFLAGS) -fPIC -c $(IF_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(LOG_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(TPOOL_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(JSON_PARSER_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(UTIL_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(MONITOR_CONFIG) $(INC_DIRS)
	$(CC) $(CFLAGS) ipc_api.o -shared -o $(IF_LIBNAME)
	$(CC) $(CFLAGS) json_parser.o -shared -o $(JSON_PARSER_LIBNAME)
	$(CC) $(CFLAGS) snow_3g.o f8.o f9.o -shared -o $(UTIL_LIBNAME)
	$(CC) $(CFLAGS) monitor_config.o -shared -o $(MONITOR_CONFIG_LIBNAME)
	ar rcs $(LOG_LIBNAME) log.o
	ar rcs $(TPOOL_LIBNAME) thread_pool.o tpool_queue.o

all: build_s6a

install:all
	-@mkdir -p $(TARGET_DIR)/lib
	-@mkdir -p $(TARGET_DIR)/conf
	-@cp $(IF_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(LOG_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(JSON_PARSER_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(UTIL_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(MONITOR_CONFIG_LIBNAME) $(TARGET_DIR)/lib

clean:
	rm -f *.o
	rm -f *.a *.so
	rm -f $(IF_LIBNAME)

