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


#include "bearerFlagsIe.h"
#include "dataTypeCodecUtils.h"

BearerFlagsIe::BearerFlagsIe() 
{
    ieType = 97;
    // TODO

}

BearerFlagsIe::~BearerFlagsIe() {
    // TODO Auto-generated destructor stub
}

bool BearerFlagsIe::encodeBearerFlagsIe(MsgBuffer &buffer, BearerFlagsIeData const &data)
{
    buffer.skipBits(6);

    if(!(buffer.writeBits(data.vb, 1)))
    {
        errorStream.add((char *)"Encoding of vb failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.ppc, 1)))
    {
        errorStream.add((char *)"Encoding of ppc failed\n");
        return false;
    }

    return true;
}

bool BearerFlagsIe::decodeBearerFlagsIe(MsgBuffer &buffer, BearerFlagsIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(6);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.vb = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: vb\n");
        return false;
    }
    data.ppc = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: ppc\n");
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
        errorStream.add((char *)"Unable to decode IE BearerFlagsIe\n");
        return false;
    }
}
void BearerFlagsIe::displayBearerFlagsIe_v(BearerFlagsIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"BearerFlagsIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"vb: "); 
    stream.add((Uint8)data.vb);
    stream.endOfLine();
  
    stream.add( (char *)"ppc: "); 
    stream.add((Uint8)data.ppc);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
