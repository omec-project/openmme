/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "fqCsidIe.h"
#include "dataTypeCodecUtils.h"

FqCsidIe::FqCsidIe() 
{
    ieType = 132;
    // TODO

}

FqCsidIe::~FqCsidIe() {
    // TODO Auto-generated destructor stub
}

bool FqCsidIe::encodeFqCsidIe(MsgBuffer &buffer, FqCsidIeData const &data)
{
    if(!(buffer.writeBits(data.nodeIdType, 4)))
    {
        errorStream.add((char *)"Encoding of nodeIdType failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfCsids, 4)))
    {
        errorStream.add((char *)"Encoding of numberOfCsids failed\n");
        return false;
    }
    if (data.nodeIdType == 0)
    {
        if (!(DataTypeCodecUtils::encodeIpAddressV4(buffer, data.nodeIdIpv4)))
        {
            errorStream.add((char *)"Encoding of nodeIdIpv4 failed\n");
            return false;
        }
    }
    if (data.nodeIdType == 1)
    {
        if (!(DataTypeCodecUtils::encodeIpAddressV6(buffer, data.nodeIdIpv6)))
        {
            errorStream.add((char *)"Encoding of nodeIdIpv6 failed\n");
            return false;
        }
    }
    if (data.nodeIdType == 2)
    {
        if (!(buffer.writeUint32(data.nodeIdUint32)))
        {
    errorStream.add((char *)"Encoding of nodeIdUint32 failed\n");
    return false;
        }
    }
    if (!(DataTypeCodecUtils::encodeUint16Array16(buffer, data.csidList)))
    {
    errorStream.add((char *)"Encoding of csidList failed\n");
    return false;
    }

    return true;
}

bool FqCsidIe::decodeFqCsidIe(MsgBuffer &buffer, FqCsidIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.nodeIdType = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: nodeIdType\n");
        return false;
    }
    data.numberOfCsids = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfCsids\n");
        return false;
    }

    Uint16 lengthLeft = length;

    if (data.nodeIdType == 0)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeIpAddressV4(buffer, data.nodeIdIpv4, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: nodeIdIpv4\n");
            return false;
        }
    }

    if (data.nodeIdType == 1)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeIpAddressV6(buffer, data.nodeIdIpv6, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: nodeIdIpv6\n");
            return false;
        }
    }

    if (data.nodeIdType == 2)
    {

        buffer.readUint32(data.nodeIdUint32);
        if (buffer.getCurrentIndex() > ieBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond IE boundary: nodeIdUint32\n");
            return false;
        }
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint16Array16(buffer, data.csidList, lengthLeft, data.numberOfCsids)))
    {
        errorStream.add((char *)"Failed to decode: csidList\n");
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
        errorStream.add((char *)"Unable to decode IE FqCsidIe\n");
        return false;
    }
}
void FqCsidIe::displayFqCsidIe_v(FqCsidIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"FqCsidIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"nodeIdType: "); 
    stream.add((Uint8)data.nodeIdType);
    stream.endOfLine();
  
    stream.add( (char *)"numberOfCsids: "); 
    stream.add((Uint8)data.numberOfCsids);
    stream.endOfLine();
  
    if (data.nodeIdType == 0)
    {
        stream.add((char *)"nodeIdIpv4:");
        stream.endOfLine();
        DataTypeCodecUtils::displayIpAddressV4_v(data.nodeIdIpv4, stream);
    }
  
    if (data.nodeIdType == 1)
    {
        stream.add((char *)"nodeIdIpv6:");
        stream.endOfLine();
        DataTypeCodecUtils::displayIpAddressV6_v(data.nodeIdIpv6, stream);
    }
  
    if (data.nodeIdType == 2)
    {
        stream.add((char *)"nodeIdUint32: ");
        stream.add(data.nodeIdUint32);
        stream.endOfLine();
    }
  
    stream.add((char *)"csidList:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint16Array16_v(data.csidList, stream);
    stream.decrIndent();
    stream.decrIndent();
}
