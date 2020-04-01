/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "additionalProtocolConfigurationOptionsIe.h"
#include "dataTypeCodecUtils.h"

AdditionalProtocolConfigurationOptionsIe::AdditionalProtocolConfigurationOptionsIe() 
{
    ieType = 163;
    // TODO

}

AdditionalProtocolConfigurationOptionsIe::~AdditionalProtocolConfigurationOptionsIe() {
    // TODO Auto-generated destructor stub
}

bool AdditionalProtocolConfigurationOptionsIe::encodeAdditionalProtocolConfigurationOptionsIe(MsgBuffer &buffer, AdditionalProtocolConfigurationOptionsIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.apco)))
    {
    errorStream.add((char *)"Encoding of apco failed\n");
    return false;
    }

    return true;
}

bool AdditionalProtocolConfigurationOptionsIe::decodeAdditionalProtocolConfigurationOptionsIe(MsgBuffer &buffer, AdditionalProtocolConfigurationOptionsIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    Uint16 lengthLeft = length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.apco, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: apco\n");
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
        errorStream.add((char *)"Unable to decode IE AdditionalProtocolConfigurationOptionsIe\n");
        return false;
    }
}
void AdditionalProtocolConfigurationOptionsIe::displayAdditionalProtocolConfigurationOptionsIe_v(AdditionalProtocolConfigurationOptionsIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"AdditionalProtocolConfigurationOptionsIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"apco:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array16_v(data.apco, stream);
    stream.decrIndent();
    stream.decrIndent();
}
