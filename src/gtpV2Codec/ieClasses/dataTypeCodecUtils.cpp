/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include "dataTypeCodecUtils.h"

// TODO

DataTypeCodecUtils::DataTypeCodecUtils()
{
    // TODO
}

DataTypeCodecUtils::~DataTypeCodecUtils() {
    // TODO Auto-generated destructor stub
}


bool DataTypeCodecUtils::encodeCgiField(MsgBuffer &buffer, CgiField const &data)
{
    buffer.writeBits(data.mccDigit2, 4);
    buffer.writeBits(data.mccDigit1, 4);
    buffer.writeBits(data.mncDigit3, 4);
    buffer.writeBits(data.mccDigit3, 4);
    buffer.writeBits(data.mncDigit2, 4);
    buffer.writeBits(data.mncDigit1, 4);
    buffer.writeUint16(data.locationAreaCode);
    buffer.writeUint16(data.cellIdentity);
    return true;
}

bool DataTypeCodecUtils::decodeCgiField(MsgBuffer &buffer,CgiField &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit2\n");
         return false;
    }
    data.mccDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit1\n");
         return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit3\n");
         return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit3\n");
         return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit2\n");
         return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit1\n");
         return false;
    }

    buffer.readUint16(data.locationAreaCode);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: locationAreaCode\n");
         return false;
    }

    buffer.readUint16(data.cellIdentity);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: cellIdentity\n");
         return false;
    }

  return true;
}

void DataTypeCodecUtils::displayCgiField_v(CgiField const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"CgiField:");
    stream.incrIndent();
    stream.endOfLine();
    stream.add((char *)"mccDigit2 = ");
    stream.add(data.mccDigit2);
    stream.endOfLine();
    stream.add((char *)"mccDigit1 = ");
    stream.add(data.mccDigit1);
    stream.endOfLine();
    stream.add((char *)"mncDigit3 = ");
    stream.add(data.mncDigit3);
    stream.endOfLine();
    stream.add((char *)"mccDigit3 = ");
    stream.add(data.mccDigit3);
    stream.endOfLine();
    stream.add((char *)"mncDigit2 = ");
    stream.add(data.mncDigit2);
    stream.endOfLine();
    stream.add((char *)"mncDigit1 = ");
    stream.add(data.mncDigit1);
    stream.endOfLine();
    stream.add((char *)"locationAreaCode = ");
    stream.add(data.locationAreaCode);
    stream.endOfLine();
    stream.add((char *)"cellIdentity = ");
    stream.add(data.cellIdentity);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeOffendingIeData(MsgBuffer &buffer, OffendingIeData const &data)
{
    buffer.writeUint8(data.typeOfOffendingIe);
    buffer.skipBits(4);

    buffer.writeUint16(data.lengthOfOffendingIe);
    buffer.writeBits(data.instanceOfOffendingIe, 4);
    return true;
}

bool DataTypeCodecUtils::decodeOffendingIeData(MsgBuffer &buffer,OffendingIeData &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.typeOfOffendingIe);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: typeOfOffendingIe\n");
         return false;
    }
    buffer.skipBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond type boundary: \n");
        return false;
    }

    buffer.readUint16(data.lengthOfOffendingIe);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: lengthOfOffendingIe\n");
         return false;
    }
    data.instanceOfOffendingIe = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: instanceOfOffendingIe\n");
         return false;
    }

  return true;
}

void DataTypeCodecUtils::displayOffendingIeData_v(OffendingIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"OffendingIeData:");
    stream.incrIndent();
    stream.endOfLine();
    stream.add((char *)"typeOfOffendingIe = ");
    stream.add(data.typeOfOffendingIe);
    stream.endOfLine();
    stream.add((char *)"lengthOfOffendingIe = ");
    stream.add(data.lengthOfOffendingIe);
    stream.endOfLine();
    stream.add((char *)"instanceOfOffendingIe = ");
    stream.add(data.instanceOfOffendingIe);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeSaiField(MsgBuffer &buffer, SaiField const &data)
{
    buffer.writeBits(data.mccDigit2, 4);
    buffer.writeBits(data.mccDigit1, 4);
    buffer.writeBits(data.mncDigit3, 4);
    buffer.writeBits(data.mccDigit3, 4);
    buffer.writeBits(data.mncDigit2, 4);
    buffer.writeBits(data.mncDigit1, 4);
    buffer.writeUint16(data.locationAreaCode);
    buffer.writeUint16(data.serviceAreaCode);
    return true;
}

