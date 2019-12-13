/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "servingNetworkIe.h"
#include "dataTypeCodecUtils.h"

ServingNetworkIe::ServingNetworkIe() 
{
    ieType = 83;
    // TODO

}

ServingNetworkIe::~ServingNetworkIe() {
    // TODO Auto-generated destructor stub
}

bool ServingNetworkIe::encodeServingNetworkIe(MsgBuffer &buffer, ServingNetworkIeData const &data)
{
    if(!(buffer.writeBits(data.mccDigit2, 4)))
    {
        errorStream.add((char *)"Encoding of mccDigit2 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mccDigit1, 4)))
    {
        errorStream.add((char *)"Encoding of mccDigit1 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit3, 4)))
    {
        errorStream.add((char *)"Encoding of mncDigit3 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mccDigit3, 4)))
    {
        errorStream.add((char *)"Encoding of mccDigit3 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit2, 4)))
    {
        errorStream.add((char *)"Encoding of mncDigit2 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit1, 4)))
    {
        errorStream.add((char *)"Encoding of mncDigit1 failed\n");
        return false;
    }

    return true;
}

bool ServingNetworkIe::decodeServingNetworkIe(MsgBuffer &buffer, ServingNetworkIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: mccDigit2\n");
        return false;
    }
    data.mccDigit1 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: mccDigit1\n");
        return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: mncDigit3\n");
        return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: mccDigit3\n");
        return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: mncDigit2\n");
        return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: mncDigit1\n");
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
        errorStream.add((char *)"Unable to decode IE ServingNetworkIe\n");
        return false;
    }
}
void ServingNetworkIe::displayServingNetworkIe_v(ServingNetworkIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ServingNetworkIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"mccDigit2: "); 
    stream.add((Uint8)data.mccDigit2);
    stream.endOfLine();
  
    stream.add( (char *)"mccDigit1: "); 
    stream.add((Uint8)data.mccDigit1);
    stream.endOfLine();
  
    stream.add( (char *)"mncDigit3: "); 
    stream.add((Uint8)data.mncDigit3);
    stream.endOfLine();
  
    stream.add( (char *)"mccDigit3: "); 
    stream.add((Uint8)data.mccDigit3);
    stream.endOfLine();
  
    stream.add( (char *)"mncDigit2: "); 
    stream.add((Uint8)data.mncDigit2);
    stream.endOfLine();
  
    stream.add( (char *)"mncDigit1: "); 
    stream.add((Uint8)data.mncDigit1);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
