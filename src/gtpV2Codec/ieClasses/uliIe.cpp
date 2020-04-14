/*
 * uliIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "uliIe.h"
#include "dataTypeCodecUtils.h"

UliIe::UliIe() 
{
    ieType = 86;
    // TODO

}

UliIe::~UliIe() {
    // TODO Auto-generated destructor stub
}

bool UliIe::encodeUliIe(MsgBuffer &buffer, UliIeData const &data)
{
    buffer.skipBits(2);

    if(!(buffer.writeBits(data.laipresent, 1)))
    {
        errorStream.add("Encoding of laipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.ecgipresent, 1)))
    {
        errorStream.add("Encoding of ecgipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.taipresent, 1)))
    {
        errorStream.add("Encoding of taipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.raipresent, 1)))
    {
        errorStream.add("Encoding of raipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.saipresent, 1)))
    {
        errorStream.add("Encoding of saipresent failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.cgipresent, 1)))
    {
        errorStream.add("Encoding of cgipresent failed\n");
        return false;
    }
    if (data.cgipresent)
    {
        if (!(DataTypeCodecUtils::encodeCgiField(buffer, data.cgi)))
        {
            errorStream.add("Encoding of cgi failed\n");
            return false;
        }
    }
    if (data.saipresent)
    {
        if (!(DataTypeCodecUtils::encodeSaiField(buffer, data.sai)))
        {
            errorStream.add("Encoding of sai failed\n");
            return false;
        }
    }
    if (data.raipresent)
    {
        if (!(DataTypeCodecUtils::encodeRaiField(buffer, data.rai)))
        {
            errorStream.add("Encoding of rai failed\n");
            return false;
        }
    }
    if (data.taipresent)
    {
        if (!(DataTypeCodecUtils::encodeTaiField(buffer, data.tai)))
        {
            errorStream.add("Encoding of tai failed\n");
            return false;
        }
    }
    if (data.ecgipresent)
    {
        if (!(DataTypeCodecUtils::encodeEcgiField(buffer, data.ecgi)))
        {
            errorStream.add("Encoding of ecgi failed\n");
            return false;
        }
    }
    if (data.laipresent)
    {
        if (!(DataTypeCodecUtils::encodeLaiField(buffer, data.lai)))
        {
            errorStream.add("Encoding of lai failed\n");
            return false;
        }
    }

    return true;
}

bool UliIe::decodeUliIe(MsgBuffer &buffer, UliIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.laipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: laipresent\n");
        return false;
    }
    data.ecgipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: ecgipresent\n");
        return false;
    }
    data.taipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: taipresent\n");
        return false;
    }
    data.raipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: raipresent\n");
        return false;
    }
    data.saipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: saipresent\n");
        return false;
    }
    data.cgipresent = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: cgipresent\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeCgiField(buffer, data.cgi, lengthLeft)))
    {
        errorStream.add("Failed to decode: cgi\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeSaiField(buffer, data.sai, lengthLeft)))
    {
        errorStream.add("Failed to decode: sai\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeRaiField(buffer, data.rai, lengthLeft)))
    {
        errorStream.add("Failed to decode: rai\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeTaiField(buffer, data.tai, lengthLeft)))
    {
        errorStream.add("Failed to decode: tai\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeEcgiField(buffer, data.ecgi, lengthLeft)))
    {
        errorStream.add("Failed to decode: ecgi\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeLaiField(buffer, data.lai, lengthLeft)))
    {
        errorStream.add("Failed to decode: lai\n");
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
        errorStream.add("Unable to decode IE UliIe\n");
        return false;
    }
}
void UliIe::displayUliIe_v(UliIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("UliIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "laipresent: "); 
    stream.add((Uint8)data.laipresent);
    stream.endOfLine();
  
    stream.add( "ecgipresent: "); 
    stream.add((Uint8)data.ecgipresent);
    stream.endOfLine();
  
    stream.add( "taipresent: "); 
    stream.add((Uint8)data.taipresent);
    stream.endOfLine();
  
    stream.add( "raipresent: "); 
    stream.add((Uint8)data.raipresent);
    stream.endOfLine();
  
    stream.add( "saipresent: "); 
    stream.add((Uint8)data.saipresent);
    stream.endOfLine();
  
    stream.add( "cgipresent: "); 
    stream.add((Uint8)data.cgipresent);
    stream.endOfLine();
  
    if (data.cgipresent)
    {
        stream.add("cgi:");
        stream.endOfLine();
        DataTypeCodecUtils::displayCgiField_v(data.cgi, stream);
    }
  
    if (data.saipresent)
    {
        stream.add("sai:");
        stream.endOfLine();
        DataTypeCodecUtils::displaySaiField_v(data.sai, stream);
    }
  
    if (data.raipresent)
    {
        stream.add("rai:");
        stream.endOfLine();
        DataTypeCodecUtils::displayRaiField_v(data.rai, stream);
    }
  
    if (data.taipresent)
    {
        stream.add("tai:");
        stream.endOfLine();
        DataTypeCodecUtils::displayTaiField_v(data.tai, stream);
    }
  
    if (data.ecgipresent)
    {
        stream.add("ecgi:");
        stream.endOfLine();
        DataTypeCodecUtils::displayEcgiField_v(data.ecgi, stream);
    }
  
    if (data.laipresent)
    {
        stream.add("lai:");
        stream.endOfLine();
        DataTypeCodecUtils::displayLaiField_v(data.lai, stream);
    }
    stream.decrIndent();
    stream.decrIndent();
}
