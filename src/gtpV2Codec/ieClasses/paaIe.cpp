/*
 * Copyright (c) 2019, Infosys Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */ 


#include "paaIe.h"
#include "dataTypeCodecUtils.h"

PaaIe::PaaIe() 
{
    ieType = 79;
    // TODO

}

PaaIe::~PaaIe() {
    // TODO Auto-generated destructor stub
}

bool PaaIe::encodePaaIe(MsgBuffer &buffer, PaaIeData const &data)
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
    if (data.pdnType == 2 || data.pdnType == 3)
    {
        if (!(buffer.writeUint8(data.ipv6PrefixLength)))
        {
    errorStream.add((char *)"Encoding of ipv6PrefixLength failed\n");
    return false;
        }
    }
    if (data.pdnType == 2 || data.pdnType == 3)
    {
        if (!(DataTypeCodecUtils::encodeIpAddressV6(buffer, data.ipV6Address)))
        {
            errorStream.add((char *)"Encoding of ipV6Address failed\n");
            return false;
        }
    }
    if (data.pdnType == 1)
    {
        if (!(DataTypeCodecUtils::encodeIpAddressV4(buffer, data.ipV4Address)))
        {
            errorStream.add((char *)"Encoding of ipV4Address failed\n");
            return false;
        }
    }

    return true;
}

bool PaaIe::decodePaaIe(MsgBuffer &buffer, PaaIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
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

    if (data.pdnType == 2 || data.pdnType == 3)
    {

        buffer.readUint8(data.ipv6PrefixLength);
        if (buffer.getCurrentIndex() > ieBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond IE boundary: ipv6PrefixLength\n");
            return false;
        }
    }

    if (data.pdnType == 2 || data.pdnType == 3)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeIpAddressV6(buffer, data.ipV6Address, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: ipV6Address\n");
            return false;
        }
    }

    if (data.pdnType == 1)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeIpAddressV4(buffer, data.ipV4Address, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: ipV4Address\n");
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
        errorStream.add((char *)"Unable to decode IE PaaIe\n");
        return false;
    }
}
void PaaIe::displayPaaIe_v(PaaIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"PaaIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"pdnType: "); 
    stream.add((Uint8)data.pdnType);
    stream.endOfLine();
  
    if (data.pdnType == 2 || data.pdnType == 3)
    {
        stream.add((char *)"ipv6PrefixLength: ");
        stream.add(data.ipv6PrefixLength);
        stream.endOfLine();
    }
  
    if (data.pdnType == 2 || data.pdnType == 3)
    {
        stream.add((char *)"ipV6Address:");
        stream.endOfLine();
        DataTypeCodecUtils::displayIpAddressV6_v(data.ipV6Address, stream);
    }
  
    if (data.pdnType == 1)
    {
        stream.add((char *)"ipV4Address:");
        stream.endOfLine();
        DataTypeCodecUtils::displayIpAddressV4_v(data.ipV4Address, stream);
    }
    stream.decrIndent();
    stream.decrIndent();
}
