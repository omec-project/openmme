#
# Copyright 2019-present Open Networking Foundation
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
TARGET := mme-app
BUILDDIR := build

SRCEXT := c

SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS += -Wall -DSTATS

ifeq ($(DEBUG),true)
	CFLAGS += -g
endif

ifeq ($(DEBUG),false)
	CFLAGS += -O3
endif

INCS := $(INC_DIRS) \
	-I../gtpV2Codec -I../cmn \

LIBS := -lpthread -lcrypto -lthreadpool -lusock
#-L$(LIB_PATH) -ls6a

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/handlers
	@mkdir -p $(BUILDDIR)/sec
	#@echo " $(CC) $(LFLAGS) $^ -o $(TARGET) $(LIB_PATH) -linterface $(LIBS)";
	$(CC) $(LFLAGS) $^ -o $(TARGET) $(LIB_PATH) -linterface -llog -ljson -lmonitor_config $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/handlers
	@mkdir -p $(BUILDDIR)/sec
	@echo " $(CC) $(CFLAGS) $(INCS) -c -o $@ $<"; $(CC) $(CFLAGS) $(INCS) -c -o $@ $<

all:$(TARGET)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

install:
	mkdir -p $(TARGET_DIR)/bin
	cp $(TARGET) $(TARGET_DIR)/bin
	cp run.sh $(TARGET_DIR)
	cp stop.sh $(TARGET_DIR)
	-@mkdir -p $(TARGET_DIR)/conf
	-@cp conf/*.json $(TARGET_DIR)/conf/

.PHONY: clean

