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
