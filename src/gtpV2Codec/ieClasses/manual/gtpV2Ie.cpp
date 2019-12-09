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
 


#include "../../../gtpV2Codec/ieClasses/manual/gtpV2Ie.h"

#include "msgBuffer.h"

#define GTP_V2_IE_HEADER_LENGTH 4
GtpV2Ie::GtpV2Ie() {
	// TODO Auto-generated constructor stub

}

GtpV2Ie::~GtpV2Ie() {
	// TODO Auto-generated destructor stub
}

void GtpV2Ie::decodeGtpV2IeHeader(MsgBuffer &buffer, GtpV2IeHeader &data)
{
	// Assume that the pointer in the MsgBuffer is pointing to the start of the IE
	buffer.readUint8(data.ieType);
	buffer.readUint16(data.length);
	buffer.skipBits(4);
	data.instance = buffer.readBits(4);
}

void GtpV2Ie::encodeGtpV2IeHeader(MsgBuffer &buffer, GtpV2IeHeader const &data)
{
	// Assume that the pointer in the MsgBuffer is pointing to the start of the IE
	buffer.writeUint8(data.ieType, false);
	buffer.writeUint16(data.length, false);
	buffer.skipBits(4);
	buffer.writeBits(data.instance, 4, false);
}

void GtpV2Ie::reserveHeaderSpace(MsgBuffer &buffer)
{
	buffer.skipBytes(GTP_V2_IE_HEADER_LENGTH);
}
