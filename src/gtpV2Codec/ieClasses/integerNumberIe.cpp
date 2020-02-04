/*
 * integerNumberIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "integerNumberIe.h"
#include "dataTypeCodecUtils.h"

IntegerNumberIe::IntegerNumberIe() 
{
    ieType = 187;
    // TODO

}

IntegerNumberIe::~IntegerNumberIe() {
    // TODO Auto-generated destructor stub
}

bool IntegerNumberIe::encodeIntegerNumberIe(MsgBuffer &buffer, IntegerNumberIeData const &data)
{
    if (!(buffer.writeUint64(data.integerNumberValue)))
    {
        errorStream.add("Encoding of integerNumberValue failed\n");
        return false;
    }

    return true;
}

bool IntegerNumberIe::decodeIntegerNumberIe(MsgBuffer &buffer, IntegerNumberIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint64(data.integerNumberValue);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: integerNumberValue\n");
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
        errorStream.add("Unable to decode IE IntegerNumberIe\n");
        return false;
    }
}
void IntegerNumberIe::displayIntegerNumberIe_v(IntegerNumberIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("IntegerNumberIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("integerNumberValue: ");
    stream.add(data.integerNumberValue);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
