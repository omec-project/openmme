 /*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 
 


#ifndef GTPV2MESSAGE_H_
#define GTPV2MESSAGE_H_

#include "basicTypes.h"
#include "msgBuffer.h"
#include "../../../gtpV2Codec/msgClasses/gtpV2MsgDataTypes.h"

class GtpV2Message {
public:
	GtpV2Message();
	virtual ~GtpV2Message();
        static void encodeHeader(MsgBuffer& buffer, GtpV2MessageHeader& msgHeader);
        static bool decodeHeader(MsgBuffer& buffer, GtpV2MessageHeader& msgHeader);

protected:
        Uint8 msgType;
};

#endif /* GTPV2MESSAGE_H_ */

