/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "fTeidIe.h"
#include "dataTypeCodecUtils.h"

FTeidIe::FTeidIe() 
{
    ieType = 87;
    // TODO

}

FTeidIe::~FTeidIe() {
    // TODO Auto-generated destructor stub
}

bool FTeidIe::encodeFTeidIe(MsgBuffer &buffer, FTeidIeData const &data)
{
    if(!(buffer.writeBits(data.ipv4present, 1)))
    {
        errorStream.add((char *)"Encoding of ipv4present failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.ipv6present, 1)))
    {
        errorStream.add((char *)"Encoding of ipv6present failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.interfaceType, 6)))
    {
        errorStream.add((char *)"Encoding of interfaceType failed\n");
        return false;
    }
    if (!(buffer.writeUint32(data.teidGreKey)))
    {
        errorStream.add((char *)"Encoding of teidGreKey failed\n");
        return false;
    }
    if (data.ipv4present)
    {
        if (!(DataTypeCodecUtils::encodeIpAddressV4(buffer, data.ipV4Address)))
        {
            errorStream.add((char *)"Encoding of ipV4Address failed\n");
            return false;
        }
    }
    if (data.ipv6present)
    {
        if (!(DataTypeCodecUtils::encodeIpAddressV6(buffer, data.ipV6Address)))
        {
            errorStream.add((char *)"Encoding of ipV6Address failed\n");
            return false;
        }
    }

    return true;
}

bool FTeidIe::decodeFTeidIe(MsgBuffer &buffer, FTeidIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.ipv4present = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: ipv4present\n");
        return false;
    }
    data.ipv6present = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: ipv6present\n");
        return false;
    }
    data.interfaceType = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: interfaceType\n");
        return false;
    }

    buffer.readUint32(data.teidGreKey);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: teidGreKey\n");
        return false;
    }

    Uint16 lengthLeft = length;

    if (data.ipv4present)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeIpAddressV4(buffer, data.ipV4Address, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: ipV4Address\n");
            return false;
        }
    }

    if (data.ipv6present)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeIpAddressV6(buffer, data.ipV6Address, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: ipV6Address\n");
            return false;
        }
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
        errorStream.add((char *)"Unable to decode IE FTeidIe\n");
        return false;
    }
}
void FTeidIe::displayFTeidIe_v(FTeidIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"FTeidIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"ipv4present: "); 
    stream.add((Uint8)data.ipv4present);
    stream.endOfLine();
  
    stream.add( (char *)"ipv6present: "); 
    stream.add((Uint8)data.ipv6present);
    stream.endOfLine();
  
    stream.add( (char *)"interfaceType: "); 
    stream.add((Uint8)data.interfaceType);
    stream.endOfLine();
  
    stream.add((char *)"teidGreKey: ");
    stream.add(data.teidGreKey);
    stream.endOfLine();
  
    if (data.ipv4present)
    {
        stream.add((char *)"ipV4Address:");
        stream.endOfLine();
        DataTypeCodecUtils::displayIpAddressV4_v(data.ipV4Address, stream);
    }
  
    if (data.ipv6present)
    {
        stream.add((char *)"ipV6Address:");
        stream.endOfLine();
        DataTypeCodecUtils::displayIpAddressV6_v(data.ipV6Address, stream);
    }
    stream.decrIndent();
    stream.decrIndent();
}
