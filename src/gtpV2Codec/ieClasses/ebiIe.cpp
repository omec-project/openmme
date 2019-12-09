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


#include "ebiIe.h"
#include "dataTypeCodecUtils.h"

EbiIe::EbiIe() 
{
    ieType = 73;
    // TODO

}

EbiIe::~EbiIe() {
    // TODO Auto-generated destructor stub
}

bool EbiIe::encodeEbiIe(MsgBuffer &buffer, EbiIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.epsBearerId, 4)))
    {
        errorStream.add((char *)"Encoding of epsBearerId failed\n");
        return false;
    }

    return true;
}

bool EbiIe::decodeEbiIe(MsgBuffer &buffer, EbiIeData &data, Uint16 length)
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

    data.epsBearerId = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: epsBearerId\n");
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
        errorStream.add((char *)"Unable to decode IE EbiIe\n");
        return false;
    }
}
void EbiIe::displayEbiIe_v(EbiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"EbiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"epsBearerId: "); 
    stream.add((Uint8)data.epsBearerId);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
