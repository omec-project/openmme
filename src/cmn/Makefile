#
# Copyright 2019-present Open Networking Foundation
# Copyright (c) 2019, Infosys Ltd.
#
# SPDX-License-Identifier: Apache-2.0
#

include ../../Makefile.common

CC := g++
CFLAGS += -std=c++11 

ifeq ($(DEBUG),true)
        CFLAGS += -g
endif
ifeq ($(DEBUG),false)
        CFLAGS += -O3
endif

DATAGROUPMGR_LIBNAME = $(LIBDIR)/libdatagroupmgr.so
CMNUTILS_LIBNAME = $(LIBDIR)/libcmnUtils.so

DATAGROUPMGR_SRCS := ./dataGroupManager.cpp
CMNUTILS_SRCS := ./debug.cpp \
		./msgBuffer.cpp

SRCDIR := .
SRCEXT := cpp
DATAGROUPMGR_OBJS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/cmn/%,$(DATAGROUPMGR_SRCS:.$(SRCEXT)=.o))
CMNUTILS_OBJS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/cmn/%,$(CMNUTILS_SRCS:.$(SRCEXT)=.o))


OBJS := $(DATAGROUPMGR_OBJS)\
	$(CMNUTILS_OBJS)

all : buildCommonLIBS

buildCommonLIBS : $(OBJS)
	@echo "Linking"
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) $(DATAGROUPMGR_OBJS) -shared -o $(DATAGROUPMGR_LIBNAME)
	$(CC) $(CFLAGS) $(CMNUTILS_OBJS) -shared -o $(CMNUTILS_LIBNAME)

$(OBJS) : $(OBJDIR)/cmn/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/cmn
	$(CC) $(CFLAGS) $(INC_DIRS) -fPIC -c -o $@ $<

install:all
	-@mkdir -p $(TARGET_DIR)/lib
	-@cp $(DATAGROUPMGR_LIBNAME) $(TARGET_DIR)/lib
	-@cp $(CMNUTILS_LIBNAME) $(TARGET_DIR)/lib

clean:
	@echo " Cleaning...";
	-@rm -rf $(OBJDIR)/cmn
	-@rm -f $(DATAGROUPMGR_LIBNAME) $(CMNUTILS_LIBNAME)

