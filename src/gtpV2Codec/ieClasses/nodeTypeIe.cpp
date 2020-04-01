/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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
