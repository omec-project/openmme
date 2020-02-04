/*
 * ambrMmbrIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "ambrMmbrIe.h"
#include "dataTypeCodecUtils.h"

AmbrMmbrIe::AmbrMmbrIe() 
{
    ieType = 161;
    // TODO

}

AmbrMmbrIe::~AmbrMmbrIe() {
    // TODO Auto-generated destructor stub
}

bool AmbrMmbrIe::encodeAmbrMmbrIe(MsgBuffer &buffer, AmbrMmbrIeData const &data)
{
    if (!(buffer.writeUint32(data.maxMbrUplink)))
    {
        errorStream.add("Encoding of maxMbrUplink failed\n");
        return false;
    }
    if (!(buffer.writeUint32(data.maxMbrDownlink)))
    {
        errorStream.add("Encoding of maxMbrDownlink failed\n");
        return false;
    }

    return true;
}

bool AmbrMmbrIe::decodeAmbrMmbrIe(MsgBuffer &buffer, AmbrMmbrIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint32(data.maxMbrUplink);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: maxMbrUplink\n");
        return false;
    }

    buffer.readUint32(data.maxMbrDownlink);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: maxMbrDownlink\n");
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
        errorStream.add("Unable to decode IE AmbrMmbrIe\n");
        return false;
    }
}
void AmbrMmbrIe::displayAmbrMmbrIe_v(AmbrMmbrIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("AmbrMmbrIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("maxMbrUplink: ");
    stream.add(data.maxMbrUplink);
    stream.endOfLine();
  
    stream.add("maxMbrDownlink: ");
    stream.add(data.maxMbrDownlink);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
