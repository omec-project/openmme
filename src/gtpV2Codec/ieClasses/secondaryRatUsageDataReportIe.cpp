/*
 * secondaryRatUsageDataReportIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "secondaryRatUsageDataReportIe.h"
#include "dataTypeCodecUtils.h"

SecondaryRatUsageDataReportIe::SecondaryRatUsageDataReportIe() 
{
    ieType = 201;
    // TODO

}

SecondaryRatUsageDataReportIe::~SecondaryRatUsageDataReportIe() {
    // TODO Auto-generated destructor stub
}

bool SecondaryRatUsageDataReportIe::encodeSecondaryRatUsageDataReportIe(MsgBuffer &buffer, SecondaryRatUsageDataReportIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.irsgw, 2)))
    {
        errorStream.add("Encoding of irsgw failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.irpgw, 2)))
    {
        errorStream.add("Encoding of irpgw failed\n");
        return false;
    }
    if (!(data.secondaryRatType== 0 || data.secondaryRatType== 1))
    {
        errorStream.add("Data validation failure: secondaryRatType\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.secondaryRatType)))
    {
        errorStream.add("Encoding of secondaryRatType failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.epsBearerId, 4)))
    {
        errorStream.add("Encoding of epsBearerId failed\n");
        return false;
    }
    if (!(buffer.writeUint32(data.starttimestamp)))
    {
        errorStream.add("Encoding of starttimestamp failed\n");
        return false;
    }
    if (!(buffer.writeUint32(data.endtimestamp)))
    {
        errorStream.add("Encoding of endtimestamp failed\n");
        return false;
    }
    if (!(buffer.writeUint64(data.usageDataDL)))
    {
        errorStream.add("Encoding of usageDataDL failed\n");
        return false;
    }
    if (!(buffer.writeUint64(data.usageDataUL)))
    {
        errorStream.add("Encoding of usageDataUL failed\n");
        return false;
    }

    return true;
}

bool SecondaryRatUsageDataReportIe::decodeSecondaryRatUsageDataReportIe(MsgBuffer &buffer, SecondaryRatUsageDataReportIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(4);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.irsgw = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: irsgw\n");
        return false;
    }
    data.irpgw = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: irpgw\n");
        return false;
    }

    buffer.readUint8(data.secondaryRatType);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: secondaryRatType\n");
        return false;
    }
    if (!(data.secondaryRatType== 0 || data.secondaryRatType== 1))
    {
        errorStream.add("Data validation failure : secondaryRatType\n");
        return false; //TODO need to add validations
    }
    data.epsBearerId = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: epsBearerId\n");
        return false;
    }

    buffer.readUint32(data.starttimestamp);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: starttimestamp\n");
        return false;
    }

    buffer.readUint32(data.endtimestamp);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: endtimestamp\n");
        return false;
    }

    buffer.readUint64(data.usageDataDL);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: usageDataDL\n");
        return false;
    }

    buffer.readUint64(data.usageDataUL);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: usageDataUL\n");
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
        errorStream.add("Unable to decode IE SecondaryRatUsageDataReportIe\n");
        return false;
    }
}
void SecondaryRatUsageDataReportIe::displaySecondaryRatUsageDataReportIe_v(SecondaryRatUsageDataReportIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("SecondaryRatUsageDataReportIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "irsgw: "); 
    stream.add((Uint8)data.irsgw);
    stream.endOfLine();
  
    stream.add( "irpgw: "); 
    stream.add((Uint8)data.irpgw);
    stream.endOfLine();
  
    stream.add("secondaryRatType: ");
    stream.add(data.secondaryRatType);
    stream.endOfLine();
  
    stream.add( "epsBearerId: "); 
    stream.add((Uint8)data.epsBearerId);
    stream.endOfLine();
  
    stream.add("starttimestamp: ");
    stream.add(data.starttimestamp);
    stream.endOfLine();
  
    stream.add("endtimestamp: ");
    stream.add(data.endtimestamp);
    stream.endOfLine();
  
    stream.add("usageDataDL: ");
    stream.add(data.usageDataDL);
    stream.endOfLine();
  
    stream.add("usageDataUL: ");
    stream.add(data.usageDataUL);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
