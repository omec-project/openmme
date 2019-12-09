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
