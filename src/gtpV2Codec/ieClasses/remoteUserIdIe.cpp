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


#include "remoteUserIdIe.h"
#include "dataTypeCodecUtils.h"

RemoteUserIdIe::RemoteUserIdIe() 
{
    ieType = 192;
    // TODO

}

RemoteUserIdIe::~RemoteUserIdIe() {
    // TODO Auto-generated destructor stub
}

bool RemoteUserIdIe::encodeRemoteUserIdIe(MsgBuffer &buffer, RemoteUserIdIeData const &data)
{
    buffer.skipBits(6);

    if(!(buffer.writeBits(data.imeifpresent, 1)))
    {
        errorStream.add((char *)"Encoding of imeifpresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.msisdnfpresent, 1)))
    {
        errorStream.add((char *)"Encoding of msisdnfpresent failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.lengthofIMSI)))
    {
        errorStream.add((char *)"Encoding of lengthofIMSI failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.imsi)))
    {
    errorStream.add((char *)"Encoding of imsi failed\n");
    return false;
    }
    if (!(buffer.writeUint8(data.lengthOfMSISDN)))
    {
        errorStream.add((char *)"Encoding of lengthOfMSISDN failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.msisdn)))
    {
    errorStream.add((char *)"Encoding of msisdn failed\n");
    return false;
    }
    if (!(buffer.writeUint8(data.lengthOfIMEI)))
    {
        errorStream.add((char *)"Encoding of lengthOfIMEI failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.imei)))
    {
    errorStream.add((char *)"Encoding of imei failed\n");
    return false;
    }

    return true;
}

bool RemoteUserIdIe::decodeRemoteUserIdIe(MsgBuffer &buffer, RemoteUserIdIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(6);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.imeifpresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: imeifpresent\n");
        return false;
    }
    data.msisdnfpresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: msisdnfpresent\n");
        return false;
    }

    buffer.readUint8(data.lengthofIMSI);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: lengthofIMSI\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.imsi, lengthLeft)))
    {
        errorStream.add((char *)"Failed to decode: imsi\n");
        return false;
    }

    buffer.readUint8(data.lengthOfMSISDN);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: lengthOfMSISDN\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.msisdn, lengthLeft)))
    {
        errorStream.add((char *)"Failed to decode: msisdn\n");
        return false;
    }

    buffer.readUint8(data.lengthOfIMEI);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: lengthOfIMEI\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.imei, lengthLeft)))
    {
        errorStream.add((char *)"Failed to decode: imei\n");
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
        errorStream.add((char *)"Unable to decode IE RemoteUserIdIe\n");
        return false;
    }
}
void RemoteUserIdIe::displayRemoteUserIdIe_v(RemoteUserIdIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"RemoteUserIdIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"imeifpresent: "); 
    stream.add((Uint8)data.imeifpresent);
    stream.endOfLine();
  
    stream.add( (char *)"msisdnfpresent: "); 
    stream.add((Uint8)data.msisdnfpresent);
    stream.endOfLine();
  
    stream.add((char *)"lengthofIMSI: ");
    stream.add(data.lengthofIMSI);
    stream.endOfLine();
  
    stream.add((char *)"imsi:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.imsi, stream);
  
    stream.add((char *)"lengthOfMSISDN: ");
    stream.add(data.lengthOfMSISDN);
    stream.endOfLine();
  
    stream.add((char *)"msisdn:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.msisdn, stream);
  
    stream.add((char *)"lengthOfIMEI: ");
    stream.add(data.lengthOfIMEI);
    stream.endOfLine();
  
    stream.add((char *)"imei:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.imei, stream);
    stream.decrIndent();
    stream.decrIndent();
}
