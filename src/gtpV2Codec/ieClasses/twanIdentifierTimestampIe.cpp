/*
 * twanIdentifierTimestampIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "twanIdentifierTimestampIe.h"
#include "dataTypeCodecUtils.h"

TwanIdentifierTimestampIe::TwanIdentifierTimestampIe() 
{
    ieType = 179;
    // TODO

}

TwanIdentifierTimestampIe::~TwanIdentifierTimestampIe() {
    // TODO Auto-generated destructor stub
}

bool TwanIdentifierTimestampIe::encodeTwanIdentifierTimestampIe(MsgBuffer &buffer, TwanIdentifierTimestampIeData const &data)
{
    if (!(buffer.writeUint32(data.twanIdentifierTimestampvalue)))
    {
        errorStream.add("Encoding of twanIdentifierTimestampvalue failed\n");
        return false;
    }

    return true;
}

bool TwanIdentifierTimestampIe::decodeTwanIdentifierTimestampIe(MsgBuffer &buffer, TwanIdentifierTimestampIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint32(data.twanIdentifierTimestampvalue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: twanIdentifierTimestampvalue\n");
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
        errorStream.add("Unable to decode IE TwanIdentifierTimestampIe\n");
        return false;
    }
}
void TwanIdentifierTimestampIe::displayTwanIdentifierTimestampIe_v(TwanIdentifierTimestampIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("TwanIdentifierTimestampIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("twanIdentifierTimestampvalue: ");
    stream.add(data.twanIdentifierTimestampvalue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
