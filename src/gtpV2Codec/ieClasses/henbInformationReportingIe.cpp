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


#include "henbInformationReportingIe.h"
#include "dataTypeCodecUtils.h"

HenbInformationReportingIe::HenbInformationReportingIe() 
{
    ieType = 165;
    // TODO

}

HenbInformationReportingIe::~HenbInformationReportingIe() {
    // TODO Auto-generated destructor stub
}

bool HenbInformationReportingIe::encodeHenbInformationReportingIe(MsgBuffer &buffer, HenbInformationReportingIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.fti, 4)))
    {
        errorStream.add((char *)"Encoding of fti failed\n");
        return false;
    }

    return true;
}

bool HenbInformationReportingIe::decodeHenbInformationReportingIe(MsgBuffer &buffer, HenbInformationReportingIeData &data, Uint16 length)
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

    data.fti = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: fti\n");
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
        errorStream.add((char *)"Unable to decode IE HenbInformationReportingIe\n");
        return false;
    }
}
void HenbInformationReportingIe::displayHenbInformationReportingIe_v(HenbInformationReportingIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"HenbInformationReportingIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"fti: "); 
    stream.add((Uint8)data.fti);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
