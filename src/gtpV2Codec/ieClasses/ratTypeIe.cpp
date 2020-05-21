/*
 * ratTypeIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "ratTypeIe.h"
#include "dataTypeCodecUtils.h"

RatTypeIe::RatTypeIe() 
{
    ieType = 82;
    // TODO

}

RatTypeIe::~RatTypeIe() {
    // TODO Auto-generated destructor stub
}

bool RatTypeIe::encodeRatTypeIe(MsgBuffer &buffer, RatTypeIeData const &data)
{
    if (!(buffer.writeUint8(data.ratType)))
    {
        errorStream.add("Encoding of ratType failed\n");
        return false;
    }

    return true;
}

bool RatTypeIe::decodeRatTypeIe(MsgBuffer &buffer, RatTypeIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.ratType);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: ratType\n");
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
        errorStream.add("Unable to decode IE RatTypeIe\n");
        return false;
    }
}
void RatTypeIe::displayRatTypeIe_v(RatTypeIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("RatTypeIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("ratType: ");
    stream.add(data.ratType);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
