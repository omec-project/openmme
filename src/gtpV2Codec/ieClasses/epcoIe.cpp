/*
 * epcoIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "epcoIe.h"
#include "dataTypeCodecUtils.h"

EpcoIe::EpcoIe() 
{
    ieType = 197;
    // TODO

}

EpcoIe::~EpcoIe() {
    // TODO Auto-generated destructor stub
}

bool EpcoIe::encodeEpcoIe(MsgBuffer &buffer, EpcoIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.epco)))
    {
    errorStream.add("Encoding of epco failed\n");
    return false;
    }

    return true;
}

bool EpcoIe::decodeEpcoIe(MsgBuffer &buffer, EpcoIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.epco, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: epco\n");
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
        errorStream.add("Unable to decode IE EpcoIe\n");
        return false;
    }
}
void EpcoIe::displayEpcoIe_v(EpcoIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("EpcoIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("epco:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array16_v(data.epco, stream);
    stream.decrIndent();
    stream.decrIndent();
}
