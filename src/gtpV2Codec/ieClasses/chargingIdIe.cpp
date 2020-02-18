/*
 * chargingIdIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "chargingIdIe.h"
#include "dataTypeCodecUtils.h"

ChargingIdIe::ChargingIdIe() 
{
    ieType = 94;
    // TODO

}

ChargingIdIe::~ChargingIdIe() {
    // TODO Auto-generated destructor stub
}

bool ChargingIdIe::encodeChargingIdIe(MsgBuffer &buffer, ChargingIdIeData const &data)
{
    if (!(buffer.writeUint32(data.chargingIdValue)))
    {
        errorStream.add("Encoding of chargingIdValue failed\n");
        return false;
    }

    return true;
}

bool ChargingIdIe::decodeChargingIdIe(MsgBuffer &buffer, ChargingIdIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint32(data.chargingIdValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: chargingIdValue\n");
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
        errorStream.add("Unable to decode IE ChargingIdIe\n");
        return false;
    }
}
void ChargingIdIe::displayChargingIdIe_v(ChargingIdIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("ChargingIdIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("chargingIdValue: ");
    stream.add(data.chargingIdValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
