 /*
 * Copyright (c) 2019, Infosys Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

