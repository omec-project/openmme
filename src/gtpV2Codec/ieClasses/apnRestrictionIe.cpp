/*
 * apnRestrictionIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "apnRestrictionIe.h"
#include "dataTypeCodecUtils.h"

ApnRestrictionIe::ApnRestrictionIe() 
{
    ieType = 127;
    // TODO

}

ApnRestrictionIe::~ApnRestrictionIe() {
    // TODO Auto-generated destructor stub
}

bool ApnRestrictionIe::encodeApnRestrictionIe(MsgBuffer &buffer, ApnRestrictionIeData const &data)
{
    if (!(buffer.writeUint8(data.restrictionValue)))
    {
        errorStream.add("Encoding of restrictionValue failed\n");
        return false;
    }

    return true;
}

bool ApnRestrictionIe::decodeApnRestrictionIe(MsgBuffer &buffer, ApnRestrictionIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.restrictionValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: restrictionValue\n");
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
        errorStream.add("Unable to decode IE ApnRestrictionIe\n");
        return false;
    }
}
void ApnRestrictionIe::displayApnRestrictionIe_v(ApnRestrictionIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("ApnRestrictionIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("restrictionValue: ");
    stream.add(data.restrictionValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
