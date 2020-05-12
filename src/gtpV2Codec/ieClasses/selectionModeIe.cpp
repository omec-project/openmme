/*
 * selectionModeIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "selectionModeIe.h"
#include "dataTypeCodecUtils.h"

SelectionModeIe::SelectionModeIe() 
{
    ieType = 128;
    // TODO

}

SelectionModeIe::~SelectionModeIe() {
    // TODO Auto-generated destructor stub
}

bool SelectionModeIe::encodeSelectionModeIe(MsgBuffer &buffer, SelectionModeIeData const &data)
{
    buffer.skipBits(6);

    if(!(buffer.writeBits(data.selectionMode, 2)))
    {
        errorStream.add("Encoding of selectionMode failed\n");
        return false;
    }

    return true;
}

bool SelectionModeIe::decodeSelectionModeIe(MsgBuffer &buffer, SelectionModeIeData &data, Uint16 length)
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

    data.selectionMode = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: selectionMode\n");
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
        errorStream.add("Unable to decode IE SelectionModeIe\n");
        return false;
    }
}
void SelectionModeIe::displaySelectionModeIe_v(SelectionModeIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("SelectionModeIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "selectionMode: "); 
    stream.add((Uint8)data.selectionMode);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