bool DataTypeCodecUtils::decodeSaiField(MsgBuffer &buffer,SaiField &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit2\n");
         return false;
    }
    data.mccDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit1\n");
         return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit3\n");
         return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit3\n");
         return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit2\n");
         return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit1\n");
         return false;
    }

    buffer.readUint16(data.locationAreaCode);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: locationAreaCode\n");
         return false;
    }

    buffer.readUint16(data.serviceAreaCode);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: serviceAreaCode\n");
         return false;
    }

  return true;
}

void DataTypeCodecUtils::displaySaiField_v(SaiField const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"SaiField:");
    stream.incrIndent();
    stream.endOfLine();
    stream.add((char *)"mccDigit2 = ");
    stream.add(data.mccDigit2);
    stream.endOfLine();
    stream.add((char *)"mccDigit1 = ");
    stream.add(data.mccDigit1);
    stream.endOfLine();
    stream.add((char *)"mncDigit3 = ");
    stream.add(data.mncDigit3);
    stream.endOfLine();
    stream.add((char *)"mccDigit3 = ");
    stream.add(data.mccDigit3);
    stream.endOfLine();
    stream.add((char *)"mncDigit2 = ");
    stream.add(data.mncDigit2);
    stream.endOfLine();
    stream.add((char *)"mncDigit1 = ");
    stream.add(data.mncDigit1);
    stream.endOfLine();
    stream.add((char *)"locationAreaCode = ");
    stream.add(data.locationAreaCode);
    stream.endOfLine();
    stream.add((char *)"serviceAreaCode = ");
    stream.add(data.serviceAreaCode);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeRaiField(MsgBuffer &buffer, RaiField const &data)
{
    buffer.writeBits(data.mccDigit2, 4);
    buffer.writeBits(data.mccDigit1, 4);
    buffer.writeBits(data.mncDigit3, 4);
    buffer.writeBits(data.mccDigit3, 4);
    buffer.writeBits(data.mncDigit2, 4);
    buffer.writeBits(data.mncDigit1, 4);
    buffer.writeUint16(data.locationAreaCode);
    buffer.writeUint16(data.routintAreaCode);
    return true;
}

bool DataTypeCodecUtils::decodeRaiField(MsgBuffer &buffer,RaiField &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit2\n");
         return false;
    }
    data.mccDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit1\n");
         return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit3\n");
         return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit3\n");
         return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit2\n");
         return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit1\n");
         return false;
    }

    buffer.readUint16(data.locationAreaCode);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: locationAreaCode\n");
         return false;
    }

    buffer.readUint16(data.routintAreaCode);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: routintAreaCode\n");
         return false;
    }

  return true;
}

void DataTypeCodecUtils::displayRaiField_v(RaiField const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"RaiField:");
    stream.incrIndent();
    stream.endOfLine();
    stream.add((char *)"mccDigit2 = ");
    stream.add(data.mccDigit2);
    stream.endOfLine();
    stream.add((char *)"mccDigit1 = ");
    stream.add(data.mccDigit1);
    stream.endOfLine();
    stream.add((char *)"mncDigit3 = ");
    stream.add(data.mncDigit3);
    stream.endOfLine();
    stream.add((char *)"mccDigit3 = ");
    stream.add(data.mccDigit3);
    stream.endOfLine();
    stream.add((char *)"mncDigit2 = ");
    stream.add(data.mncDigit2);
    stream.endOfLine();
    stream.add((char *)"mncDigit1 = ");
    stream.add(data.mncDigit1);
    stream.endOfLine();
    stream.add((char *)"locationAreaCode = ");
    stream.add(data.locationAreaCode);
    stream.endOfLine();
    stream.add((char *)"routintAreaCode = ");
    stream.add(data.routintAreaCode);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeTaiField(MsgBuffer &buffer, TaiField const &data)
{
    buffer.writeBits(data.mccDigit2, 4);
    buffer.writeBits(data.mccDigit1, 4);
    buffer.writeBits(data.mncDigit3, 4);
    buffer.writeBits(data.mccDigit3, 4);
    buffer.writeBits(data.mncDigit2, 4);
    buffer.writeBits(data.mncDigit1, 4);
    buffer.writeUint16(data.trackingAreaCode);
    return true;
}

