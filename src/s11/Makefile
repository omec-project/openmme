#
# Copyright 2019-present Open Networking Foundation
# Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
# Copyright (c) 2017 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0
#
ifndef ROOT
include ../../build-config
ROOT=../..
LIB_PATH +=-L../common/ \
	   -L../../build/libs/
TARGET_DIR := $(ROOT)/target
endif
SRCDIR := .
TARGET := s11-app
BUILDDIR := build
S11_JSON = s11.json

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

INCS := $(INC_DIRS) \
	-I../gtpV2Codec -I../cmn \

LIBS := -lpthread	\
	-lsctp \
	-lgtpV2Codec \
    -lmonitor_config \
	-lcmnUtils

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(BUILDDIR)/handlers
	@mkdir -p $(BUILDDIR)/message_handlers
	#@echo " $(CC) $(LFLAGS) $^ -o $(TARGET) $(LIB_PATH) -linterface $(LIBS)";
	g++ $(LFLAGS) $^ -o $(TARGET) $(LIB_PATH) -linterface -llog -lthreadpool -ljson -lmonitor_config $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)/handlers
	@mkdir -p $(BUILDDIR)/message_handlers
	@echo " $(CC) $(CFLAGS) $(INCS) -c -o $@ $<"; gcc $(CFLAGS) $(INCS) -c -o $@ $<

all:$(TARGET)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

install:
	mkdir -p $(TARGET_DIR)/bin/
	cp $(TARGET) $(TARGET_DIR)/bin/
	cp conf/$(S11_JSON) $(TARGET_DIR)/conf/

.PHONY: clean

