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


#include "signallingPriorityIndicationIe.h"
#include "dataTypeCodecUtils.h"

SignallingPriorityIndicationIe::SignallingPriorityIndicationIe() 
{
    ieType = 157;
    // TODO

}

SignallingPriorityIndicationIe::~SignallingPriorityIndicationIe() {
    // TODO Auto-generated destructor stub
}

bool SignallingPriorityIndicationIe::encodeSignallingPriorityIndicationIe(MsgBuffer &buffer, SignallingPriorityIndicationIeData const &data)
{
    buffer.skipBytes(2);


    return true;
}

bool SignallingPriorityIndicationIe::decodeSignallingPriorityIndicationIe(MsgBuffer &buffer, SignallingPriorityIndicationIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBytes(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
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
        errorStream.add((char *)"Unable to decode IE SignallingPriorityIndicationIe\n");
        return false;
    }
}
void SignallingPriorityIndicationIe::displaySignallingPriorityIndicationIe_v(SignallingPriorityIndicationIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"SignallingPriorityIndicationIeData:");
    stream.incrIndent();
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
