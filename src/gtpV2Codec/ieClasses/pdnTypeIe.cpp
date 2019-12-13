/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "pdnTypeIe.h"
#include "dataTypeCodecUtils.h"

PdnTypeIe::PdnTypeIe() 
{
    ieType = 99;
    // TODO

}

PdnTypeIe::~PdnTypeIe() {
    // TODO Auto-generated destructor stub
}

bool PdnTypeIe::encodePdnTypeIe(MsgBuffer &buffer, PdnTypeIeData const &data)
{
    buffer.skipBits(5);

    if (!(data.pdnType<= 3))
    {
        errorStream.add((char *)"Data validation failure: pdnType\n");
        return false; 
    }
    if(!(buffer.writeBits(data.pdnType, 3)))
    {
        errorStream.add((char *)"Encoding of pdnType failed\n");
        return false;
    }

    return true;
}

bool PdnTypeIe::decodePdnTypeIe(MsgBuffer &buffer, PdnTypeIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(5);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.pdnType = buffer.readBits(3);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: pdnType\n");
        return false;
    }
    if (!(data.pdnType<= 3))
    {
        errorStream.add((char *)"Data validation failure : pdnType\n");
        return false; //TODO need to add validations
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
        errorStream.add((char *)"Unable to decode IE PdnTypeIe\n");
        return false;
    }
}
void PdnTypeIe::displayPdnTypeIe_v(PdnTypeIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"PdnTypeIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"pdnType: "); 
    stream.add((Uint8)data.pdnType);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
