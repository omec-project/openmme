/*
 * bearerTftIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "bearerTftIe.h"
#include "dataTypeCodecUtils.h"

BearerTftIe::BearerTftIe() 
{
    ieType = 84;
    // TODO

}

BearerTftIe::~BearerTftIe() {
    // TODO Auto-generated destructor stub
}

bool BearerTftIe::encodeBearerTftIe(MsgBuffer &buffer, BearerTftIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.tft)))
    {
    errorStream.add("Encoding of tft failed\n");
    return false;
    }

    return true;
}

bool BearerTftIe::decodeBearerTftIe(MsgBuffer &buffer, BearerTftIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.tft, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: tft\n");
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
        errorStream.add("Unable to decode IE BearerTftIe\n");
        return false;
    }
}
void BearerTftIe::displayBearerTftIe_v(BearerTftIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("BearerTftIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("tft:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array16_v(data.tft, stream);
    stream.decrIndent();
    stream.decrIndent();
}
