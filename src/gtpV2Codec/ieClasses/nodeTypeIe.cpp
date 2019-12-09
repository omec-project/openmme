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


#include "nodeTypeIe.h"
#include "dataTypeCodecUtils.h"

NodeTypeIe::NodeTypeIe() 
{
    ieType = 135;
    // TODO

}

NodeTypeIe::~NodeTypeIe() {
    // TODO Auto-generated destructor stub
}

bool NodeTypeIe::encodeNodeTypeIe(MsgBuffer &buffer, NodeTypeIeData const &data)
{
    if (!(data.nodeType==0||data.nodeType==1))
    {
        errorStream.add((char *)"Data validation failure: nodeType\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.nodeType)))
    {
        errorStream.add((char *)"Encoding of nodeType failed\n");
        return false;
    }

    return true;
}

bool NodeTypeIe::decodeNodeTypeIe(MsgBuffer &buffer, NodeTypeIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.nodeType);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: nodeType\n");
        return false;
    }
    if (!(data.nodeType==0||data.nodeType==1))
    {
        errorStream.add((char *)"Data validation failure : nodeType\n");
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
        errorStream.add((char *)"Unable to decode IE NodeTypeIe\n");
        return false;
    }
}
void NodeTypeIe::displayNodeTypeIe_v(NodeTypeIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"NodeTypeIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"nodeType: ");
    stream.add(data.nodeType);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
