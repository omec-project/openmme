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


#include "pagingAndServiceInformationIe.h"
#include "dataTypeCodecUtils.h"

PagingAndServiceInformationIe::PagingAndServiceInformationIe() 
{
    ieType = 186;
    // TODO

}

PagingAndServiceInformationIe::~PagingAndServiceInformationIe() {
    // TODO Auto-generated destructor stub
}

bool PagingAndServiceInformationIe::encodePagingAndServiceInformationIe(MsgBuffer &buffer, PagingAndServiceInformationIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.epsBearerId, 4)))
    {
        errorStream.add((char *)"Encoding of epsBearerId failed\n");
        return false;
    }
    buffer.skipBits(7);

    if(!(buffer.writeBits(data.ppi, 1)))
    {
        errorStream.add((char *)"Encoding of ppi failed\n");
        return false;
    }
    buffer.skipBits(2);

    if (!(data.ppiValue==1))
    {
        errorStream.add((char *)"Data validation failure: ppiValue\n");
        return false; 
    }
    if(!(buffer.writeBits(data.ppiValue, 6)))
    {
        errorStream.add((char *)"Encoding of ppiValue failed\n");
        return false;
    }

    return true;
}

bool PagingAndServiceInformationIe::decodePagingAndServiceInformationIe(MsgBuffer &buffer, PagingAndServiceInformationIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(4);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.epsBearerId = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: epsBearerId\n");
        return false;
    }
    buffer.skipBits(7);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.ppi = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: ppi\n");
        return false;
    }
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.ppiValue = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: ppiValue\n");
        return false;
    }
    if (!(data.ppiValue==1))
    {
        errorStream.add((char *)"Data validation failure : ppiValue\n");
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
        errorStream.add((char *)"Unable to decode IE PagingAndServiceInformationIe\n");
        return false;
    }
}
void PagingAndServiceInformationIe::displayPagingAndServiceInformationIe_v(PagingAndServiceInformationIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"PagingAndServiceInformationIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"epsBearerId: "); 
    stream.add((Uint8)data.epsBearerId);
    stream.endOfLine();
  
    stream.add( (char *)"ppi: "); 
    stream.add((Uint8)data.ppi);
    stream.endOfLine();
  
    stream.add( (char *)"ppiValue: "); 
    stream.add((Uint8)data.ppiValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
