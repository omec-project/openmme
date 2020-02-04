/*
 * portNumberIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "portNumberIe.h"
#include "dataTypeCodecUtils.h"

PortNumberIe::PortNumberIe() 
{
    ieType = 126;
    // TODO

}

PortNumberIe::~PortNumberIe() {
    // TODO Auto-generated destructor stub
}

bool PortNumberIe::encodePortNumberIe(MsgBuffer &buffer, PortNumberIeData const &data)
{
    if (!(buffer.writeUint16(data.portNumber)))
    {
        errorStream.add("Encoding of portNumber failed\n");
        return false;
    }

    return true;
}

bool PortNumberIe::decodePortNumberIe(MsgBuffer &buffer, PortNumberIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint16(data.portNumber);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: portNumber\n");
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
        errorStream.add("Unable to decode IE PortNumberIe\n");
        return false;
    }
}
void PortNumberIe::displayPortNumberIe_v(PortNumberIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("PortNumberIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("portNumber: ");
    stream.add(data.portNumber);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
