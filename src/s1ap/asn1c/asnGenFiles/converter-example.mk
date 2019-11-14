include Makefile.am.libasncodec

LIBS += -lm
CFLAGS += $(ASN_MODULE_CFLAGS) -DPDU=S1AP_PDU -I.
ASN_LIBRARY ?= libasncodec.a
ASN_PROGRAM ?= converter-example
ASN_PROGRAM_SRCS ?= \
	converter-example.c

all: $(ASN_PROGRAM)

$(ASN_PROGRAM): $(ASN_LIBRARY) $(ASN_PROGRAM_SRCS:.c=.o)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(ASN_PROGRAM) $(ASN_PROGRAM_SRCS:.c=.o) $(LDFLAGS) $(ASN_LIBRARY) $(LIBS)

$(ASN_LIBRARY): $(ASN_MODULE_SRCS:.c=.o)
	$(AR) rcs $@ $(ASN_MODULE_SRCS:.c=.o)

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(ASN_PROGRAM) $(ASN_LIBRARY)
	rm -f $(ASN_MODULE_SRCS:.c=.o) $(ASN_PROGRAM_SRCS:.c=.o)

regen: regenerate-from-asn1-source

regenerate-from-asn1-source:
	asn1c -fcompound-names -fno-include-deps -gen-PER -findirect-choice -pdu=S1AP-PDU ./asn1c/S1AP-CommonDataTypes.asn ./asn1c/S1AP-Constants.asn ./asn1c/S1AP-Containers.asn ./asn1c/S1AP-IEs.asn ./asn1c/S1AP-PDU-Contents.asn ./asn1c/S1AP-PDU-Descriptions.asn

