/*
 * epcTimerIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "epcTimerIe.h"
#include "dataTypeCodecUtils.h"

EpcTimerIe::EpcTimerIe() 
{
    ieType = 156;
    // TODO

}

EpcTimerIe::~EpcTimerIe() {
    // TODO Auto-generated destructor stub
}

bool EpcTimerIe::encodeEpcTimerIe(MsgBuffer &buffer, EpcTimerIeData const &data)
{
    if(!(buffer.writeBits(data.timerUnit, 3)))
    {
        errorStream.add("Encoding of timerUnit failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.timerValue, 5)))
    {
        errorStream.add("Encoding of timerValue failed\n");
        return false;
    }

    return true;
}

bool EpcTimerIe::decodeEpcTimerIe(MsgBuffer &buffer, EpcTimerIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.timerUnit = buffer.readBits(3);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: timerUnit\n");
        return false;
    }
    data.timerValue = buffer.readBits(5);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: timerValue\n");
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
        errorStream.add("Unable to decode IE EpcTimerIe\n");
        return false;
    }
}
void EpcTimerIe::displayEpcTimerIe_v(EpcTimerIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("EpcTimerIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "timerUnit: "); 
    stream.add((Uint8)data.timerUnit);
    stream.endOfLine();
  
    stream.add( "timerValue: "); 
    stream.add((Uint8)data.timerValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
