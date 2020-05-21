/*
 * ip4cpIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "ip4cpIe.h"
#include "dataTypeCodecUtils.h"

Ip4cpIe::Ip4cpIe() 
{
    ieType = 166;
    // TODO

}

Ip4cpIe::~Ip4cpIe() {
    // TODO Auto-generated destructor stub
}

bool Ip4cpIe::encodeIp4cpIe(MsgBuffer &buffer, Ip4cpIeData const &data)
{
    if (!(buffer.writeUint8(data.subnetPrefixLength)))
    {
        errorStream.add("Encoding of subnetPrefixLength failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeIpAddressV4(buffer, data.iPv4DefaultRouterAddress)))
    {
    errorStream.add("Encoding of iPv4DefaultRouterAddress failed\n");
    return false;
    }

    return true;
}

bool Ip4cpIe::decodeIp4cpIe(MsgBuffer &buffer, Ip4cpIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.subnetPrefixLength);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: subnetPrefixLength\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeIpAddressV4(buffer, data.iPv4DefaultRouterAddress, lengthLeft)))
    {
        errorStream.add("Failed to decode: iPv4DefaultRouterAddress\n");
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
        errorStream.add("Unable to decode IE Ip4cpIe\n");
        return false;
    }
}
void Ip4cpIe::displayIp4cpIe_v(Ip4cpIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("Ip4cpIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("subnetPrefixLength: ");
    stream.add(data.subnetPrefixLength);
    stream.endOfLine();
  
    stream.add("iPv4DefaultRouterAddress:");
    stream.endOfLine();
    DataTypeCodecUtils::displayIpAddressV4_v(data.iPv4DefaultRouterAddress, stream);
    stream.decrIndent();
    stream.decrIndent();
}
