/*
 * ranNasCauseIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "ranNasCauseIe.h"
#include "dataTypeCodecUtils.h"

RanNasCauseIe::RanNasCauseIe() 
{
    ieType = 172;
    // TODO

}

RanNasCauseIe::~RanNasCauseIe() {
    // TODO Auto-generated destructor stub
}

bool RanNasCauseIe::encodeRanNasCauseIe(MsgBuffer &buffer, RanNasCauseIeData const &data)
{
    if (!(data.protocolType>= 1 && data.protocolType<=5))
    {
        errorStream.add("Data validation failure: protocolType\n");
        return false; 
    }
    if(!(buffer.writeBits(data.protocolType, 4)))
    {
        errorStream.add("Encoding of protocolType failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.causeType, 4)))
    {
        errorStream.add("Encoding of causeType failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.causeValue)))
    {
        errorStream.add("Encoding of causeValue failed\n");
        return false;
    }

    return true;
}

bool RanNasCauseIe::decodeRanNasCauseIe(MsgBuffer &buffer, RanNasCauseIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.protocolType = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: protocolType\n");
        return false;
    }
    if (!(data.protocolType>= 1 && data.protocolType<=5))
    {
        errorStream.add("Data validation failure : protocolType\n");
        return false; //TODO need to add validations
    }
    data.causeType = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: causeType\n");
        return false;
    }

    buffer.readUint8(data.causeValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: causeValue\n");
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
        errorStream.add("Unable to decode IE RanNasCauseIe\n");
        return false;
    }
}
void RanNasCauseIe::displayRanNasCauseIe_v(RanNasCauseIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("RanNasCauseIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "protocolType: "); 
    stream.add((Uint8)data.protocolType);
    stream.endOfLine();
  
    stream.add( "causeType: "); 
    stream.add((Uint8)data.causeType);
    stream.endOfLine();
  
    stream.add("causeValue: ");
    stream.add(data.causeValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