bool DataTypeCodecUtils::decodeTaiField(MsgBuffer &buffer,TaiField &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit2\n");
         return false;
    }
    data.mccDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit1\n");
         return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit3\n");
         return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit3\n");
         return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit2\n");
         return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit1\n");
         return false;
    }

    buffer.readUint16(data.trackingAreaCode);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: trackingAreaCode\n");
         return false;
    }

  return true;
}

void DataTypeCodecUtils::displayTaiField_v(TaiField const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"TaiField:");
    stream.incrIndent();
    stream.endOfLine();
    stream.add((char *)"mccDigit2 = ");
    stream.add(data.mccDigit2);
    stream.endOfLine();
    stream.add((char *)"mccDigit1 = ");
    stream.add(data.mccDigit1);
    stream.endOfLine();
    stream.add((char *)"mncDigit3 = ");
    stream.add(data.mncDigit3);
    stream.endOfLine();
    stream.add((char *)"mccDigit3 = ");
    stream.add(data.mccDigit3);
    stream.endOfLine();
    stream.add((char *)"mncDigit2 = ");
    stream.add(data.mncDigit2);
    stream.endOfLine();
    stream.add((char *)"mncDigit1 = ");
    stream.add(data.mncDigit1);
    stream.endOfLine();
    stream.add((char *)"trackingAreaCode = ");
    stream.add(data.trackingAreaCode);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeEcgiField(MsgBuffer &buffer, EcgiField const &data)
{
    buffer.writeBits(data.mccDigit2, 4);
    buffer.writeBits(data.mccDigit1, 4);
    buffer.writeBits(data.mncDigit3, 4);
    buffer.writeBits(data.mccDigit3, 4);
    buffer.writeBits(data.mncDigit2, 4);
    buffer.writeBits(data.mncDigit1, 4);
    if (!(data.eUtranCellId<0x0FFFFFFF))
    {
         errorStream.add((char *)"Data validation failure: eUtranCellId\n"); 
         return false; //TODO need to add validations
    }
    buffer.writeUint32(data.eUtranCellId);
    return true;
}

bool DataTypeCodecUtils::decodeEcgiField(MsgBuffer &buffer,EcgiField &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit2\n");
         return false;
    }
    data.mccDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit1\n");
         return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit3\n");
         return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit3\n");
         return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit2\n");
         return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit1\n");
         return false;
    }

    buffer.readUint32(data.eUtranCellId);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: eUtranCellId\n");
         return false;
    }
    if (!(data.eUtranCellId<0x0FFFFFFF))
    {
         errorStream.add((char *)"Data validation failure: eUtranCellId\n");
         return false; //TODO need to add validations
    }

  return true;
}

void DataTypeCodecUtils::displayEcgiField_v(EcgiField const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"EcgiField:");
    stream.incrIndent();
    stream.endOfLine();
    stream.add((char *)"mccDigit2 = ");
    stream.add(data.mccDigit2);
    stream.endOfLine();
    stream.add((char *)"mccDigit1 = ");
    stream.add(data.mccDigit1);
    stream.endOfLine();
    stream.add((char *)"mncDigit3 = ");
    stream.add(data.mncDigit3);
    stream.endOfLine();
    stream.add((char *)"mccDigit3 = ");
    stream.add(data.mccDigit3);
    stream.endOfLine();
    stream.add((char *)"mncDigit2 = ");
    stream.add(data.mncDigit2);
    stream.endOfLine();
    stream.add((char *)"mncDigit1 = ");
    stream.add(data.mncDigit1);
    stream.endOfLine();
    stream.add((char *)"eUtranCellId = ");
    stream.add(data.eUtranCellId);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeLaiField(MsgBuffer &buffer, LaiField const &data)
{
    buffer.writeBits(data.mccDigit2, 4);
    buffer.writeBits(data.mccDigit1, 4);
    buffer.writeBits(data.mncDigit3, 4);
    buffer.writeBits(data.mccDigit3, 4);
    buffer.writeBits(data.mncDigit2, 4);
    buffer.writeBits(data.mncDigit1, 4);
    buffer.writeUint16(data.locationAreaCode);
    return true;
}

