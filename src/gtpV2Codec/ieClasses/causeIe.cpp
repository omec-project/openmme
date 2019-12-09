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


#include "causeIe.h"
#include "dataTypeCodecUtils.h"

CauseIe::CauseIe() 
{
    ieType = 2;
    // TODO

}

CauseIe::~CauseIe() {
    // TODO Auto-generated destructor stub
}

bool CauseIe::encodeCauseIe(MsgBuffer &buffer, CauseIeData const &data)
{
    if (!(buffer.writeUint8(data.causeValue)))
    {
        errorStream.add((char *)"Encoding of causeValue failed\n");
        return false;
    }
    buffer.skipBits(5);

    if(!(buffer.writeBits(data.pce, 1)))
    {
        errorStream.add((char *)"Encoding of pce failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.pbe, 1)))
    {
        errorStream.add((char *)"Encoding of pbe failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.cs, 1)))
    {
        errorStream.add((char *)"Encoding of cs failed\n");
        return false;
    }
    if (data.offendingIeDataPresent)
    {
        if (!(DataTypeCodecUtils::encodeOffendingIeData(buffer, data.offendingIeData)))
        {
            errorStream.add((char *)"Encoding of offendingIeData failed\n");
            return false;
        }
    }

    return true;
}

bool CauseIe::decodeCauseIe(MsgBuffer &buffer, CauseIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.causeValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: causeValue\n");
        return false;
    }
    buffer.skipBits(5);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.pce = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: pce\n");
        return false;
    }
    data.pbe = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: pbe\n");
        return false;
    }
    data.cs = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: cs\n");
        return false;
    }

    if (length == 6)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeOffendingIeData(buffer, data.offendingIeData, lengthLeft)))
        {
            errorStream.add((char *)"Failed to decode: offendingIeData\n");
            return false;
        }
        data.offendingIeDataPresent = true;
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
        errorStream.add((char *)"Unable to decode IE CauseIe\n");
        return false;
    }
}
void CauseIe::displayCauseIe_v(CauseIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"CauseIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"causeValue: ");
    stream.add(data.causeValue);
    stream.endOfLine();
  
    stream.add( (char *)"pce: "); 
    stream.add((Uint8)data.pce);
    stream.endOfLine();
  
    stream.add( (char *)"pbe: "); 
    stream.add((Uint8)data.pbe);
    stream.endOfLine();
  
    stream.add( (char *)"cs: "); 
    stream.add((Uint8)data.cs);
    stream.endOfLine();
  
    if (data.offendingIeDataPresent)
    {
        stream.add((char *)"offendingIeData:");
        stream.endOfLine();
        DataTypeCodecUtils::displayOffendingIeData_v(data.offendingIeData, stream);
    }   
    stream.decrIndent();
    stream.decrIndent();
}
