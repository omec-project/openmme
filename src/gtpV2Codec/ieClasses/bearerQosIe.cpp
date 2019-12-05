/*
 * bearerQosIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "bearerQosIe.h"
#include "dataTypeCodecUtils.h"

BearerQosIe::BearerQosIe() 
{
    ieType = 80;
    // TODO

}

BearerQosIe::~BearerQosIe() {
    // TODO Auto-generated destructor stub
}

bool BearerQosIe::encodeBearerQosIe(MsgBuffer &buffer, BearerQosIeData const &data)
{
    buffer.skipBits(1);

    if(!(buffer.writeBits(data.pci, 1)))
    {
        errorStream.add("Encoding of pci failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.pl, 4)))
    {
        errorStream.add("Encoding of pl failed\n");
        return false;
    }

    buffer.skipBits(1);

    if(!(buffer.writeBits(data.pvi, 1)))
    {
        errorStream.add("Encoding of pvi failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.qci)))
    {
        errorStream.add("Encoding of qci failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeUint8Array5(buffer, data.maxBitRateUl)))
    {
    errorStream.add("Encoding of maxBitRateUl failed\n");
    return false;
    }
    if (!(DataTypeCodecUtils::encodeUint8Array5(buffer, data.maxBitRateDl)))
    {
    errorStream.add("Encoding of maxBitRateDl failed\n");
    return false;
    }
    if (!(DataTypeCodecUtils::encodeUint8Array5(buffer, data.guraranteedBitRateUl)))
    {
    errorStream.add("Encoding of guraranteedBitRateUl failed\n");
    return false;
    }
    if (!(DataTypeCodecUtils::encodeUint8Array5(buffer, data.guaranteedBitRateDl)))
    {
    errorStream.add("Encoding of guaranteedBitRateDl failed\n");
    return false;
    }

    return true;
}

bool BearerQosIe::decodeBearerQosIe(MsgBuffer &buffer, BearerQosIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(1);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.pci = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: pci\n");
        return false;
    }
    data.pl = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: pl\n");
        return false;
    }
    buffer.skipBits(1);
    data.pvi = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: pvi\n");
        return false;
    }

    buffer.readUint8(data.qci);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: qci\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array5(buffer, data.maxBitRateUl, lengthLeft, 5)))
    {
        errorStream.add("Failed to decode: maxBitRateUl\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array5(buffer, data.maxBitRateDl, lengthLeft, 5)))
    {
        errorStream.add("Failed to decode: maxBitRateDl\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array5(buffer, data.guraranteedBitRateUl, lengthLeft, 5)))
    {
        errorStream.add("Failed to decode: guraranteedBitRateUl\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array5(buffer, data.guaranteedBitRateDl, lengthLeft, 5)))
    {
        errorStream.add("Failed to decode: guaranteedBitRateDl\n");
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
        errorStream.add("Unable to decode IE BearerQosIe\n");
        return false;
    }
}
void BearerQosIe::displayBearerQosIe_v(BearerQosIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("BearerQosIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "pci: "); 
    stream.add((Uint8)data.pci);
    stream.endOfLine();
  
    stream.add( "pl: "); 
    stream.add((Uint8)data.pl);
    stream.endOfLine();
  
    stream.add( "pvi: "); 
    stream.add((Uint8)data.pvi);
    stream.endOfLine();
  
    stream.add("qci: ");
    stream.add(data.qci);
    stream.endOfLine();
  
    stream.add("maxBitRateUl:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array5_v(data.maxBitRateUl, stream);
  
    stream.add("maxBitRateDl:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array5_v(data.maxBitRateDl, stream);
  
    stream.add("guraranteedBitRateUl:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array5_v(data.guraranteedBitRateUl, stream);
  
    stream.add("guaranteedBitRateDl:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array5_v(data.guaranteedBitRateDl, stream);
    stream.decrIndent();
    stream.decrIndent();
}