bool DataTypeCodecUtils::decodeLaiField(MsgBuffer &buffer,LaiField &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit2\n");
         return false;
    }
    data.mccDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit1\n");
         return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit3\n");
         return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mccDigit3\n");
         return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit2\n");
         return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: mncDigit1\n");
         return false;
    }

    buffer.readUint16(data.locationAreaCode);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: locationAreaCode\n");
         return false;
    }

  return true;
}

void DataTypeCodecUtils::displayLaiField_v(LaiField const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"LaiField:");
    stream.incrIndent();
    stream.endOfLine();
    stream.add((char *)"mccDigit2 = ");
    stream.add(data.mccDigit2);
    stream.endOfLine();
    stream.add((char *)"mccDigit1 = ");
    stream.add(data.mccDigit1);
    stream.endOfLine();
    stream.add((char *)"mncDigit3 = ");
    stream.add(data.mncDigit3);
    stream.endOfLine();
    stream.add((char *)"mccDigit3 = ");
    stream.add(data.mccDigit3);
    stream.endOfLine();
    stream.add((char *)"mncDigit2 = ");
    stream.add(data.mncDigit2);
    stream.endOfLine();
    stream.add((char *)"mncDigit1 = ");
    stream.add(data.mncDigit1);
    stream.endOfLine();
    stream.add((char *)"locationAreaCode = ");
    stream.add(data.locationAreaCode);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeIpAddressV4(MsgBuffer &buffer, IpAddressV4 const &data)
{
    buffer.writeUint32(data.ipValue);
    return true;
}

bool DataTypeCodecUtils::decodeIpAddressV4(MsgBuffer &buffer,IpAddressV4 &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint32(data.ipValue);
    if (buffer.getCurrentIndex() > typeBoundary)
    {
         errorStream.add((char *)"Attempt to read beyond type boundary: ipValue\n");
         return false;
    }

  return true;
}

void DataTypeCodecUtils::displayIpAddressV4_v(IpAddressV4 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"IpAddressV4:");
    stream.incrIndent();
    stream.endOfLine();
    stream.add((char *)"ipValue = ");
    stream.add(data.ipValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeIpAddressV6(MsgBuffer &buffer, IpAddressV6 const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.ipValue)))
    {
        errorStream.add((char *)"Failed to encode ipValue\n");
        return false;
    }

    return true;
}

bool DataTypeCodecUtils::decodeIpAddressV6(MsgBuffer &buffer,IpAddressV6 &data,
                         Uint16 length)
{
    
    Uint16 typeBoundary = buffer.getCurrentIndex() + length;
 Uint16   lengthLeft = typeBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.ipValue, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: ipValue\n");
        return false;
    }

  return true;
}

void DataTypeCodecUtils::displayIpAddressV6_v(IpAddressV6 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"IpAddressV6:");
    stream.incrIndent();
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}



bool DataTypeCodecUtils::encodeUint16Array16(MsgBuffer &buffer,
 Uint16Array16 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        buffer.writeUint16(data.values[i]);
    }
    return true;
}

bool DataTypeCodecUtils::decodeUint16Array16(MsgBuffer &buffer,
 Uint16Array16 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        buffer.readUint16(data.values[i]);
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:Uint16Array16\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayUint16Array16_v(Uint16Array16 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"Uint16Array16: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        stream.add(data.values[i]);
        stream.endOfLine();     
    }
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeUint8Array16(MsgBuffer &buffer,
 Uint8Array16 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        buffer.writeUint8(data.values[i]);
    }
    return true;
}

