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

