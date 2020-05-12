/*
 * imsiIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "imsiIe.h"
#include "dataTypeCodecUtils.h"

ImsiIe::ImsiIe() 
{
    ieType = 1;
    // TODO

}

ImsiIe::~ImsiIe() {
    // TODO Auto-generated destructor stub
}

bool ImsiIe::encodeImsiIe(MsgBuffer &buffer, ImsiIeData const &data)
{
    if (!(data.imsiValue.length>=9 && data.imsiValue.length <=15))
    {
        errorStream.add("Data validation failure: imsiValue\n");
        return false; 
    }
    if (!(DataTypeCodecUtils::encodeDigitRegister(buffer, data.imsiValue)))
    {
    errorStream.add("Encoding of imsiValue failed\n");
    return false;
    }

    return true;
}

bool ImsiIe::decodeImsiIe(MsgBuffer &buffer, ImsiIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeDigitRegister(buffer, data.imsiValue, lengthLeft)))
    {
        errorStream.add("Failed to decode: imsiValue\n");
        return false;
    }
    if (!(data.imsiValue.length>=9 && data.imsiValue.length <=15))
    {
        errorStream.add("Data validation failure : imsiValue\n");
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
        errorStream.add("Unable to decode IE ImsiIe\n");
        return false;
    }
}
void ImsiIe::displayImsiIe_v(ImsiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("ImsiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("imsiValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayDigitRegister_v(data.imsiValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
