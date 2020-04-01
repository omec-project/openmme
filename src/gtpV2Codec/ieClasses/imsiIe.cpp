/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "imsiIe.h"
#include "dataTypeCodecUtils.h"

ImsiIe::ImsiIe() 
{
    ieType = 1;
    // TODO

}

ImsiIe::~ImsiIe() {
    // TODO Auto-generated destructor stub
}

bool ImsiIe::encodeImsiIe(MsgBuffer &buffer, ImsiIeData const &data)
{
    if (!(data.imsiValue.length>=9 && data.imsiValue.length <=15))
    {
        errorStream.add((char *)"Data validation failure: imsiValue\n");
        return false; 
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.imsiValue)))
    {
    errorStream.add((char *)"Encoding of imsiValue failed\n");
    return false;
    }

    return true;
}

bool ImsiIe::decodeImsiIe(MsgBuffer &buffer, ImsiIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    Uint16 lengthLeft = length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.imsiValue, lengthLeft)))
    {
        errorStream.add((char *)"Failed to decode: imsiValue\n");
        return false;
    }
    if (!(data.imsiValue.length>=9 && data.imsiValue.length <=15))
    {
        errorStream.add((char *)"Data validation failure : imsiValue\n");
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
        errorStream.add((char *)"Unable to decode IE ImsiIe\n");
        return false;
    }
}
void ImsiIe::displayImsiIe_v(ImsiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ImsiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"imsiValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.imsiValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