bool DataTypeCodecUtils::decodeUint8Array16(MsgBuffer &buffer,
 Uint8Array16 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        buffer.readUint8(data.values[i]);
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:Uint8Array16\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayUint8Array16_v(Uint8Array16 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"Uint8Array16: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        stream.add(data.values[i]);
        stream.endOfLine();     
    }
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeUint8Array32(MsgBuffer &buffer,
 Uint8Array32 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        buffer.writeUint8(data.values[i]);
    }
    return true;
}

bool DataTypeCodecUtils::decodeUint8Array32(MsgBuffer &buffer,
 Uint8Array32 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        buffer.readUint8(data.values[i]);
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:Uint8Array32\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayUint8Array32_v(Uint8Array32 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"Uint8Array32: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        stream.add(data.values[i]);
        stream.endOfLine();     
    }
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeUint8Array5(MsgBuffer &buffer,
 Uint8Array5 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        buffer.writeUint8(data.values[i]);
    }
    return true;
}

bool DataTypeCodecUtils::decodeUint8Array5(MsgBuffer &buffer,
 Uint8Array5 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        buffer.readUint8(data.values[i]);
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:Uint8Array5\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayUint8Array5_v(Uint8Array5 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"Uint8Array5: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        stream.add(data.values[i]);
        stream.endOfLine();     
    }
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeUint8Array4(MsgBuffer &buffer,
 Uint8Array4 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        buffer.writeUint8(data.values[i]);
    }
    return true;
}

bool DataTypeCodecUtils::decodeUint8Array4(MsgBuffer &buffer,
 Uint8Array4 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        buffer.readUint8(data.values[i]);
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:Uint8Array4\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayUint8Array4_v(Uint8Array4 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"Uint8Array4: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        stream.add(data.values[i]);
        stream.endOfLine();     
    }
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeUint8Array512(MsgBuffer &buffer,
 Uint8Array512 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        buffer.writeUint8(data.values[i]);
    }
    return true;
}

bool DataTypeCodecUtils::decodeUint8Array512(MsgBuffer &buffer,
 Uint8Array512 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        buffer.readUint8(data.values[i]);
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:Uint8Array512\n");
            return false;
        }
        data.count++;
        i++;
    }
    return true;
}

void DataTypeCodecUtils::displayUint8Array512_v(Uint8Array512 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"Uint8Array512: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        stream.add(data.values[i]);
        stream.endOfLine();     
    }
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeUint8Array255(MsgBuffer &buffer,
 Uint8Array255 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        buffer.writeUint8(data.values[i]);
    }
    return true;
}

bool DataTypeCodecUtils::decodeUint8Array255(MsgBuffer &buffer,
 Uint8Array255 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        buffer.readUint8(data.values[i]);
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:Uint8Array255\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayUint8Array255_v(Uint8Array255 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"Uint8Array255: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        stream.add(data.values[i]);
        stream.endOfLine();     
    }
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeCgiFieldArray64(MsgBuffer &buffer,
 CgiFieldArray64 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        if (!(DataTypeCodecUtils::encodeCgiField(buffer, data.values[i])))
        {
            errorStream.add((char *)"Failed to encode CgiFieldArray64\n");
            return false;
        }
    }
    return true;
}

bool DataTypeCodecUtils::decodeCgiFieldArray64(MsgBuffer &buffer,
 CgiFieldArray64 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        Uint16 lengthLeft = typeBoundary - buffer.getCurrentIndex();
                 if (!(DataTypeCodecUtils::decodeCgiField(buffer, data.values[i], lengthLeft)))
                 
        {
            errorStream.add((char *)"Failed to encode CgiFieldArray64\n");
            return false;
        }
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:CgiFieldArray64\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayCgiFieldArray64_v(CgiFieldArray64 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"CgiFieldArray64: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeSaiFieldArray64(MsgBuffer &buffer,
 SaiFieldArray64 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        if (!(DataTypeCodecUtils::encodeSaiField(buffer, data.values[i])))
        {
            errorStream.add((char *)"Failed to encode SaiFieldArray64\n");
            return false;
        }
    }
    return true;
}

