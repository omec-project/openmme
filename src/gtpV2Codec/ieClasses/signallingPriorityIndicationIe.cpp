/*
 * signallingPriorityIndicationIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "signallingPriorityIndicationIe.h"
#include "dataTypeCodecUtils.h"

SignallingPriorityIndicationIe::SignallingPriorityIndicationIe() 
{
    ieType = 157;
    // TODO

}

SignallingPriorityIndicationIe::~SignallingPriorityIndicationIe() {
    // TODO Auto-generated destructor stub
}

bool SignallingPriorityIndicationIe::encodeSignallingPriorityIndicationIe(MsgBuffer &buffer, SignallingPriorityIndicationIeData const &data)
{
    buffer.skipBytes(2);


    return true;
}

bool SignallingPriorityIndicationIe::decodeSignallingPriorityIndicationIe(MsgBuffer &buffer, SignallingPriorityIndicationIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBytes(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
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
        errorStream.add("Unable to decode IE SignallingPriorityIndicationIe\n");
        return false;
    }
}
void SignallingPriorityIndicationIe::displaySignallingPriorityIndicationIe_v(SignallingPriorityIndicationIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("SignallingPriorityIndicationIeData:");
    stream.incrIndent();
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
