/*
 * remoteUserIdIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
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
        errorStream.add("Encoding of imeifpresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.msisdnfpresent, 1)))
    {
        errorStream.add("Encoding of msisdnfpresent failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.lengthofIMSI)))
    {
        errorStream.add("Encoding of lengthofIMSI failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.imsi)))
    {
    errorStream.add("Encoding of imsi failed\n");
    return false;
    }
    if (!(buffer.writeUint8(data.lengthOfMSISDN)))
    {
        errorStream.add("Encoding of lengthOfMSISDN failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.msisdn)))
    {
    errorStream.add("Encoding of msisdn failed\n");
    return false;
    }
    if (!(buffer.writeUint8(data.lengthOfIMEI)))
    {
        errorStream.add("Encoding of lengthOfIMEI failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.imei)))
    {
    errorStream.add("Encoding of imei failed\n");
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
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.imeifpresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: imeifpresent\n");
        return false;
    }
    data.msisdnfpresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: msisdnfpresent\n");
        return false;
    }

    buffer.readUint8(data.lengthofIMSI);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: lengthofIMSI\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.imsi, lengthLeft)))
    {
        errorStream.add("Failed to decode: imsi\n");
        return false;
    }

    buffer.readUint8(data.lengthOfMSISDN);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: lengthOfMSISDN\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.msisdn, lengthLeft)))
    {
        errorStream.add("Failed to decode: msisdn\n");
        return false;
    }

    buffer.readUint8(data.lengthOfIMEI);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: lengthOfIMEI\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.imei, lengthLeft)))
    {
        errorStream.add("Failed to decode: imei\n");
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
        errorStream.add("Unable to decode IE RemoteUserIdIe\n");
        return false;
    }
}
void RemoteUserIdIe::displayRemoteUserIdIe_v(RemoteUserIdIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("RemoteUserIdIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "imeifpresent: "); 
    stream.add((Uint8)data.imeifpresent);
    stream.endOfLine();
  
    stream.add( "msisdnfpresent: "); 
    stream.add((Uint8)data.msisdnfpresent);
    stream.endOfLine();
  
    stream.add("lengthofIMSI: ");
    stream.add(data.lengthofIMSI);
    stream.endOfLine();
  
    stream.add("imsi:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.imsi, stream);
  
    stream.add("lengthOfMSISDN: ");
    stream.add(data.lengthOfMSISDN);
    stream.endOfLine();
  
    stream.add("msisdn:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.msisdn, stream);
  
    stream.add("lengthOfIMEI: ");
    stream.add(data.lengthOfIMEI);
    stream.endOfLine();
  
    stream.add("imei:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.imei, stream);
    stream.decrIndent();
    stream.decrIndent();
}
