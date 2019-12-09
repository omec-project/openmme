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


#include "meiIe.h"
#include "dataTypeCodecUtils.h"

MeiIe::MeiIe() 
{
    ieType = 75;
    // TODO

}

MeiIe::~MeiIe() {
    // TODO Auto-generated destructor stub
}

bool MeiIe::encodeMeiIe(MsgBuffer &buffer, MeiIeData const &data)
{
    if (!(data.imeiSvValue.length ==15 || data.imeiSvValue.length == 16))
    {
        errorStream.add((char *)"Data validation failure: imeiSvValue\n");
        return false; 
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.imeiSvValue)))
    {
    errorStream.add((char *)"Encoding of imeiSvValue failed\n");
    return false;
    }

    return true;
}

bool MeiIe::decodeMeiIe(MsgBuffer &buffer, MeiIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.imeiSvValue, lengthLeft)))
    {
        errorStream.add((char *)"Failed to decode: imeiSvValue\n");
        return false;
    }
    if (!(data.imeiSvValue.length ==15 || data.imeiSvValue.length == 16))
    {
        errorStream.add((char *)"Data validation failure : imeiSvValue\n");
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
        errorStream.add((char *)"Unable to decode IE MeiIe\n");
        return false;
    }
}
void MeiIe::displayMeiIe_v(MeiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"MeiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"imeiSvValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.imeiSvValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
