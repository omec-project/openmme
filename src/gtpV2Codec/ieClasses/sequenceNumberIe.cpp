/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "sequenceNumberIe.h"
#include "dataTypeCodecUtils.h"

SequenceNumberIe::SequenceNumberIe() 
{
    ieType = 183;
    // TODO

}

SequenceNumberIe::~SequenceNumberIe() {
    // TODO Auto-generated destructor stub
}

bool SequenceNumberIe::encodeSequenceNumberIe(MsgBuffer &buffer, SequenceNumberIeData const &data)
{
    if (!(buffer.writeUint32(data.sequenceNumber)))
    {
        errorStream.add((char *)"Encoding of sequenceNumber failed\n");
        return false;
    }

    return true;
}

bool SequenceNumberIe::decodeSequenceNumberIe(MsgBuffer &buffer, SequenceNumberIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint32(data.sequenceNumber);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: sequenceNumber\n");
        return false;
    }

    // The IE is decoded now. The buffer index should be pointing to the 
    // IE Boundary. If not, we have some more data left for the IE which we don't know
    // how to decode
    if (ieBoundary == buffer.getCurrentIndex())
    {
        return true;
    }
    else
    {
        errorStream.add((char *)"Unable to decode IE SequenceNumberIe\n");
        return false;
    }
}
void SequenceNumberIe::displaySequenceNumberIe_v(SequenceNumberIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"SequenceNumberIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"sequenceNumber: ");
    stream.add(data.sequenceNumber);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
