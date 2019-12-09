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


#include "twmiIe.h"
#include "dataTypeCodecUtils.h"

TwmiIe::TwmiIe() 
{
    ieType = 174;
    // TODO

}

TwmiIe::~TwmiIe() {
    // TODO Auto-generated destructor stub
}

bool TwmiIe::encodeTwmiIe(MsgBuffer &buffer, TwmiIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.mcm, 2)))
    {
        errorStream.add((char *)"Encoding of mcm failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.scm, 2)))
    {
        errorStream.add((char *)"Encoding of scm failed\n");
        return false;
    }

    return true;
}

bool TwmiIe::decodeTwmiIe(MsgBuffer &buffer, TwmiIeData &data, Uint16 length)
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

    data.mcm = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: mcm\n");
        return false;
    }
    data.scm = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: scm\n");
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
        errorStream.add((char *)"Unable to decode IE TwmiIe\n");
        return false;
    }
}
void TwmiIe::displayTwmiIe_v(TwmiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"TwmiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"mcm: "); 
    stream.add((Uint8)data.mcm);
    stream.endOfLine();
  
    stream.add( (char *)"scm: "); 
    stream.add((Uint8)data.scm);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
