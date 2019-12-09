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


#include "integerNumberIe.h"
#include "dataTypeCodecUtils.h"

IntegerNumberIe::IntegerNumberIe() 
{
    ieType = 187;
    // TODO

}

IntegerNumberIe::~IntegerNumberIe() {
    // TODO Auto-generated destructor stub
}

bool IntegerNumberIe::encodeIntegerNumberIe(MsgBuffer &buffer, IntegerNumberIeData const &data)
{
    if (!(buffer.writeUint64(data.integerNumberValue)))
    {
        errorStream.add((char *)"Encoding of integerNumberValue failed\n");
        return false;
    }

    return true;
}

bool IntegerNumberIe::decodeIntegerNumberIe(MsgBuffer &buffer, IntegerNumberIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint64(data.integerNumberValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: integerNumberValue\n");
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
        errorStream.add((char *)"Unable to decode IE IntegerNumberIe\n");
        return false;
    }
}
void IntegerNumberIe::displayIntegerNumberIe_v(IntegerNumberIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"IntegerNumberIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"integerNumberValue: ");
    stream.add(data.integerNumberValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
