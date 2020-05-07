/*
 * ebiIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "ebiIe.h"
#include "dataTypeCodecUtils.h"

EbiIe::EbiIe() 
{
    ieType = 73;
    // TODO

}

EbiIe::~EbiIe() {
    // TODO Auto-generated destructor stub
}

bool EbiIe::encodeEbiIe(MsgBuffer &buffer, EbiIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.epsBearerId, 4)))
    {
        errorStream.add("Encoding of epsBearerId failed\n");
        return false;
    }

    return true;
}

bool EbiIe::decodeEbiIe(MsgBuffer &buffer, EbiIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(4);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.epsBearerId = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: epsBearerId\n");
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
        errorStream.add("Unable to decode IE EbiIe\n");
        return false;
    }
}
void EbiIe::displayEbiIe_v(EbiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("EbiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "epsBearerId: "); 
    stream.add((Uint8)data.epsBearerId);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
