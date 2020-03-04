#
# Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
# Copyright (c) 2017 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0
#

#SRCDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
ifndef ROOT
include ../../build-config
ROOT=../..
LIB_PATH +=-L../common/
TARGET_DIR := $(ROOT)/target
endif
SRCDIR := .
TARGET := s6a-app
BUILDDIR := build

SRCEXT := c

SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS += -Wall

ifeq ($(DEBUG),true)
	CFLAGS += -g
endif

ifeq ($(DEBUG),false)
#	CFLAGS += -O3
endif

INCS := $(INC_DIRS)

LIBS := -lpthread	\
	-lfdproto -lfdcore

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(BUILDDIR)/handlers
	#@echo " $(CC) $(LFLAGS) $^ -o $(TARGET) $(LIB_PATH) -linterface $(LIBS)";
	$(CC) $(LFLAGS) $^ -o $(TARGET) $(LIB_PATH) -linterface -llog -lthreadpool -ljson -lmonitor_config $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)/handlers
	@echo " $(CC) $(CFLAGS) $(INCS) -c -o $@ $<"; $(CC) $(CFLAGS) $(INCS) -c -o $@ $<

all:$(TARGET)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

install:
	mkdir -p $(TARGET_DIR)/bin
	cp $(TARGET) $(TARGET_DIR)/bin
	-@mkdir -p $(TARGET_DIR)/conf
	-@cp conf/s6a_fd.conf $(TARGET_DIR)/conf/s6a_fd.conf
	-@cp conf/s6a.json $(TARGET_DIR)/conf/s6a.json
	-@cp conf/make_certs.sh $(TARGET_DIR)/conf/make_certs.sh


.PHONY: clean

