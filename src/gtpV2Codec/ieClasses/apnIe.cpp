/*
 * apnIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "apnIe.h"
#include "dataTypeCodecUtils.h"

ApnIe::ApnIe() 
{
    ieType = 71;
    // TODO

}

ApnIe::~ApnIe() {
    // TODO Auto-generated destructor stub
}

bool ApnIe::encodeApnIe(MsgBuffer &buffer, ApnIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array32(buffer, data.apnValue)))
    {
    errorStream.add("Encoding of apnValue failed\n");
    return false;
    }

    return true;
}

bool ApnIe::decodeApnIe(MsgBuffer &buffer, ApnIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array32(buffer, data.apnValue, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: apnValue\n");
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
        errorStream.add("Unable to decode IE ApnIe\n");
        return false;
    }
}
void ApnIe::displayApnIe_v(ApnIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("ApnIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("apnValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array32_v(data.apnValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
