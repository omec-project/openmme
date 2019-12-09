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


#include "cnOperatorSelectionEntityIe.h"
#include "dataTypeCodecUtils.h"

CnOperatorSelectionEntityIe::CnOperatorSelectionEntityIe() 
{
    ieType = 173;
    // TODO

}

CnOperatorSelectionEntityIe::~CnOperatorSelectionEntityIe() {
    // TODO Auto-generated destructor stub
}

bool CnOperatorSelectionEntityIe::encodeCnOperatorSelectionEntityIe(MsgBuffer &buffer, CnOperatorSelectionEntityIeData const &data)
{
    buffer.skipBits(6);

    if (!(data.cnOpselectionEntity<= 3))
    {
        errorStream.add((char *)"Data validation failure: cnOpselectionEntity\n");
        return false; 
    }
    if(!(buffer.writeBits(data.cnOpselectionEntity, 2)))
    {
        errorStream.add((char *)"Encoding of cnOpselectionEntity failed\n");
        return false;
    }

    return true;
}

bool CnOperatorSelectionEntityIe::decodeCnOperatorSelectionEntityIe(MsgBuffer &buffer, CnOperatorSelectionEntityIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(6);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.cnOpselectionEntity = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: cnOpselectionEntity\n");
        return false;
    }
    if (!(data.cnOpselectionEntity<= 3))
    {
        errorStream.add((char *)"Data validation failure : cnOpselectionEntity\n");
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
        errorStream.add((char *)"Unable to decode IE CnOperatorSelectionEntityIe\n");
        return false;
    }
}
void CnOperatorSelectionEntityIe::displayCnOperatorSelectionEntityIe_v(CnOperatorSelectionEntityIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"CnOperatorSelectionEntityIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"cnOpselectionEntity: "); 
    stream.add((Uint8)data.cnOpselectionEntity);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
