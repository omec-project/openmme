/*
 * fContainerIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "fContainerIe.h"
#include "dataTypeCodecUtils.h"

FContainerIe::FContainerIe() 
{
    ieType = 118;
    // TODO

}

FContainerIe::~FContainerIe() {
    // TODO Auto-generated destructor stub
}

bool FContainerIe::encodeFContainerIe(MsgBuffer &buffer, FContainerIeData const &data)
{
    buffer.skipBits(4);

    if (!(data.containerType<= 4))
    {
        errorStream.add("Data validation failure: containerType\n");
        return false; 
    }
    if(!(buffer.writeBits(data.containerType, 4)))
    {
        errorStream.add("Encoding of containerType failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.fContainerField)))
    {
        errorStream.add("Encoding of fContainerField failed\n");
        return false;
    }

    return true;
}

bool FContainerIe::decodeFContainerIe(MsgBuffer &buffer, FContainerIeData &data, Uint16 length)
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

    data.containerType = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: containerType\n");
        return false;
    }
    if (!(data.containerType<= 4))
    {
        errorStream.add("Data validation failure : containerType\n");
        return false; //TODO need to add validations
    }

    buffer.readUint8(data.fContainerField);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: fContainerField\n");
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
        errorStream.add("Unable to decode IE FContainerIe\n");
        return false;
    }
}
void FContainerIe::displayFContainerIe_v(FContainerIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("FContainerIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "containerType: "); 
    stream.add((Uint8)data.containerType);
    stream.endOfLine();
  
    stream.add("fContainerField: ");
    stream.add(data.fContainerField);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
