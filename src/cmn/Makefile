#
# Copyright (c) 2019, Infosys Ltd.
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

