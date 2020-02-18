/*
 * chargingCharacteristicsIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "chargingCharacteristicsIe.h"
#include "dataTypeCodecUtils.h"

ChargingCharacteristicsIe::ChargingCharacteristicsIe() 
{
    ieType = 95;
    // TODO

}

ChargingCharacteristicsIe::~ChargingCharacteristicsIe() {
    // TODO Auto-generated destructor stub
}

bool ChargingCharacteristicsIe::encodeChargingCharacteristicsIe(MsgBuffer &buffer, ChargingCharacteristicsIeData const &data)
{
    if (!(buffer.writeUint16(data.value)))
    {
        errorStream.add("Encoding of value failed\n");
        return false;
    }

    return true;
}

bool ChargingCharacteristicsIe::decodeChargingCharacteristicsIe(MsgBuffer &buffer, ChargingCharacteristicsIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint16(data.value);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: value\n");
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
        errorStream.add("Unable to decode IE ChargingCharacteristicsIe\n");
        return false;
    }
}
void ChargingCharacteristicsIe::displayChargingCharacteristicsIe_v(ChargingCharacteristicsIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("ChargingCharacteristicsIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("value: ");
    stream.add(data.value);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
