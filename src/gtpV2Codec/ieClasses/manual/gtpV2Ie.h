 /*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 



#ifndef GTPV2IE_H_
#define GTPV2IE_H_

#include "basicTypes.h"
#include "msgBuffer.h"
#include "../gtpV2IeDataTypes.h"

#define IE_HEADER_SIZE 4

typedef struct
{
  Uint8  ieType;
  Uint16 length;
  Uint8  instance;
}GtpV2IeHeader;

class GtpV2Ie {
public:
	GtpV2Ie();
	virtual ~GtpV2Ie();

	static void encodeGtpV2IeHeader(MsgBuffer &buffer, GtpV2IeHeader const &data);
	static void decodeGtpV2IeHeader(MsgBuffer &buffer, GtpV2IeHeader &data);
	static void reserveHeaderSpace(MsgBuffer &buffer);

protected:
	Uint8 ieType;
};

#endif /* GTPV2IE_H_ */
