/*
 * traceInformationIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "traceInformationIe.h"
#include "dataTypeCodecUtils.h"

TraceInformationIe::TraceInformationIe() 
{
    ieType = 96;
    // TODO

}

TraceInformationIe::~TraceInformationIe() {
    // TODO Auto-generated destructor stub
}

bool TraceInformationIe::encodeTraceInformationIe(MsgBuffer &buffer, TraceInformationIeData const &data)
{
    if(!(buffer.writeBits(data.mccDigit2, 4)))
    {
        errorStream.add("Encoding of mccDigit2 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mccDigit1, 4)))
    {
        errorStream.add("Encoding of mccDigit1 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit3, 4)))
    {
        errorStream.add("Encoding of mncDigit3 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mccDigit3, 4)))
    {
        errorStream.add("Encoding of mccDigit3 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit2, 4)))
    {
        errorStream.add("Encoding of mncDigit2 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit1, 4)))
    {
        errorStream.add("Encoding of mncDigit1 failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeUint8Array4(buffer, data.traceId)))
    {
    errorStream.add("Encoding of traceId failed\n");
    return false;
    }
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.triggeringEvents)))
    {
    errorStream.add("Encoding of triggeringEvents failed\n");
    return false;
    }
    if (!(buffer.writeUint16(data.listOfNeTypes)))
    {
        errorStream.add("Encoding of listOfNeTypes failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.sessionTraceDepth)))
    {
        errorStream.add("Encoding of sessionTraceDepth failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeUint8Array16(buffer, data.listOfInterfaces)))
    {
    errorStream.add("Encoding of listOfInterfaces failed\n");
    return false;
    }
    if (!(DataTypeCodecUtils::encodeIpAddressV4(buffer, data.ipAddressOfTce)))
    {
    errorStream.add("Encoding of ipAddressOfTce failed\n");
    return false;
    }

    return true;
}

bool TraceInformationIe::decodeTraceInformationIe(MsgBuffer &buffer, TraceInformationIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mccDigit2\n");
        return false;
    }
    data.mccDigit1 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mccDigit1\n");
        return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mncDigit3\n");
        return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mccDigit3\n");
        return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mncDigit2\n");
        return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mncDigit1\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array4(buffer, data.traceId, lengthLeft, 3)))
    {
        errorStream.add("Failed to decode: traceId\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.triggeringEvents, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: triggeringEvents\n");
        return false;
    }

    buffer.readUint16(data.listOfNeTypes);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: listOfNeTypes\n");
        return false;
    }

    buffer.readUint8(data.sessionTraceDepth);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: sessionTraceDepth\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array16(buffer, data.listOfInterfaces, lengthLeft, 0)))
    {
        errorStream.add("Failed to decode: listOfInterfaces\n");
        return false;
    }
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeIpAddressV4(buffer, data.ipAddressOfTce, lengthLeft)))
    {
        errorStream.add("Failed to decode: ipAddressOfTce\n");
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
        errorStream.add("Unable to decode IE TraceInformationIe\n");
        return false;
    }
}
void TraceInformationIe::displayTraceInformationIe_v(TraceInformationIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("TraceInformationIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "mccDigit2: "); 
    stream.add((Uint8)data.mccDigit2);
    stream.endOfLine();
  
    stream.add( "mccDigit1: "); 
    stream.add((Uint8)data.mccDigit1);
    stream.endOfLine();
  
    stream.add( "mncDigit3: "); 
    stream.add((Uint8)data.mncDigit3);
    stream.endOfLine();
  
    stream.add( "mccDigit3: "); 
    stream.add((Uint8)data.mccDigit3);
    stream.endOfLine();
  
    stream.add( "mncDigit2: "); 
    stream.add((Uint8)data.mncDigit2);
    stream.endOfLine();
  
    stream.add( "mncDigit1: "); 
    stream.add((Uint8)data.mncDigit1);
    stream.endOfLine();
  
    stream.add("traceId:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array4_v(data.traceId, stream);
  
    stream.add("triggeringEvents:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array16_v(data.triggeringEvents, stream);
  
    stream.add("listOfNeTypes: ");
    stream.add(data.listOfNeTypes);
    stream.endOfLine();
  
    stream.add("sessionTraceDepth: ");
    stream.add(data.sessionTraceDepth);
    stream.endOfLine();
  
    stream.add("listOfInterfaces:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array16_v(data.listOfInterfaces, stream);
  
    stream.add("ipAddressOfTce:");
    stream.endOfLine();
    DataTypeCodecUtils::displayIpAddressV4_v(data.ipAddressOfTce, stream);
    stream.decrIndent();
    stream.decrIndent();
}
