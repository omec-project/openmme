/*
 * millisecondTimeStampIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "millisecondTimeStampIe.h"
#include "dataTypeCodecUtils.h"

MillisecondTimeStampIe::MillisecondTimeStampIe() 
{
    ieType = 188;
    // TODO

}

MillisecondTimeStampIe::~MillisecondTimeStampIe() {
    // TODO Auto-generated destructor stub
}

bool MillisecondTimeStampIe::encodeMillisecondTimeStampIe(MsgBuffer &buffer, MillisecondTimeStampIeData const &data)
{
    if (!(buffer.writeUint64(data.millisecondTimeStampValue)))
    {
        errorStream.add("Encoding of millisecondTimeStampValue failed\n");
        return false;
    }

    return true;
}

bool MillisecondTimeStampIe::decodeMillisecondTimeStampIe(MsgBuffer &buffer, MillisecondTimeStampIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint64(data.millisecondTimeStampValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: millisecondTimeStampValue\n");
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
        errorStream.add("Unable to decode IE MillisecondTimeStampIe\n");
        return false;
    }
}
void MillisecondTimeStampIe::displayMillisecondTimeStampIe_v(MillisecondTimeStampIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("MillisecondTimeStampIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("millisecondTimeStampValue: ");
    stream.add(data.millisecondTimeStampValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
