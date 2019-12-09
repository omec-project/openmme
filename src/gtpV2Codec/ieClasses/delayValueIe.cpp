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


#include "delayValueIe.h"
#include "dataTypeCodecUtils.h"

DelayValueIe::DelayValueIe() 
{
    ieType = 92;
    // TODO

}

DelayValueIe::~DelayValueIe() {
    // TODO Auto-generated destructor stub
}

bool DelayValueIe::encodeDelayValueIe(MsgBuffer &buffer, DelayValueIeData const &data)
{
    if (!(data.delayValue% 50 == 0 || data.delayValue== 0))
    {
        errorStream.add((char *)"Data validation failure: delayValue\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.delayValue)))
    {
        errorStream.add((char *)"Encoding of delayValue failed\n");
        return false;
    }

    return true;
}

bool DelayValueIe::decodeDelayValueIe(MsgBuffer &buffer, DelayValueIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.delayValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: delayValue\n");
        return false;
    }
    if (!(data.delayValue% 50 == 0 || data.delayValue== 0))
    {
        errorStream.add((char *)"Data validation failure : delayValue\n");
        return false; //TODO need to add validations
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
        errorStream.add((char *)"Unable to decode IE DelayValueIe\n");
        return false;
    }
}
void DelayValueIe::displayDelayValueIe_v(DelayValueIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"DelayValueIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"delayValue: ");
    stream.add(data.delayValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
