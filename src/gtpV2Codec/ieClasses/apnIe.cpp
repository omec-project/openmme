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


#include "apnIe.h"
#include "dataTypeCodecUtils.h"

ApnIe::ApnIe() 
{
    ieType = 71;
    // TODO

}

ApnIe::~ApnIe() {
    // TODO Auto-generated destructor stub
}

bool ApnIe::encodeApnIe(MsgBuffer &buffer, ApnIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array32(buffer, data.apnValue)))
    {
    errorStream.add((char *)"Encoding of apnValue failed\n");
    return false;
    }

    return true;
}

bool ApnIe::decodeApnIe(MsgBuffer &buffer, ApnIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array32(buffer, data.apnValue, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: apnValue\n");
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
        errorStream.add((char *)"Unable to decode IE ApnIe\n");
        return false;
    }
}
void ApnIe::displayApnIe_v(ApnIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ApnIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"apnValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array32_v(data.apnValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
