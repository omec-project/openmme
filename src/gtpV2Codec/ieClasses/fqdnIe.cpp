/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "fqdnIe.h"
#include "dataTypeCodecUtils.h"

FqdnIe::FqdnIe() 
{
    ieType = 136;
    // TODO

}

FqdnIe::~FqdnIe() {
    // TODO Auto-generated destructor stub
}

bool FqdnIe::encodeFqdnIe(MsgBuffer &buffer, FqdnIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array32(buffer, data.fqdn)))
    {
    errorStream.add((char *)"Encoding of fqdn failed\n");
    return false;
    }

    return true;
}

bool FqdnIe::decodeFqdnIe(MsgBuffer &buffer, FqdnIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    Uint16 lengthLeft = length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array32(buffer, data.fqdn, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: fqdn\n");
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
        errorStream.add((char *)"Unable to decode IE FqdnIe\n");
        return false;
    }
}
void FqdnIe::displayFqdnIe_v(FqdnIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"FqdnIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"fqdn:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array32_v(data.fqdn, stream);
    stream.decrIndent();
    stream.decrIndent();
}
