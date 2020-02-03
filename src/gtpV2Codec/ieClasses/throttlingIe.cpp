/*
 * throttlingIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
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
        errorStream.add("Encoding of throttlingDelayUnit failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.throttlingDelayValue, 5)))
    {
        errorStream.add("Encoding of throttlingDelayValue failed\n");
        return false;
    }
    if (!(data.throttlingFactor>= 0 && data.throttlingFactor<= 100))
    {
        errorStream.add("Data validation failure: throttlingFactor\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.throttlingFactor)))
    {
        errorStream.add("Encoding of throttlingFactor failed\n");
        return false;
    }

    return true;
}

bool ThrottlingIe::decodeThrottlingIe(MsgBuffer &buffer, ThrottlingIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.throttlingDelayUnit = buffer.readBits(3);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: throttlingDelayUnit\n");
        return false;
    }
    data.throttlingDelayValue = buffer.readBits(5);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: throttlingDelayValue\n");
        return false;
    }

    buffer.readUint8(data.throttlingFactor);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: throttlingFactor\n");
        return false;
    }
    if (!(data.throttlingFactor>= 0 && data.throttlingFactor<= 100))
    {
        errorStream.add("Data validation failure : throttlingFactor\n");
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
        errorStream.add("Unable to decode IE ThrottlingIe\n");
        return false;
    }
}
void ThrottlingIe::displayThrottlingIe_v(ThrottlingIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("ThrottlingIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "throttlingDelayUnit: "); 
    stream.add((Uint8)data.throttlingDelayUnit);
    stream.endOfLine();
  
    stream.add( "throttlingDelayValue: "); 
    stream.add((Uint8)data.throttlingDelayValue);
    stream.endOfLine();
  
    stream.add("throttlingFactor: ");
    stream.add(data.throttlingFactor);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
