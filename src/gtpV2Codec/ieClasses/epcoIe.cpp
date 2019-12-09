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


#include "epcoIe.h"
#include "dataTypeCodecUtils.h"

EpcoIe::EpcoIe() 
{
    ieType = 197;
    // TODO

}

EpcoIe::~EpcoIe() {
    // TODO Auto-generated destructor stub
}

bool EpcoIe::encodeEpcoIe(MsgBuffer &buffer, EpcoIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.epco)))
    {
    errorStream.add((char *)"Encoding of epco failed\n");
    return false;
    }

    return true;
}

bool EpcoIe::decodeEpcoIe(MsgBuffer &buffer, EpcoIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.epco, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: epco\n");
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
        errorStream.add((char *)"Unable to decode IE EpcoIe\n");
        return false;
    }
}
void EpcoIe::displayEpcoIe_v(EpcoIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"EpcoIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"epco:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array16_v(data.epco, stream);
    stream.decrIndent();
    stream.decrIndent();
}
