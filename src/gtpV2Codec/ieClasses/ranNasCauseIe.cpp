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


#include "ranNasCauseIe.h"
#include "dataTypeCodecUtils.h"

RanNasCauseIe::RanNasCauseIe() 
{
    ieType = 172;
    // TODO

}

RanNasCauseIe::~RanNasCauseIe() {
    // TODO Auto-generated destructor stub
}

bool RanNasCauseIe::encodeRanNasCauseIe(MsgBuffer &buffer, RanNasCauseIeData const &data)
{
    if (!(data.protocolType>= 1 && data.protocolType<=5))
    {
        errorStream.add((char *)"Data validation failure: protocolType\n");
        return false; 
    }
    if(!(buffer.writeBits(data.protocolType, 4)))
    {
        errorStream.add((char *)"Encoding of protocolType failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.causeType, 4)))
    {
        errorStream.add((char *)"Encoding of causeType failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.causeValue)))
    {
        errorStream.add((char *)"Encoding of causeValue failed\n");
        return false;
    }

    return true;
}

bool RanNasCauseIe::decodeRanNasCauseIe(MsgBuffer &buffer, RanNasCauseIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.protocolType = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: protocolType\n");
        return false;
    }
    if (!(data.protocolType>= 1 && data.protocolType<=5))
    {
        errorStream.add((char *)"Data validation failure : protocolType\n");
        return false; //TODO need to add validations
    }
    data.causeType = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: causeType\n");
        return false;
    }

    buffer.readUint8(data.causeValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: causeValue\n");
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
        errorStream.add((char *)"Unable to decode IE RanNasCauseIe\n");
        return false;
    }
}
void RanNasCauseIe::displayRanNasCauseIe_v(RanNasCauseIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"RanNasCauseIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"protocolType: "); 
    stream.add((Uint8)data.protocolType);
    stream.endOfLine();
  
    stream.add( (char *)"causeType: "); 
    stream.add((Uint8)data.causeType);
    stream.endOfLine();
  
    stream.add((char *)"causeValue: ");
    stream.add(data.causeValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
