#
# Copyright 2019-present Open Networking Foundation
# Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
# Copyright (c) 2017 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0
#

#SRCDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include ../../Makefile.common
ifndef ROOT
include ../../build-config
ROOT=../..
LIB_PATH +=-L../common/ -L./asn1c/asnGenFiles -L./contextManager \
           -L../cmn -L../stateMachineFwk
TARGET_DIR := $(ROOT)/target
endif
SRCDIR := .
TARGET := s1ap-app
BUILDDIR := build
S1AP_CONF = s1ap.json

SRCEXT := c

SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS += -Wall

ifeq ($(DEBUG),true)
	CFLAGS += -g
endif

ifeq ($(DEBUG),false)
	CFLAGS += -O3
endif

INCS := $(INC_DIRS)

LIBS := -lpthread	\
	-lsctp \
	-linterface \
	-llog \
	-lthreadpool \
    -ls1apctxmgr \
    -lstatemachinefwk \
    -ldatagroupmgr \
    -lcmnUtils \
	-lasncodec \
	-ljson \
    -lmonitor_config \
	-lsecutil

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(BUILDDIR)/handlers
	@mkdir -p $(BUILDDIR)/message_handlers
	@mkdir -p $(BUILDDIR)/contextManager
	#@echo " $(CC) $(LFLAGS) $^ -o $(TARGET) $(LIB_PATH) -linterface $(LIBS)";
	$(CC) $(LFLAGS) $^ -o $(TARGET) $(LIB_PATH)  $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)/handlers
	@mkdir -p $(BUILDDIR)/message_handlers
	@mkdir -p $(BUILDDIR)/contextManager
	@echo " $(CC) $(CFLAGS) $(INCS) -c -o $@ $<"; $(CC) $(CFLAGS) $(INCS) -c -o $@ $<

all:$(TARGET)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

install:
	mkdir -p $(TARGET_DIR)/bin/
	cp $(TARGET) $(TARGET_DIR)/bin/
	cp conf/$(S1AP_CONF) $(TARGET_DIR)/conf/


.PHONY: clean

