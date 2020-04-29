#
# Copyright 2019-present Open Networking Foundation
# Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
# Copyright (c) 2017 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0
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
UNIXSOCK_LIBNAME = libusock.a
TPOOL_LIBNAME = libthreadpool.a
UTIL_LIBNAME = libsecutil.so
MONITOR_CONFIG_LIBNAME = libmonitor_config.so

IF_SRC=ipc_api.c
LOG_SRC = log.c
TPOOL_SRC = thread_pool.c tpool_queue.c
JSON_PARSER_SRC = json_parser.c
UTIL_SRC = snow_3g.c f8.c f9.c
UNIXSOCK_SRC = unix_sock.c unix_conn.c
MONITOR_CONFIG = monitor_config.c backtrace.c

build_s6a:
	$(CC) $(CFLAGS) -fPIC -c $(IF_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(LOG_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(TPOOL_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(JSON_PARSER_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(UTIL_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(MONITOR_CONFIG) $(INC_DIRS)
	$(CC) $(CFLAGS) -fPIC -c $(UNIXSOCK_SRC) $(INC_DIRS)
	$(CC) $(CFLAGS) ipc_api.o -shared -o $(IF_LIBNAME)
	$(CC) $(CFLAGS) json_parser.o -shared -o $(JSON_PARSER_LIBNAME)
	$(CC) $(CFLAGS) snow_3g.o f8.o f9.o -shared -o $(UTIL_LIBNAME)
	$(CC) $(CFLAGS) monitor_config.o backtrace.o -shared -o $(MONITOR_CONFIG_LIBNAME)
	ar rcs $(LOG_LIBNAME) log.o
	ar rcs $(TPOOL_LIBNAME) thread_pool.o tpool_queue.o
	ar rcs $(UNIXSOCK_LIBNAME) unix_sock.o unix_conn.o

all: build_s6a

install:all
	-@mkdir -p $(TARGET_DIR)/lib
	-@mkdir -p $(TARGET_DIR)/conf
	-@cp $(IF_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(LOG_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(JSON_PARSER_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(UTIL_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(MONITOR_CONFIG_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(UNIXSOCK_LIBNAME) $(TARGET_DIR)/lib

clean:
	rm -f *.o
	rm -f *.a *.so
	rm -f $(IF_LIBNAME)

