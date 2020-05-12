/*
 * ptiIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "ptiIe.h"
#include "dataTypeCodecUtils.h"

PtiIe::PtiIe() 
{
    ieType = 100;
    // TODO

}

PtiIe::~PtiIe() {
    // TODO Auto-generated destructor stub
}

bool PtiIe::encodePtiIe(MsgBuffer &buffer, PtiIeData const &data)
{
    if (!(buffer.writeUint8(data.procedureTransactionId)))
    {
        errorStream.add("Encoding of procedureTransactionId failed\n");
        return false;
    }

    return true;
}

bool PtiIe::decodePtiIe(MsgBuffer &buffer, PtiIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.procedureTransactionId);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: procedureTransactionId\n");
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
        errorStream.add("Unable to decode IE PtiIe\n");
        return false;
    }
}
void PtiIe::displayPtiIe_v(PtiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("PtiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("procedureTransactionId: ");
    stream.add(data.procedureTransactionId);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
