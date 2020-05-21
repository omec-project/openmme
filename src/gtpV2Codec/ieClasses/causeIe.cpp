/*
 * causeIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "causeIe.h"
#include "dataTypeCodecUtils.h"

CauseIe::CauseIe() 
{
    ieType = 2;
    // TODO

}

CauseIe::~CauseIe() {
    // TODO Auto-generated destructor stub
}

bool CauseIe::encodeCauseIe(MsgBuffer &buffer, CauseIeData const &data)
{
    if (!(buffer.writeUint8(data.causeValue)))
    {
        errorStream.add("Encoding of causeValue failed\n");
        return false;
    }
    buffer.skipBits(5);

    if(!(buffer.writeBits(data.pce, 1)))
    {
        errorStream.add("Encoding of pce failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.pbe, 1)))
    {
        errorStream.add("Encoding of pbe failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.cs, 1)))
    {
        errorStream.add("Encoding of cs failed\n");
        return false;
    }
    if (data.offendingIeDataPresent)
    {
        if (!(DataTypeCodecUtils::encodeOffendingIeData(buffer, data.offendingIeData)))
        {
            errorStream.add("Encoding of offendingIeData failed\n");
            return false;
        }
    }

    return true;
}

bool CauseIe::decodeCauseIe(MsgBuffer &buffer, CauseIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.causeValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: causeValue\n");
        return false;
    }
    buffer.skipBits(5);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.pce = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: pce\n");
        return false;
    }
    data.pbe = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: pbe\n");
        return false;
    }
    data.cs = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: cs\n");
        return false;
    }

    if (length == 6)
    {
        lengthLeft = ieBoundary - buffer.getCurrentIndex();
        if (!(DataTypeCodecUtils::decodeOffendingIeData(buffer, data.offendingIeData, lengthLeft)))
        {
            errorStream.add("Failed to decode: offendingIeData\n");
            return false;
        }
        data.offendingIeDataPresent = true;
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
        errorStream.add("Unable to decode IE CauseIe\n");
        return false;
    }
}
void CauseIe::displayCauseIe_v(CauseIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("CauseIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("causeValue: ");
    stream.add(data.causeValue);
    stream.endOfLine();
  
    stream.add( "pce: "); 
    stream.add((Uint8)data.pce);
    stream.endOfLine();
  
    stream.add( "pbe: "); 
    stream.add((Uint8)data.pbe);
    stream.endOfLine();
  
    stream.add( "cs: "); 
    stream.add((Uint8)data.cs);
    stream.endOfLine();
  
    if (data.offendingIeDataPresent)
    {
        stream.add("offendingIeData:");
        stream.endOfLine();
        DataTypeCodecUtils::displayOffendingIeData_v(data.offendingIeData, stream);
    }   
    stream.decrIndent();
    stream.decrIndent();
}
