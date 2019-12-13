/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "throttlingIe.h"
#include "dataTypeCodecUtils.h"

ThrottlingIe::ThrottlingIe() 
{
    ieType = 154;
    // TODO

}

ThrottlingIe::~ThrottlingIe() {
    // TODO Auto-generated destructor stub
}

bool ThrottlingIe::encodeThrottlingIe(MsgBuffer &buffer, ThrottlingIeData const &data)
{
    if(!(buffer.writeBits(data.throttlingDelayUnit, 3)))
    {
        errorStream.add((char *)"Encoding of throttlingDelayUnit failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.throttlingDelayValue, 5)))
    {
        errorStream.add((char *)"Encoding of throttlingDelayValue failed\n");
        return false;
    }
    if (!(data.throttlingFactor>= 0 && data.throttlingFactor<= 100))
    {
        errorStream.add((char *)"Data validation failure: throttlingFactor\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.throttlingFactor)))
    {
        errorStream.add((char *)"Encoding of throttlingFactor failed\n");
        return false;
    }

    return true;
}

bool ThrottlingIe::decodeThrottlingIe(MsgBuffer &buffer, ThrottlingIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.throttlingDelayUnit = buffer.readBits(3);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: throttlingDelayUnit\n");
        return false;
    }
    data.throttlingDelayValue = buffer.readBits(5);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: throttlingDelayValue\n");
        return false;
    }

    buffer.readUint8(data.throttlingFactor);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: throttlingFactor\n");
        return false;
    }
    if (!(data.throttlingFactor>= 0 && data.throttlingFactor<= 100))
    {
        errorStream.add((char *)"Data validation failure : throttlingFactor\n");
        return false; //TODO need to add validations
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
        errorStream.add((char *)"Unable to decode IE ThrottlingIe\n");
        return false;
    }
}
void ThrottlingIe::displayThrottlingIe_v(ThrottlingIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ThrottlingIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"throttlingDelayUnit: "); 
    stream.add((Uint8)data.throttlingDelayUnit);
    stream.endOfLine();
  
    stream.add( (char *)"throttlingDelayValue: "); 
    stream.add((Uint8)data.throttlingDelayValue);
    stream.endOfLine();
  
    stream.add((char *)"throttlingFactor: ");
    stream.add(data.throttlingFactor);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
