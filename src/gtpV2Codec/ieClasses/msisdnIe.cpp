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


#include "msisdnIe.h"
#include "dataTypeCodecUtils.h"

MsisdnIe::MsisdnIe() 
{
    ieType = 76;
    // TODO

}

MsisdnIe::~MsisdnIe() {
    // TODO Auto-generated destructor stub
}

bool MsisdnIe::encodeMsisdnIe(MsgBuffer &buffer, MsisdnIeData const &data)
{
    if (!(data.msisdnValue.length>=9 && data.msisdnValue.length <=15))
    {
        errorStream.add((char *)"Data validation failure: msisdnValue\n");
        return false; 
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.msisdnValue)))
    {
    errorStream.add((char *)"Encoding of msisdnValue failed\n");
    return false;
    }

    return true;
}

bool MsisdnIe::decodeMsisdnIe(MsgBuffer &buffer, MsisdnIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.msisdnValue, lengthLeft)))
    {
        errorStream.add((char *)"Failed to decode: msisdnValue\n");
        return false;
    }
    if (!(data.msisdnValue.length>=9 && data.msisdnValue.length <=15))
    {
        errorStream.add((char *)"Data validation failure : msisdnValue\n");
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
        errorStream.add((char *)"Unable to decode IE MsisdnIe\n");
        return false;
    }
}
void MsisdnIe::displayMsisdnIe_v(MsisdnIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"MsisdnIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"msisdnValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.msisdnValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
