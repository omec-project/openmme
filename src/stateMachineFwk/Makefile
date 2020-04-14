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

