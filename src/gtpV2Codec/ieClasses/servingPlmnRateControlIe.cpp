/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "servingPlmnRateControlIe.h"
#include "dataTypeCodecUtils.h"

ServingPlmnRateControlIe::ServingPlmnRateControlIe() 
{
    ieType = 198;
    // TODO

}

ServingPlmnRateControlIe::~ServingPlmnRateControlIe() {
    // TODO Auto-generated destructor stub
}

bool ServingPlmnRateControlIe::encodeServingPlmnRateControlIe(MsgBuffer &buffer, ServingPlmnRateControlIeData const &data)
{
    if (!(buffer.writeUint16(data.uplinkRateLimit)))
    {
        errorStream.add((char *)"Encoding of uplinkRateLimit failed\n");
        return false;
    }
    if (!(buffer.writeUint16(data.downlinkRateLimit)))
    {
        errorStream.add((char *)"Encoding of downlinkRateLimit failed\n");
        return false;
    }

    return true;
}

bool ServingPlmnRateControlIe::decodeServingPlmnRateControlIe(MsgBuffer &buffer, ServingPlmnRateControlIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint16(data.uplinkRateLimit);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: uplinkRateLimit\n");
        return false;
    }

    buffer.readUint16(data.downlinkRateLimit);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: downlinkRateLimit\n");
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
        errorStream.add((char *)"Unable to decode IE ServingPlmnRateControlIe\n");
        return false;
    }
}
void ServingPlmnRateControlIe::displayServingPlmnRateControlIe_v(ServingPlmnRateControlIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ServingPlmnRateControlIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"uplinkRateLimit: ");
    stream.add(data.uplinkRateLimit);
    stream.endOfLine();
  
    stream.add((char *)"downlinkRateLimit: ");
    stream.add(data.downlinkRateLimit);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
