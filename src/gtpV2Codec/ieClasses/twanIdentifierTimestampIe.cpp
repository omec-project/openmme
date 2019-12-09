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


#include "twanIdentifierTimestampIe.h"
#include "dataTypeCodecUtils.h"

TwanIdentifierTimestampIe::TwanIdentifierTimestampIe() 
{
    ieType = 179;
    // TODO

}

TwanIdentifierTimestampIe::~TwanIdentifierTimestampIe() {
    // TODO Auto-generated destructor stub
}

bool TwanIdentifierTimestampIe::encodeTwanIdentifierTimestampIe(MsgBuffer &buffer, TwanIdentifierTimestampIeData const &data)
{
    if (!(buffer.writeUint32(data.twanIdentifierTimestampvalue)))
    {
        errorStream.add((char *)"Encoding of twanIdentifierTimestampvalue failed\n");
        return false;
    }

    return true;
}

bool TwanIdentifierTimestampIe::decodeTwanIdentifierTimestampIe(MsgBuffer &buffer, TwanIdentifierTimestampIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint32(data.twanIdentifierTimestampvalue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: twanIdentifierTimestampvalue\n");
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
        errorStream.add((char *)"Unable to decode IE TwanIdentifierTimestampIe\n");
        return false;
    }
}
void TwanIdentifierTimestampIe::displayTwanIdentifierTimestampIe_v(TwanIdentifierTimestampIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"TwanIdentifierTimestampIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"twanIdentifierTimestampvalue: ");
    stream.add(data.twanIdentifierTimestampvalue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
