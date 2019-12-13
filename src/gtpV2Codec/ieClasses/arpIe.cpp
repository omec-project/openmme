/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "arpIe.h"
#include "dataTypeCodecUtils.h"

ArpIe::ArpIe() 
{
    ieType = 155;
    // TODO

}

ArpIe::~ArpIe() {
    // TODO Auto-generated destructor stub
}

bool ArpIe::encodeArpIe(MsgBuffer &buffer, ArpIeData const &data)
{
    buffer.skipBits(1);

    if(!(buffer.writeBits(data.pci, 1)))
    {
        errorStream.add((char *)"Encoding of pci failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.pl, 4)))
    {
        errorStream.add((char *)"Encoding of pl failed\n");
        return false;
    }
    buffer.skipBits(1);

    if(!(buffer.writeBits(data.pvi, 1)))
    {
        errorStream.add((char *)"Encoding of pvi failed\n");
        return false;
    }

    return true;
}

bool ArpIe::decodeArpIe(MsgBuffer &buffer, ArpIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(1);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.pci = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: pci\n");
        return false;
    }
    data.pl = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: pl\n");
        return false;
    }
    buffer.skipBits(1);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.pvi = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: pvi\n");
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
        errorStream.add((char *)"Unable to decode IE ArpIe\n");
        return false;
    }
}
void ArpIe::displayArpIe_v(ArpIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ArpIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"pci: "); 
    stream.add((Uint8)data.pci);
    stream.endOfLine();
  
    stream.add( (char *)"pl: "); 
    stream.add((Uint8)data.pl);
    stream.endOfLine();
  
    stream.add( (char *)"pvi: "); 
    stream.add((Uint8)data.pvi);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
