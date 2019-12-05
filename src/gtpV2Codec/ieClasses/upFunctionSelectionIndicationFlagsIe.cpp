/*
 * upFunctionSelectionIndicationFlagsIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "upFunctionSelectionIndicationFlagsIe.h"
#include "dataTypeCodecUtils.h"

UpFunctionSelectionIndicationFlagsIe::UpFunctionSelectionIndicationFlagsIe() 
{
    ieType = 202;
    // TODO

}

UpFunctionSelectionIndicationFlagsIe::~UpFunctionSelectionIndicationFlagsIe() {
    // TODO Auto-generated destructor stub
}

bool UpFunctionSelectionIndicationFlagsIe::encodeUpFunctionSelectionIndicationFlagsIe(MsgBuffer &buffer, UpFunctionSelectionIndicationFlagsIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.dcnr, 4)))
    {
        errorStream.add("Encoding of dcnr failed\n");
        return false;
    }

    return true;
}

bool UpFunctionSelectionIndicationFlagsIe::decodeUpFunctionSelectionIndicationFlagsIe(MsgBuffer &buffer, UpFunctionSelectionIndicationFlagsIeData &data, Uint16 length)
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

    data.dcnr = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: dcnr\n");
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
        errorStream.add("Unable to decode IE UpFunctionSelectionIndicationFlagsIe\n");
        return false;
    }
}
void UpFunctionSelectionIndicationFlagsIe::displayUpFunctionSelectionIndicationFlagsIe_v(UpFunctionSelectionIndicationFlagsIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("UpFunctionSelectionIndicationFlagsIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "dcnr: "); 
    stream.add((Uint8)data.dcnr);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
