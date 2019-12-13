/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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
        errorStream.add((char *)"Encoding of dcnr failed\n");
        return false;
    }

    return true;
}

bool UpFunctionSelectionIndicationFlagsIe::decodeUpFunctionSelectionIndicationFlagsIe(MsgBuffer &buffer, UpFunctionSelectionIndicationFlagsIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(4);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.dcnr = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: dcnr\n");
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
        errorStream.add((char *)"Unable to decode IE UpFunctionSelectionIndicationFlagsIe\n");
        return false;
    }
}
void UpFunctionSelectionIndicationFlagsIe::displayUpFunctionSelectionIndicationFlagsIe_v(UpFunctionSelectionIndicationFlagsIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"UpFunctionSelectionIndicationFlagsIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"dcnr: "); 
    stream.add((Uint8)data.dcnr);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
