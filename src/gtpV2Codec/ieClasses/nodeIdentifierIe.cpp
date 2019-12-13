/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "nodeIdentifierIe.h"
#include "dataTypeCodecUtils.h"

NodeIdentifierIe::NodeIdentifierIe() 
{
    ieType = 176;
    // TODO

}

NodeIdentifierIe::~NodeIdentifierIe() {
    // TODO Auto-generated destructor stub
}

bool NodeIdentifierIe::encodeNodeIdentifierIe(MsgBuffer &buffer, NodeIdentifierIeData const &data)
{
    if (!(data.lengthOfNodeName!=0))
    {
        errorStream.add((char *)"Data validation failure: lengthOfNodeName\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.lengthOfNodeName)))
    {
        errorStream.add((char *)"Encoding of lengthOfNodeName failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.nodeName)))
    {
        errorStream.add((char *)"Encoding of nodeName failed\n");
        return false;
    }
    if (!(data.lengthOfNodeRealm!=0))
    {
        errorStream.add((char *)"Data validation failure: lengthOfNodeRealm\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.lengthOfNodeRealm)))
    {
        errorStream.add((char *)"Encoding of lengthOfNodeRealm failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.nodeRealm)))
    {
        errorStream.add((char *)"Encoding of nodeRealm failed\n");
        return false;
    }

    return true;
}

bool NodeIdentifierIe::decodeNodeIdentifierIe(MsgBuffer &buffer, NodeIdentifierIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.lengthOfNodeName);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: lengthOfNodeName\n");
        return false;
    }
    if (!(data.lengthOfNodeName!=0))
    {
        errorStream.add((char *)"Data validation failure : lengthOfNodeName\n");
        return false; //TODO need to add validations
    }

    buffer.readUint8(data.nodeName);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: nodeName\n");
        return false;
    }

    buffer.readUint8(data.lengthOfNodeRealm);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: lengthOfNodeRealm\n");
        return false;
    }
    if (!(data.lengthOfNodeRealm!=0))
    {
        errorStream.add((char *)"Data validation failure : lengthOfNodeRealm\n");
        return false; //TODO need to add validations
    }

    buffer.readUint8(data.nodeRealm);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: nodeRealm\n");
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
        errorStream.add((char *)"Unable to decode IE NodeIdentifierIe\n");
        return false;
    }
}
void NodeIdentifierIe::displayNodeIdentifierIe_v(NodeIdentifierIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"NodeIdentifierIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"lengthOfNodeName: ");
    stream.add(data.lengthOfNodeName);
    stream.endOfLine();
  
    stream.add((char *)"nodeName: ");
    stream.add(data.nodeName);
    stream.endOfLine();
  
    stream.add((char *)"lengthOfNodeRealm: ");
    stream.add(data.lengthOfNodeRealm);
    stream.endOfLine();
  
    stream.add((char *)"nodeRealm: ");
    stream.add(data.nodeRealm);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
