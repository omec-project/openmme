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

INCS := $(INC_DIRS)

LIBS := -lpthread -lcrypto
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

