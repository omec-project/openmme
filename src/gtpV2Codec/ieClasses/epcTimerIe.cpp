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


#include "epcTimerIe.h"
#include "dataTypeCodecUtils.h"

EpcTimerIe::EpcTimerIe() 
{
    ieType = 156;
    // TODO

}

EpcTimerIe::~EpcTimerIe() {
    // TODO Auto-generated destructor stub
}

bool EpcTimerIe::encodeEpcTimerIe(MsgBuffer &buffer, EpcTimerIeData const &data)
{
    if(!(buffer.writeBits(data.timerUnit, 3)))
    {
        errorStream.add((char *)"Encoding of timerUnit failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.timerValue, 5)))
    {
        errorStream.add((char *)"Encoding of timerValue failed\n");
        return false;
    }

    return true;
}

bool EpcTimerIe::decodeEpcTimerIe(MsgBuffer &buffer, EpcTimerIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.timerUnit = buffer.readBits(3);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: timerUnit\n");
        return false;
    }
    data.timerValue = buffer.readBits(5);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: timerValue\n");
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
        errorStream.add((char *)"Unable to decode IE EpcTimerIe\n");
        return false;
    }
}
void EpcTimerIe::displayEpcTimerIe_v(EpcTimerIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"EpcTimerIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"timerUnit: "); 
    stream.add((Uint8)data.timerUnit);
    stream.endOfLine();
  
    stream.add( (char *)"timerValue: "); 
    stream.add((Uint8)data.timerValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
