/*
 * nodeIdentifierIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
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
        errorStream.add("Data validation failure: lengthOfNodeName\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.lengthOfNodeName)))
    {
        errorStream.add("Encoding of lengthOfNodeName failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.nodeName)))
    {
        errorStream.add("Encoding of nodeName failed\n");
        return false;
    }
    if (!(data.lengthOfNodeRealm!=0))
    {
        errorStream.add("Data validation failure: lengthOfNodeRealm\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.lengthOfNodeRealm)))
    {
        errorStream.add("Encoding of lengthOfNodeRealm failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.nodeRealm)))
    {
        errorStream.add("Encoding of nodeRealm failed\n");
        return false;
    }

    return true;
}

bool NodeIdentifierIe::decodeNodeIdentifierIe(MsgBuffer &buffer, NodeIdentifierIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.lengthOfNodeName);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: lengthOfNodeName\n");
        return false;
    }
    if (!(data.lengthOfNodeName!=0))
    {
        errorStream.add("Data validation failure : lengthOfNodeName\n");
        return false; //TODO need to add validations
    }

    buffer.readUint8(data.nodeName);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: nodeName\n");
        return false;
    }

    buffer.readUint8(data.lengthOfNodeRealm);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: lengthOfNodeRealm\n");
        return false;
    }
    if (!(data.lengthOfNodeRealm!=0))
    {
        errorStream.add("Data validation failure : lengthOfNodeRealm\n");
        return false; //TODO need to add validations
    }

    buffer.readUint8(data.nodeRealm);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: nodeRealm\n");
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
        errorStream.add("Unable to decode IE NodeIdentifierIe\n");
        return false;
    }
}
void NodeIdentifierIe::displayNodeIdentifierIe_v(NodeIdentifierIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("NodeIdentifierIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("lengthOfNodeName: ");
    stream.add(data.lengthOfNodeName);
    stream.endOfLine();
  
    stream.add("nodeName: ");
    stream.add(data.nodeName);
    stream.endOfLine();
  
    stream.add("lengthOfNodeRealm: ");
    stream.add(data.lengthOfNodeRealm);
    stream.endOfLine();
  
    stream.add("nodeRealm: ");
    stream.add(data.nodeRealm);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
