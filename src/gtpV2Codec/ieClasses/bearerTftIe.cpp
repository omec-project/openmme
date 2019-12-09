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


#include "bearerTftIe.h"
#include "dataTypeCodecUtils.h"

BearerTftIe::BearerTftIe() 
{
    ieType = 84;
    // TODO

}

BearerTftIe::~BearerTftIe() {
    // TODO Auto-generated destructor stub
}

bool BearerTftIe::encodeBearerTftIe(MsgBuffer &buffer, BearerTftIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.tft)))
    {
    errorStream.add((char *)"Encoding of tft failed\n");
    return false;
    }

    return true;
}

bool BearerTftIe::decodeBearerTftIe(MsgBuffer &buffer, BearerTftIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.tft, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: tft\n");
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
        errorStream.add((char *)"Unable to decode IE BearerTftIe\n");
        return false;
    }
}
void BearerTftIe::displayBearerTftIe_v(BearerTftIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"BearerTftIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"tft:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array16_v(data.tft, stream);
    stream.decrIndent();
    stream.decrIndent();
}
