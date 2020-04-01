/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "ipAddressIe.h"
#include "dataTypeCodecUtils.h"

IpAddressIe::IpAddressIe() 
{
    ieType = 74;
    // TODO

}

IpAddressIe::~IpAddressIe() {
    // TODO Auto-generated destructor stub
}

bool IpAddressIe::encodeIpAddressIe(MsgBuffer &buffer, IpAddressIeData const &data)
{
    if (data.ipAddressV4Present)
    {
        if (!(DataTypeCodecUtils::encodeIpAddressV4(buffer, data.ipAddressV4)))
        {
            errorStream.add((char *)"Encoding of ipAddressV4 failed\n");
            return false;
        }
    }
    if (data.ipAddressV6Present)
    {
        if (!(DataTypeCodecUtils::encodeIpAddressV6(buffer, data.ipAddressV6)))
        {
            errorStream.add((char *)"Encoding of ipAddressV6 failed\n");
            return false;
        }
    }

    return true;
}

bool IpAddressIe::decodeIpAddressIe(MsgBuffer &buffer, IpAddressIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    Uint16 lengthLeft = length;

    if (length == 4)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeIpAddressV4(buffer, data.ipAddressV4, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: ipAddressV4\n");
            return false;
        }
        data.ipAddressV4Present = true;
    }

    if (length == 6)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeIpAddressV6(buffer, data.ipAddressV6, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: ipAddressV6\n");
            return false;
        }
        data.ipAddressV6Present = true;
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
        errorStream.add((char *)"Unable to decode IE IpAddressIe\n");
        return false;
    }
}
void IpAddressIe::displayIpAddressIe_v(IpAddressIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"IpAddressIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    if (data.ipAddressV4Present)
    {
        stream.add((char *)"ipAddressV4:");
        stream.endOfLine();
        DataTypeCodecUtils::displayIpAddressV4_v(data.ipAddressV4, stream);
    }   
  
    if (data.ipAddressV6Present)
    {
        stream.add((char *)"ipAddressV6:");
        stream.endOfLine();
        DataTypeCodecUtils::displayIpAddressV6_v(data.ipAddressV6, stream);
    }   
    stream.decrIndent();
    stream.decrIndent();
}
