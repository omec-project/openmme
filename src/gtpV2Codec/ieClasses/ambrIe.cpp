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


#include "ambrIe.h"
#include "dataTypeCodecUtils.h"

AmbrIe::AmbrIe() 
{
    ieType = 72;
    // TODO

}

AmbrIe::~AmbrIe() {
    // TODO Auto-generated destructor stub
}

bool AmbrIe::encodeAmbrIe(MsgBuffer &buffer, AmbrIeData const &data)
{
    if (!(buffer.writeUint32(data.maxMbrUplink)))
    {
        errorStream.add((char *)"Encoding of maxMbrUplink failed\n");
        return false;
    }
    if (!(buffer.writeUint32(data.maxMbrDownlink)))
    {
        errorStream.add((char *)"Encoding of maxMbrDownlink failed\n");
        return false;
    }

    return true;
}

bool AmbrIe::decodeAmbrIe(MsgBuffer &buffer, AmbrIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint32(data.maxMbrUplink);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: maxMbrUplink\n");
        return false;
    }

    buffer.readUint32(data.maxMbrDownlink);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: maxMbrDownlink\n");
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
        errorStream.add((char *)"Unable to decode IE AmbrIe\n");
        return false;
    }
}
void AmbrIe::displayAmbrIe_v(AmbrIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"AmbrIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"maxMbrUplink: ");
    stream.add(data.maxMbrUplink);
    stream.endOfLine();
  
    stream.add((char *)"maxMbrDownlink: ");
    stream.add(data.maxMbrDownlink);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
