/*
 * localDistinguishedNameIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "localDistinguishedNameIe.h"
#include "dataTypeCodecUtils.h"

LocalDistinguishedNameIe::LocalDistinguishedNameIe() 
{
    ieType = 151;
    // TODO

}

LocalDistinguishedNameIe::~LocalDistinguishedNameIe() {
    // TODO Auto-generated destructor stub
}

bool LocalDistinguishedNameIe::encodeLocalDistinguishedNameIe(MsgBuffer &buffer, LocalDistinguishedNameIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array512(buffer, data.ldn)))
    {
    errorStream.add("Encoding of ldn failed\n");
    return false;
    }

    return true;
}

bool LocalDistinguishedNameIe::decodeLocalDistinguishedNameIe(MsgBuffer &buffer, LocalDistinguishedNameIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array512(buffer, data.ldn, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: ldn\n");
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
        errorStream.add("Unable to decode IE LocalDistinguishedNameIe\n");
        return false;
    }
}
void LocalDistinguishedNameIe::displayLocalDistinguishedNameIe_v(LocalDistinguishedNameIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("LocalDistinguishedNameIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("ldn:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array512_v(data.ldn, stream);
    stream.decrIndent();
    stream.decrIndent();
}
