/*
 * maximumPacketLossRateIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "maximumPacketLossRateIe.h"
#include "dataTypeCodecUtils.h"

MaximumPacketLossRateIe::MaximumPacketLossRateIe() 
{
    ieType = 203;
    // TODO

}

MaximumPacketLossRateIe::~MaximumPacketLossRateIe() {
    // TODO Auto-generated destructor stub
}

bool MaximumPacketLossRateIe::encodeMaximumPacketLossRateIe(MsgBuffer &buffer, MaximumPacketLossRateIeData const &data)
{
	/*
    buffer.skipBits(6);

    if(!(buffer.writeBits(data.dl, 1)))
    {
        errorStream.add("Encoding of dl failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.ul, 1)))
    {
        errorStream.add("Encoding of ul failed\n");
        return false;
    }
    if (!(data.ulValue> 0 && data.ulValue<1000))
    {
        errorStream.add("Data validation failure: ulValue\n");
        return false; 
    }
    if (!(buffer.writeUint16(data.ulValue)))
    {
        errorStream.add("Encoding of ulValue failed\n");
        return false;
    }
    if (!(data.dlValue> 0 && data.dlValue<1000))
    {
        errorStream.add("Data validation failure: dlValue\n");
        return false; 
    }
    if (!(buffer.writeUint16(data.dlValue)))
    {
        errorStream.add("Encoding of dlValue failed\n");
        return false;
    }
*/
    return true;
}

bool MaximumPacketLossRateIe::decodeMaximumPacketLossRateIe(MsgBuffer &buffer, MaximumPacketLossRateIeData &data, Uint16 length)
{
       /*	
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(6);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.dl = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: dl\n");
        return false;
    }
    data.ul = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: ul\n");
        return false;
    }

    buffer.readUint16(data.ulValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: ulValue\n");
        return false;
    }
    if (!(data.ulValue> 0 && data.ulValue<1000))
    {
        errorStream.add("Data validation failure : ulValue\n");
        return false; //TODO need to add validations
    }

    buffer.readUint16(data.dlValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: dlValue\n");
        return false;
    }
    if (!(data.dlValue> 0 && data.dlValue<1000))
    {
        errorStream.add("Data validation failure : dlValue\n");
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
        errorStream.add("Unable to decode IE MaximumPacketLossRateIe\n");
        return false;
    }
    */
	return true;
}
void MaximumPacketLossRateIe::displayMaximumPacketLossRateIe_v(MaximumPacketLossRateIeData const &data, Debug &stream)
{/*
    stream.incrIndent();
    stream.add("MaximumPacketLossRateIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "dl: "); 
    stream.add((Uint8)data.dl);
    stream.endOfLine();
  
    stream.add( "ul: "); 
    stream.add((Uint8)data.ul);
    stream.endOfLine();
  
    stream.add("ulValue: ");
    stream.add(data.ulValue);
    stream.endOfLine();
  
    stream.add("dlValue: ");
    stream.add(data.dlValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
    */
}
