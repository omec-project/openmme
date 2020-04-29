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

SM_LIBNAME = $(LIBDIR)/libstatemachinefwk.so

SRCS := \
	./actionTable.cpp  \
	./controlBlock.cpp \
	./event.cpp  \
	./permDataBlock.cpp \
	./procedureQueue.cpp \
	./state.cpp \
	./stateMachineEngine.cpp \
	./tempDataBlock.cpp

SRCDIR := .
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/stateMachineFwk/%,$(SRCS:.cpp=.o)) 

buildSmLIB: $(OBJECTS)
	@echo "Linking"
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -shared -o $(SM_LIBNAME)

$(OBJECTS) : $(OBJDIR)/stateMachineFwk/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)/stateMachineFwk
	$(CC) $(CFLAGS) $(INC_DIRS) -fPIC -c -o $@ $<

all: buildSmLIB

install:all
	-@echo "Installing"
	-@mkdir -p $(TARGET_DIR)/lib
	-@cp $(SM_LIBNAME) $(TARGET_DIR)/lib

clean:
	@echo " Cleaning...";
	-@rm -rf $(OBJDIR)/stateMachineFwk $(SM_LIBNAME)

