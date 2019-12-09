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

OUTPUTOBJDIR := $(OBJDIR)/cmn/

OUTPUTLIB := $(LIBDIR)/libcommonUtils.so

OBJS := 	debug.o \
        	msgBuffer.o \

OBJECTS := $(addprefix $(OUTPUTOBJDIR), $(OBJS))

all :  $(OUTPUTLIB)

.PHONY : all

$(OUTPUTLIB) : $(OBJECTS)
	mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) -shared -o $(OUTPUTLIB) $(OBJECTS)

$(OBJECTS) : $(OBJDIR)/cmn/%.o : %.cpp
	mkdir -p $(OUTPUTOBJDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

install:
	mkdir -p $(TOPDIR)/target/lib
	cp -rf $(OUTPUTLIB) $(TOPDIR)/target/lib

clean :
	rm -rf $(OUTPUTLIB)
	rm -rf $(OUTPUTOBJDIR)

.PHONY : clean
