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


#include "localDistinguishedNameIe.h"
#include "dataTypeCodecUtils.h"

LocalDistinguishedNameIe::LocalDistinguishedNameIe() 
{
    ieType = 151;
    // TODO

}

LocalDistinguishedNameIe::~LocalDistinguishedNameIe() {
    // TODO Auto-generated destructor stub
}

bool LocalDistinguishedNameIe::encodeLocalDistinguishedNameIe(MsgBuffer &buffer, LocalDistinguishedNameIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array512(buffer, data.ldn)))
    {
    errorStream.add((char *)"Encoding of ldn failed\n");
    return false;
    }

    return true;
}

bool LocalDistinguishedNameIe::decodeLocalDistinguishedNameIe(MsgBuffer &buffer, LocalDistinguishedNameIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array512(buffer, data.ldn, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: ldn\n");
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
        errorStream.add((char *)"Unable to decode IE LocalDistinguishedNameIe\n");
        return false;
    }
}
void LocalDistinguishedNameIe::displayLocalDistinguishedNameIe_v(LocalDistinguishedNameIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"LocalDistinguishedNameIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"ldn:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array512_v(data.ldn, stream);
    stream.decrIndent();
    stream.decrIndent();
}
