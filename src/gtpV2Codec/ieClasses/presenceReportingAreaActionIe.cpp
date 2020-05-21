/*
 * presenceReportingAreaActionIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "presenceReportingAreaActionIe.h"
#include "dataTypeCodecUtils.h"

PresenceReportingAreaActionIe::PresenceReportingAreaActionIe() 
{
    ieType = 177;
    // TODO

}

PresenceReportingAreaActionIe::~PresenceReportingAreaActionIe() {
    // TODO Auto-generated destructor stub
}

bool PresenceReportingAreaActionIe::encodePresenceReportingAreaActionIe(MsgBuffer &buffer, PresenceReportingAreaActionIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.inapra, 1)))
    {
        errorStream.add("Encoding of inapra failed\n");
        return false;
    }
    buffer.skipBits(2);

    if (!(data.action<=3))
    {
        errorStream.add("Data validation failure: action\n");
        return false; 
    }
    if(!(buffer.writeBits(data.action, 3)))
    {
        errorStream.add("Encoding of action failed\n");
        return false;
    }
    if (!(buffer.writeUint32(data.presenceReportingAreaIdentifier)))
    {
        errorStream.add("Encoding of presenceReportingAreaIdentifier failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfTAI, 4)))
    {
        errorStream.add("Encoding of numberOfTAI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfRAI, 4)))
    {
        errorStream.add("Encoding of numberOfRAI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfMacroeNodeB, 6)))
    {
        errorStream.add("Encoding of numberOfMacroeNodeB failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfHomeeNodeB, 6)))
    {
        errorStream.add("Encoding of numberOfHomeeNodeB failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfECGI, 6)))
    {
        errorStream.add("Encoding of numberOfECGI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfSAI, 6)))
    {
        errorStream.add("Encoding of numberOfSAI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfCGI, 6)))
    {
        errorStream.add("Encoding of numberOfCGI failed\n");
        return false;
    }
    if (data.numberOfTAI !=0)
    {
        if (!(DataTypeCodecUtils::encodeTaiFieldArray15(buffer, data.tais)))
        {
            errorStream.add("Encoding of tais failed\n");
            return false;
        }
    }
    if (data.numberOfMacroeNodeB !=0)
    {
        if (!(buffer.writeUint8(data.macroeNBIds)))
        {
    errorStream.add("Encoding of macroeNBIds failed\n");
    return false;
        }
    }
    if (data.numberOfHomeeNodeB !=0)
    {
        if (!(buffer.writeUint8(data.homeeNBIds)))
        {
    errorStream.add("Encoding of homeeNBIds failed\n");
    return false;
        }
    }
    if (data.numberOfECGI !=0)
    {
        if (!(DataTypeCodecUtils::encodeEcgiFieldArray64(buffer, data.ecgis)))
        {
            errorStream.add("Encoding of ecgis failed\n");
            return false;
        }
    }
    if (data.numberOfRAI !=0)
    {
        if (!(DataTypeCodecUtils::encodeRaiFieldArray15(buffer, data.raiss)))
        {
            errorStream.add("Encoding of raiss failed\n");
            return false;
        }
    }
    if (data.numberOfSAI !=0)
    {
        if (!(DataTypeCodecUtils::encodeSaiFieldArray64(buffer, data.saiss)))
        {
            errorStream.add("Encoding of saiss failed\n");
            return false;
        }
    }
    if (data.numberOfCGI !=0)
    {
        if (!(DataTypeCodecUtils::encodeCgiFieldArray64(buffer, data.cgiss)))
        {
            errorStream.add("Encoding of cgiss failed\n");
            return false;
        }
    }
    if(!(buffer.writeBits(data.numberOfExtendedMacroeNodeB, 6)))
    {
        errorStream.add("Encoding of numberOfExtendedMacroeNodeB failed\n");
        return false;
    }
    if (data.numberOfExtendedMacroeNodeB !=0)
    {
        if (!(buffer.writeUint8(data.extendedMacroeNBIds)))
        {
    errorStream.add("Encoding of extendedMacroeNBIds failed\n");
    return false;
        }
    }

    return true;
}

bool PresenceReportingAreaActionIe::decodePresenceReportingAreaActionIe(MsgBuffer &buffer, PresenceReportingAreaActionIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(4);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.inapra = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: inapra\n");
        return false;
    }
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.action = buffer.readBits(3);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: action\n");
        return false;
    }
    if (!(data.action<=3))
    {
        errorStream.add("Data validation failure : action\n");
        return false; //TODO need to add validations
    }

    buffer.readUint32(data.presenceReportingAreaIdentifier);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: presenceReportingAreaIdentifier\n");
        return false;
    }
    data.numberOfTAI = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: numberOfTAI\n");
        return false;
    }
    data.numberOfRAI = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: numberOfRAI\n");
        return false;
    }
    data.numberOfMacroeNodeB = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: numberOfMacroeNodeB\n");
        return false;
    }
    data.numberOfHomeeNodeB = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: numberOfHomeeNodeB\n");
        return false;
    }
    data.numberOfECGI = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: numberOfECGI\n");
        return false;
    }
    data.numberOfSAI = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: numberOfSAI\n");
        return false;
    }
    data.numberOfCGI = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: numberOfCGI\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeTaiFieldArray15(buffer, data.tais, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: tais\n");
        return false;
    }

    buffer.readUint8(data.macroeNBIds);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: macroeNBIds\n");
        return false;
    }

    buffer.readUint8(data.homeeNBIds);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: homeeNBIds\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeEcgiFieldArray64(buffer, data.ecgis, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: ecgis\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeRaiFieldArray15(buffer, data.raiss, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: raiss\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeSaiFieldArray64(buffer, data.saiss, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: saiss\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeCgiFieldArray64(buffer, data.cgiss, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: cgiss\n");
        return false;
    }
    data.numberOfExtendedMacroeNodeB = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: numberOfExtendedMacroeNodeB\n");
        return false;
    }

    buffer.readUint8(data.extendedMacroeNBIds);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: extendedMacroeNBIds\n");
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
        errorStream.add("Unable to decode IE PresenceReportingAreaActionIe\n");
        return false;
    }
}
void PresenceReportingAreaActionIe::displayPresenceReportingAreaActionIe_v(PresenceReportingAreaActionIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("PresenceReportingAreaActionIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "inapra: "); 
    stream.add((Uint8)data.inapra);
    stream.endOfLine();
  
    stream.add( "action: "); 
    stream.add((Uint8)data.action);
    stream.endOfLine();
  
    stream.add("presenceReportingAreaIdentifier: ");
    stream.add(data.presenceReportingAreaIdentifier);
    stream.endOfLine();
  
    stream.add( "numberOfTAI: "); 
    stream.add((Uint8)data.numberOfTAI);
    stream.endOfLine();
  
    stream.add( "numberOfRAI: "); 
    stream.add((Uint8)data.numberOfRAI);
    stream.endOfLine();
  
    stream.add( "numberOfMacroeNodeB: "); 
    stream.add((Uint8)data.numberOfMacroeNodeB);
    stream.endOfLine();
  
    stream.add( "numberOfHomeeNodeB: "); 
    stream.add((Uint8)data.numberOfHomeeNodeB);
    stream.endOfLine();
  
    stream.add( "numberOfECGI: "); 
    stream.add((Uint8)data.numberOfECGI);
    stream.endOfLine();
  
    stream.add( "numberOfSAI: "); 
    stream.add((Uint8)data.numberOfSAI);
    stream.endOfLine();
  
    stream.add( "numberOfCGI: "); 
    stream.add((Uint8)data.numberOfCGI);
    stream.endOfLine();
  
    if (data.numberOfTAI !=0)
    {
        stream.add("tais:");
        stream.endOfLine();
        DataTypeCodecUtils::displayTaiFieldArray15_v(data.tais, stream);
    }
  
    if (data.numberOfMacroeNodeB !=0)
    {
        stream.add("macroeNBIds: ");
        stream.add(data.macroeNBIds);
        stream.endOfLine();
    }
  
    if (data.numberOfHomeeNodeB !=0)
    {
        stream.add("homeeNBIds: ");
        stream.add(data.homeeNBIds);
        stream.endOfLine();
    }
  
    if (data.numberOfECGI !=0)
    {
        stream.add("ecgis:");
        stream.endOfLine();
        DataTypeCodecUtils::displayEcgiFieldArray64_v(data.ecgis, stream);
    }
  
    if (data.numberOfRAI !=0)
    {
        stream.add("raiss:");
        stream.endOfLine();
        DataTypeCodecUtils::displayRaiFieldArray15_v(data.raiss, stream);
    }
  
    if (data.numberOfSAI !=0)
    {
        stream.add("saiss:");
        stream.endOfLine();
        DataTypeCodecUtils::displaySaiFieldArray64_v(data.saiss, stream);
    }
  
    if (data.numberOfCGI !=0)
    {
        stream.add("cgiss:");
        stream.endOfLine();
        DataTypeCodecUtils::displayCgiFieldArray64_v(data.cgiss, stream);
    }
  
    stream.add( "numberOfExtendedMacroeNodeB: "); 
    stream.add((Uint8)data.numberOfExtendedMacroeNodeB);
    stream.endOfLine();
  
    if (data.numberOfExtendedMacroeNodeB !=0)
    {
        stream.add("extendedMacroeNBIds: ");
        stream.add(data.extendedMacroeNBIds);
        stream.endOfLine();
    }
    stream.decrIndent();
    stream.decrIndent();
}
