/*
 * uliTimestampIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "uliTimestampIe.h"
#include "dataTypeCodecUtils.h"

UliTimestampIe::UliTimestampIe() 
{
    ieType = 170;
    // TODO

}

UliTimestampIe::~UliTimestampIe() {
    // TODO Auto-generated destructor stub
}

bool UliTimestampIe::encodeUliTimestampIe(MsgBuffer &buffer, UliTimestampIeData const &data)
{
    if (!(buffer.writeUint32(data.uliTimestampvalue)))
    {
        errorStream.add("Encoding of uliTimestampvalue failed\n");
        return false;
    }

    return true;
}

bool UliTimestampIe::decodeUliTimestampIe(MsgBuffer &buffer, UliTimestampIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint32(data.uliTimestampvalue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: uliTimestampvalue\n");
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
        errorStream.add("Unable to decode IE UliTimestampIe\n");
        return false;
    }
}
void UliTimestampIe::displayUliTimestampIe_v(UliTimestampIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("UliTimestampIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("uliTimestampvalue: ");
    stream.add(data.uliTimestampvalue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
