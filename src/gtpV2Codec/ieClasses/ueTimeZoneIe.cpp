/*
 * ueTimeZoneIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "ueTimeZoneIe.h"
#include "dataTypeCodecUtils.h"

UeTimeZoneIe::UeTimeZoneIe() 
{
    ieType = 114;
    // TODO

}

UeTimeZoneIe::~UeTimeZoneIe() {
    // TODO Auto-generated destructor stub
}

bool UeTimeZoneIe::encodeUeTimeZoneIe(MsgBuffer &buffer, UeTimeZoneIeData const &data)
{
    buffer.skipBits(6);

    if (!(data.daylightSavingTime!= 3))
    {
        errorStream.add("Data validation failure: daylightSavingTime\n");
        return false; 
    }
    if(!(buffer.writeBits(data.daylightSavingTime, 2)))
    {
        errorStream.add("Encoding of daylightSavingTime failed\n");
        return false;
    }

    return true;
}

bool UeTimeZoneIe::decodeUeTimeZoneIe(MsgBuffer &buffer, UeTimeZoneIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(6);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.daylightSavingTime = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: daylightSavingTime\n");
        return false;
    }
    if (!(data.daylightSavingTime!= 3))
    {
        errorStream.add("Data validation failure : daylightSavingTime\n");
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
        errorStream.add("Unable to decode IE UeTimeZoneIe\n");
        return false;
    }
}
void UeTimeZoneIe::displayUeTimeZoneIe_v(UeTimeZoneIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("UeTimeZoneIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "daylightSavingTime: "); 
    stream.add((Uint8)data.daylightSavingTime);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
