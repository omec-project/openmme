/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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
        errorStream.add((char *)"Encoding of portNumber failed\n");
        return false;
    }

    return true;
}

bool PortNumberIe::decodePortNumberIe(MsgBuffer &buffer, PortNumberIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint16(data.portNumber);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: portNumber\n");
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
        errorStream.add((char *)"Unable to decode IE PortNumberIe\n");
        return false;
    }
}
void PortNumberIe::displayPortNumberIe_v(PortNumberIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"PortNumberIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"portNumber: ");
    stream.add(data.portNumber);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
