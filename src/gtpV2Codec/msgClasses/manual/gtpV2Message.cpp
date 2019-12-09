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
 


#include "gtpV2Message.h"

GtpV2Message::GtpV2Message() {
	// TODO Auto-generated constructor stub

}

GtpV2Message::~GtpV2Message() {
	// TODO Auto-generated destructor stub
}

void GtpV2Message::encodeHeader(MsgBuffer& buffer, GtpV2MessageHeader& msgHeader)
{
  buffer.writeBits(2, 3); // Gtpversion 2
  buffer.writeBits(0, 1); //Pigiback - TODO later
  buffer.writeBits(msgHeader.teidPresent, 1);
  buffer.skipBits(3);

  buffer.writeUint8(msgHeader.msgType);
  buffer.writeUint16(msgHeader.msgLength);
  
  if (msgHeader.teidPresent)
  {
    buffer.writeUint32(msgHeader.teid);
  }
  
  Uint32 seqNumber = msgHeader.sequenceNumber << 8;
  std::cout << "current seq num indx is " << buffer.getCurrentIndex() << std::endl;
  buffer.writeUint32(seqNumber);
  
}

bool GtpV2Message::decodeHeader(MsgBuffer& buffer, GtpV2MessageHeader& msgHeader)
{
  buffer.skipBits(4);
  msgHeader.teidPresent = buffer.readBit();
  buffer.skipBits(3);

  buffer.readUint8(msgHeader.msgType);
  buffer.readUint16(msgHeader.msgLength);

  if (msgHeader.teidPresent)
  {
    buffer.readUint32(msgHeader.teid);
  }
  Uint32 seqNumber;

  buffer.readUint32(seqNumber);
  msgHeader.sequenceNumber = (seqNumber >> 8);
    
  return true; //TODO

}

