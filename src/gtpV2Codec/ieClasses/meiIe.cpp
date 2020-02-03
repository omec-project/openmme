/*
 * meiIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "meiIe.h"
#include "dataTypeCodecUtils.h"

MeiIe::MeiIe() 
{
    ieType = 75;
    // TODO

}

MeiIe::~MeiIe() {
    // TODO Auto-generated destructor stub
}

bool MeiIe::encodeMeiIe(MsgBuffer &buffer, MeiIeData const &data)
{
    if (!(data.imeiSvValue.length ==15 || data.imeiSvValue.length == 16))
    {
        errorStream.add("Data validation failure: imeiSvValue\n");
        return false; 
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.imeiSvValue)))
    {
    errorStream.add("Encoding of imeiSvValue failed\n");
    return false;
    }

    return true;
}

bool MeiIe::decodeMeiIe(MsgBuffer &buffer, MeiIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.imeiSvValue, lengthLeft)))
    {
        errorStream.add("Failed to decode: imeiSvValue\n");
        return false;
    }
    if (!(data.imeiSvValue.length ==15 || data.imeiSvValue.length == 16))
    {
        errorStream.add("Data validation failure : imeiSvValue\n");
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
        errorStream.add("Unable to decode IE MeiIe\n");
        return false;
    }
}
void MeiIe::displayMeiIe_v(MeiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("MeiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("imeiSvValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.imeiSvValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
