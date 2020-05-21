/*
 * msisdnIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "msisdnIe.h"
#include "dataTypeCodecUtils.h"

MsisdnIe::MsisdnIe() 
{
    ieType = 76;
    // TODO

}

MsisdnIe::~MsisdnIe() {
    // TODO Auto-generated destructor stub
}

bool MsisdnIe::encodeMsisdnIe(MsgBuffer &buffer, MsisdnIeData const &data)
{
    if (!(data.msisdnValue.length>=9 && data.msisdnValue.length <=15))
    {
        errorStream.add("Data validation failure: msisdnValue\n");
        return false; 
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.msisdnValue)))
    {
    errorStream.add("Encoding of msisdnValue failed\n");
    return false;
    }

    return true;
}

bool MsisdnIe::decodeMsisdnIe(MsgBuffer &buffer, MsisdnIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.msisdnValue, lengthLeft)))
    {
        errorStream.add("Failed to decode: msisdnValue\n");
        return false;
    }
    if (!(data.msisdnValue.length>=9 && data.msisdnValue.length <=15))
    {
        errorStream.add("Data validation failure : msisdnValue\n");
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
        errorStream.add("Unable to decode IE MsisdnIe\n");
        return false;
    }
}
void MsisdnIe::displayMsisdnIe_v(MsisdnIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("MsisdnIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("msisdnValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.msisdnValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
