#
# Copyright 2019-present Open Networking Foundation
# Copyright (c) 2019, Infosys Ltd.
#
# SPDX-License-Identifier: Apache-2.0
#

include ../../../Makefile.common

CC := g++
CFLAGS += -std=c++11 

ifeq ($(DEBUG),true)
        CFLAGS += -g
endif
ifeq ($(DEBUG),false)
        CFLAGS += -O3
endif

S1APCTXMGR_LIBNAME = libs1apctxmgr.so

S1APCTXMGR_SRCS := ./s1apContextWrapper.cpp \
                   ./s1apContextWrapper_c.cpp \
                   ./s1apDataGroupManager.cpp \
                   ./dataBlocks.cpp \
                   ./enbContextManager.cpp

SRCDIR := .
SRCEXT := cpp
S1APCTXMGR_OBJS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/s1ap/contextManager/%,$(S1APCTXMGR_SRCS:.$(SRCEXT)=.o))

OBJS := $(S1APCTXMGR_OBJS)

all : buildCommonLIBS

buildCommonLIBS : $(OBJS)
	@echo "Linking"
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) $(S1APCTXMGR_OBJS) -shared -o $(S1APCTXMGR_LIBNAME)

$(OBJS) : $(OBJDIR)/s1ap/contextManager/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/s1ap/contextManager
	$(CC) $(CFLAGS) $(INC_DIRS) -fPIC -c -o $@ $<

install:all
	-@mkdir -p $(TARGET_DIR)/lib
	-@cp $(S1APCTXMGR_LIBNAME) $(TARGET_DIR)/lib

clean:
	@echo " Cleaning...";
	-@rm -rf $(OBJDIR)/s1ap/contextManager
	-@rm -f $(S1APCTXMGR_LIBNAME)

