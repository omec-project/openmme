 /*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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

