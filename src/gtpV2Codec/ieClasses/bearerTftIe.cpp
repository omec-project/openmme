/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "bearerTftIe.h"
#include "dataTypeCodecUtils.h"

BearerTftIe::BearerTftIe() 
{
    ieType = 84;
    // TODO

}

BearerTftIe::~BearerTftIe() {
    // TODO Auto-generated destructor stub
}

bool BearerTftIe::encodeBearerTftIe(MsgBuffer &buffer, BearerTftIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.tft)))
    {
    errorStream.add((char *)"Encoding of tft failed\n");
    return false;
    }

    return true;
}

bool BearerTftIe::decodeBearerTftIe(MsgBuffer &buffer, BearerTftIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    Uint16 lengthLeft = length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.tft, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: tft\n");
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
        errorStream.add((char *)"Unable to decode IE BearerTftIe\n");
        return false;
    }
}
void BearerTftIe::displayBearerTftIe_v(BearerTftIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"BearerTftIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"tft:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array16_v(data.tft, stream);
    stream.decrIndent();
    stream.decrIndent();
}
