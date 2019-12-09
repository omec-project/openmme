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


#include "servingPlmnRateControlIe.h"
#include "dataTypeCodecUtils.h"

ServingPlmnRateControlIe::ServingPlmnRateControlIe() 
{
    ieType = 198;
    // TODO

}

ServingPlmnRateControlIe::~ServingPlmnRateControlIe() {
    // TODO Auto-generated destructor stub
}

bool ServingPlmnRateControlIe::encodeServingPlmnRateControlIe(MsgBuffer &buffer, ServingPlmnRateControlIeData const &data)
{
    if (!(buffer.writeUint16(data.uplinkRateLimit)))
    {
        errorStream.add((char *)"Encoding of uplinkRateLimit failed\n");
        return false;
    }
    if (!(buffer.writeUint16(data.downlinkRateLimit)))
    {
        errorStream.add((char *)"Encoding of downlinkRateLimit failed\n");
        return false;
    }

    return true;
}

bool ServingPlmnRateControlIe::decodeServingPlmnRateControlIe(MsgBuffer &buffer, ServingPlmnRateControlIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint16(data.uplinkRateLimit);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: uplinkRateLimit\n");
        return false;
    }

    buffer.readUint16(data.downlinkRateLimit);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: downlinkRateLimit\n");
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
        errorStream.add((char *)"Unable to decode IE ServingPlmnRateControlIe\n");
        return false;
    }
}
void ServingPlmnRateControlIe::displayServingPlmnRateControlIe_v(ServingPlmnRateControlIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ServingPlmnRateControlIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"uplinkRateLimit: ");
    stream.add(data.uplinkRateLimit);
    stream.endOfLine();
  
    stream.add((char *)"downlinkRateLimit: ");
    stream.add(data.downlinkRateLimit);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