bool DataTypeCodecUtils::decodeSaiFieldArray64(MsgBuffer &buffer,
 SaiFieldArray64 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        Uint16 lengthLeft = typeBoundary - buffer.getCurrentIndex();
                 if (!(DataTypeCodecUtils::decodeSaiField(buffer, data.values[i], lengthLeft)))
                 
        {
            errorStream.add((char *)"Failed to encode SaiFieldArray64\n");
            return false;
        }
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:SaiFieldArray64\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displaySaiFieldArray64_v(SaiFieldArray64 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"SaiFieldArray64: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeEcgiFieldArray64(MsgBuffer &buffer,
 EcgiFieldArray64 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        if (!(DataTypeCodecUtils::encodeEcgiField(buffer, data.values[i])))
        {
            errorStream.add((char *)"Failed to encode EcgiFieldArray64\n");
            return false;
        }
    }
    return true;
}

bool DataTypeCodecUtils::decodeEcgiFieldArray64(MsgBuffer &buffer,
 EcgiFieldArray64 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        Uint16 lengthLeft = typeBoundary - buffer.getCurrentIndex();
                 if (!(DataTypeCodecUtils::decodeEcgiField(buffer, data.values[i], lengthLeft)))
                 
        {
            errorStream.add((char *)"Failed to encode EcgiFieldArray64\n");
            return false;
        }
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:EcgiFieldArray64\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayEcgiFieldArray64_v(EcgiFieldArray64 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"EcgiFieldArray64: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeTaiFieldArray15(MsgBuffer &buffer,
 TaiFieldArray15 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        if (!(DataTypeCodecUtils::encodeTaiField(buffer, data.values[i])))
        {
            errorStream.add((char *)"Failed to encode TaiFieldArray15\n");
            return false;
        }
    }
    return true;
}

bool DataTypeCodecUtils::decodeTaiFieldArray15(MsgBuffer &buffer,
 TaiFieldArray15 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        Uint16 lengthLeft = typeBoundary - buffer.getCurrentIndex();
                 if (!(DataTypeCodecUtils::decodeTaiField(buffer, data.values[i], lengthLeft)))
                 
        {
            errorStream.add((char *)"Failed to encode TaiFieldArray15\n");
            return false;
        }
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:TaiFieldArray15\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayTaiFieldArray15_v(TaiFieldArray15 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"TaiFieldArray15: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}

bool DataTypeCodecUtils::encodeRaiFieldArray15(MsgBuffer &buffer,
 RaiFieldArray15 const &data)
{
    Uint16 i;
    for (i = 0; i < data.count; i++)
    {
        if (!(DataTypeCodecUtils::encodeRaiField(buffer, data.values[i])))
        {
            errorStream.add((char *)"Failed to encode RaiFieldArray15\n");
            return false;
        }
    }
    return true;
}

bool DataTypeCodecUtils::decodeRaiFieldArray15(MsgBuffer &buffer,
 RaiFieldArray15 &data, Uint16 length, Uint16 count)
{
    Uint16 i = 0;
    data.count = 0;
    bool readTillEnd = (count == 0);
    Uint16 startIndex = buffer.getCurrentIndex();
    Uint16 typeBoundary = startIndex+length;
    
    while ((i < count)||(readTillEnd && (buffer.getCurrentIndex() < typeBoundary)))
    {
        Uint16 lengthLeft = typeBoundary - buffer.getCurrentIndex();
                 if (!(DataTypeCodecUtils::decodeRaiField(buffer, data.values[i], lengthLeft)))
                 
        {
            errorStream.add((char *)"Failed to encode RaiFieldArray15\n");
            return false;
        }
        if (buffer.getCurrentIndex() > typeBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond type boundary:RaiFieldArray15\n");
            return false;
        }
        data.count++;
        i++;
    }
	return true;
}

void DataTypeCodecUtils::displayRaiFieldArray15_v(RaiFieldArray15 const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"RaiFieldArray15: Count: ");
    stream.add(data.count);
    stream.incrIndent();
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
