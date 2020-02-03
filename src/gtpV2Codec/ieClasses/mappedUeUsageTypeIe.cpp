/*
 * mappedUeUsageTypeIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "mappedUeUsageTypeIe.h"
#include "dataTypeCodecUtils.h"

MappedUeUsageTypeIe::MappedUeUsageTypeIe() 
{
    ieType = 200;
    // TODO

}

MappedUeUsageTypeIe::~MappedUeUsageTypeIe() {
    // TODO Auto-generated destructor stub
}

bool MappedUeUsageTypeIe::encodeMappedUeUsageTypeIe(MsgBuffer &buffer, MappedUeUsageTypeIeData const &data)
{
    if (!(buffer.writeUint16(data.mappedUEUsageType)))
    {
        errorStream.add("Encoding of mappedUEUsageType failed\n");
        return false;
    }

    return true;
}

bool MappedUeUsageTypeIe::decodeMappedUeUsageTypeIe(MsgBuffer &buffer, MappedUeUsageTypeIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint16(data.mappedUEUsageType);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mappedUEUsageType\n");
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
        errorStream.add("Unable to decode IE MappedUeUsageTypeIe\n");
        return false;
    }
}
void MappedUeUsageTypeIe::displayMappedUeUsageTypeIe_v(MappedUeUsageTypeIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("MappedUeUsageTypeIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("mappedUEUsageType: ");
    stream.add(data.mappedUEUsageType);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
