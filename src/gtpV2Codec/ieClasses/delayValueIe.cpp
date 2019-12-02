/*
 * delayValueIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "delayValueIe.h"
#include "dataTypeCodecUtils.h"

DelayValueIe::DelayValueIe() 
{
    ieType = 92;
    // TODO

}

DelayValueIe::~DelayValueIe() {
    // TODO Auto-generated destructor stub
}

bool DelayValueIe::encodeDelayValueIe(MsgBuffer &buffer, DelayValueIeData const &data)
{
    if (!(data.delayValue% 50 == 0 || data.delayValue== 0))
    {
        errorStream.add("Data validation failure: delayValue\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.delayValue)))
    {
        errorStream.add("Encoding of delayValue failed\n");
        return false;
    }

    return true;
}

bool DelayValueIe::decodeDelayValueIe(MsgBuffer &buffer, DelayValueIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.delayValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: delayValue\n");
        return false;
    }
    if (!(data.delayValue% 50 == 0 || data.delayValue== 0))
    {
        errorStream.add("Data validation failure : delayValue\n");
        return false; //TODO need to add validations
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
        errorStream.add("Unable to decode IE DelayValueIe\n");
        return false;
    }
}
void DelayValueIe::displayDelayValueIe_v(DelayValueIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("DelayValueIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("delayValue: ");
    stream.add(data.delayValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
