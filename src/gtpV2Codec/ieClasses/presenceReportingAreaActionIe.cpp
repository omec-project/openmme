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
        errorStream.add((char *)"Encoding of inapra failed\n");
        return false;
    }
    if (!(data.action<=3))
    {
        errorStream.add((char *)"Data validation failure: action\n");
        return false; 
    }
    if(!(buffer.writeBits(data.action, 3)))
    {
        errorStream.add((char *)"Encoding of action failed\n");
        return false;
    }
    if (!(buffer.writeUint32(data.presenceReportingAreaIdentifier)))
    {
        errorStream.add((char *)"Encoding of presenceReportingAreaIdentifier failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfTAI, 4)))
    {
        errorStream.add((char *)"Encoding of numberOfTAI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.numberOfRAI, 4)))
    {
        errorStream.add((char *)"Encoding of numberOfRAI failed\n");
        return false;
    }
    buffer.skipBits(2);

    if(!(buffer.writeBits(data.numberOfMacroeNodeB, 6)))
    {
        errorStream.add((char *)"Encoding of numberOfMacroeNodeB failed\n");
        return false;
    }
    buffer.skipBits(2);

    if(!(buffer.writeBits(data.numberOfHomeeNodeB, 6)))
    {
        errorStream.add((char *)"Encoding of numberOfHomeeNodeB failed\n");
        return false;
    }
    buffer.skipBits(2);

    if(!(buffer.writeBits(data.numberOfECGI, 6)))
    {
        errorStream.add((char *)"Encoding of numberOfECGI failed\n");
        return false;
    }
    buffer.skipBits(2);

    if(!(buffer.writeBits(data.numberOfSAI, 6)))
    {
        errorStream.add((char *)"Encoding of numberOfSAI failed\n");
        return false;
    }
    buffer.skipBits(2);

    if(!(buffer.writeBits(data.numberOfCGI, 6)))
    {
        errorStream.add((char *)"Encoding of numberOfCGI failed\n");
        return false;
    }
    if (data.numberOfTAI !=0)
    {
        if (!(DataTypeCodecUtils::encodeTaiFieldArray15(buffer, data.tais)))
        {
            errorStream.add((char *)"Encoding of tais failed\n");
            return false;
        }
    }
    if (data.numberOfMacroeNodeB !=0)
    {
        if (!(buffer.writeUint8(data.macroeNBIds)))
        {
    errorStream.add((char *)"Encoding of macroeNBIds failed\n");
    return false;
        }
    }
    if (data.numberOfHomeeNodeB !=0)
    {
        if (!(buffer.writeUint8(data.homeeNBIds)))
        {
    errorStream.add((char *)"Encoding of homeeNBIds failed\n");
    return false;
        }
    }
    if (data.numberOfECGI !=0)
    {
        if (!(DataTypeCodecUtils::encodeEcgiFieldArray64(buffer, data.ecgis)))
        {
            errorStream.add((char *)"Encoding of ecgis failed\n");
            return false;
        }
    }
    if (data.numberOfRAI !=0)
    {
        if (!(DataTypeCodecUtils::encodeRaiFieldArray15(buffer, data.raiss)))
        {
            errorStream.add((char *)"Encoding of raiss failed\n");
            return false;
        }
    }
    if (data.numberOfSAI !=0)
    {
        if (!(DataTypeCodecUtils::encodeSaiFieldArray64(buffer, data.saiss)))
        {
            errorStream.add((char *)"Encoding of saiss failed\n");
            return false;
        }
    }
    if (data.numberOfCGI !=0)
    {
        if (!(DataTypeCodecUtils::encodeCgiFieldArray64(buffer, data.cgiss)))
        {
            errorStream.add((char *)"Encoding of cgiss failed\n");
            return false;
        }
    }
    buffer.skipBits(2);

    if(!(buffer.writeBits(data.numberOfExtendedMacroeNodeB, 6)))
    {
        errorStream.add((char *)"Encoding of numberOfExtendedMacroeNodeB failed\n");
        return false;
    }
    if (data.numberOfExtendedMacroeNodeB !=0)
    {
        if (!(buffer.writeUint8(data.extendedMacroeNBIds)))
        {
    errorStream.add((char *)"Encoding of extendedMacroeNBIds failed\n");
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
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.inapra = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: inapra\n");
        return false;
    }
    data.action = buffer.readBits(3);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: action\n");
        return false;
    }
    if (!(data.action<=3))
    {
        errorStream.add((char *)"Data validation failure : action\n");
        return false; //TODO need to add validations
    }

    buffer.readUint32(data.presenceReportingAreaIdentifier);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: presenceReportingAreaIdentifier\n");
        return false;
    }
    data.numberOfTAI = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfTAI\n");
        return false;
    }
    data.numberOfRAI = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfRAI\n");
        return false;
    }
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.numberOfMacroeNodeB = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfMacroeNodeB\n");
        return false;
    }
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.numberOfHomeeNodeB = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfHomeeNodeB\n");
        return false;
    }
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.numberOfECGI = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfECGI\n");
        return false;
    }
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.numberOfSAI = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfSAI\n");
        return false;
    }
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.numberOfCGI = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfCGI\n");
        return false;
    }

    if (data.numberOfTAI !=0)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeTaiFieldArray15(buffer, data.tais, lengthLeft, 0)))
        {
            errorStream.add((char *)"Failed to decode: tais\n");
            return false;
        }
    }

    if (data.numberOfMacroeNodeB !=0)
    {

        buffer.readUint8(data.macroeNBIds);
        if (buffer.getCurrentIndex() > ieBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond IE boundary: macroeNBIds\n");
            return false;
        }
    }

    if (data.numberOfHomeeNodeB !=0)
    {

        buffer.readUint8(data.homeeNBIds);
        if (buffer.getCurrentIndex() > ieBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond IE boundary: homeeNBIds\n");
            return false;
        }
    }

    if (data.numberOfECGI !=0)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeEcgiFieldArray64(buffer, data.ecgis, lengthLeft, 0)))
        {
            errorStream.add((char *)"Failed to decode: ecgis\n");
            return false;
        }
    }

    if (data.numberOfRAI !=0)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeRaiFieldArray15(buffer, data.raiss, lengthLeft, 0)))
        {
            errorStream.add((char *)"Failed to decode: raiss\n");
            return false;
        }
    }

    if (data.numberOfSAI !=0)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeSaiFieldArray64(buffer, data.saiss, lengthLeft, 0)))
        {
            errorStream.add((char *)"Failed to decode: saiss\n");
            return false;
        }
    }

    if (data.numberOfCGI !=0)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeCgiFieldArray64(buffer, data.cgiss, lengthLeft, 0)))
        {
            errorStream.add((char *)"Failed to decode: cgiss\n");
            return false;
        }
    }
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.numberOfExtendedMacroeNodeB = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: numberOfExtendedMacroeNodeB\n");
        return false;
    }

    if (data.numberOfExtendedMacroeNodeB !=0)
    {

        buffer.readUint8(data.extendedMacroeNBIds);
        if (buffer.getCurrentIndex() > ieBoundary)
        {
            errorStream.add((char *)"Attempt to read beyond IE boundary: extendedMacroeNBIds\n");
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
        errorStream.add((char *)"Unable to decode IE PresenceReportingAreaActionIe\n");
        return false;
    }
}
void PresenceReportingAreaActionIe::displayPresenceReportingAreaActionIe_v(PresenceReportingAreaActionIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"PresenceReportingAreaActionIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"inapra: "); 
    stream.add((Uint8)data.inapra);
    stream.endOfLine();
  
    stream.add( (char *)"action: "); 
    stream.add((Uint8)data.action);
    stream.endOfLine();
  
    stream.add((char *)"presenceReportingAreaIdentifier: ");
    stream.add(data.presenceReportingAreaIdentifier);
    stream.endOfLine();
  
    stream.add( (char *)"numberOfTAI: "); 
    stream.add((Uint8)data.numberOfTAI);
    stream.endOfLine();
  
    stream.add( (char *)"numberOfRAI: "); 
    stream.add((Uint8)data.numberOfRAI);
    stream.endOfLine();
  
    stream.add( (char *)"numberOfMacroeNodeB: "); 
    stream.add((Uint8)data.numberOfMacroeNodeB);
    stream.endOfLine();
  
    stream.add( (char *)"numberOfHomeeNodeB: "); 
    stream.add((Uint8)data.numberOfHomeeNodeB);
    stream.endOfLine();
  
    stream.add( (char *)"numberOfECGI: "); 
    stream.add((Uint8)data.numberOfECGI);
    stream.endOfLine();
  
    stream.add( (char *)"numberOfSAI: "); 
    stream.add((Uint8)data.numberOfSAI);
    stream.endOfLine();
  
    stream.add( (char *)"numberOfCGI: "); 
    stream.add((Uint8)data.numberOfCGI);
    stream.endOfLine();
  
    if (data.numberOfTAI !=0)
    {
        stream.add((char *)"tais:");
        stream.endOfLine();
        DataTypeCodecUtils::displayTaiFieldArray15_v(data.tais, stream);
    }
  
    if (data.numberOfMacroeNodeB !=0)
    {
        stream.add((char *)"macroeNBIds: ");
        stream.add(data.macroeNBIds);
        stream.endOfLine();
    }
  
    if (data.numberOfHomeeNodeB !=0)
    {
        stream.add((char *)"homeeNBIds: ");
        stream.add(data.homeeNBIds);
        stream.endOfLine();
    }
  
    if (data.numberOfECGI !=0)
    {
        stream.add((char *)"ecgis:");
        stream.endOfLine();
        DataTypeCodecUtils::displayEcgiFieldArray64_v(data.ecgis, stream);
    }
  
    if (data.numberOfRAI !=0)
    {
        stream.add((char *)"raiss:");
        stream.endOfLine();
        DataTypeCodecUtils::displayRaiFieldArray15_v(data.raiss, stream);
    }
  
    if (data.numberOfSAI !=0)
    {
        stream.add((char *)"saiss:");
        stream.endOfLine();
        DataTypeCodecUtils::displaySaiFieldArray64_v(data.saiss, stream);
    }
  
    if (data.numberOfCGI !=0)
    {
        stream.add((char *)"cgiss:");
        stream.endOfLine();
        DataTypeCodecUtils::displayCgiFieldArray64_v(data.cgiss, stream);
    }
  
    stream.add( (char *)"numberOfExtendedMacroeNodeB: "); 
    stream.add((Uint8)data.numberOfExtendedMacroeNodeB);
    stream.endOfLine();
  
    if (data.numberOfExtendedMacroeNodeB !=0)
    {
        stream.add((char *)"extendedMacroeNBIds: ");
        stream.add(data.extendedMacroeNBIds);
        stream.endOfLine();
    }
    stream.decrIndent();
    stream.decrIndent();
}
