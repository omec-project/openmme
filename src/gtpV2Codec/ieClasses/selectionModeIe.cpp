/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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
        errorStream.add((char *)"Encoding of selectionMode failed\n");
        return false;
    }

    return true;
}

bool SelectionModeIe::decodeSelectionModeIe(MsgBuffer &buffer, SelectionModeIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(6);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.selectionMode = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: selectionMode\n");
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
        errorStream.add((char *)"Unable to decode IE SelectionModeIe\n");
        return false;
    }
}
void SelectionModeIe::displaySelectionModeIe_v(SelectionModeIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"SelectionModeIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"selectionMode: "); 
    stream.add((Uint8)data.selectionMode);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
