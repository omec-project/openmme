/*
 * recoveryIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "recoveryIe.h"
#include "dataTypeCodecUtils.h"

RecoveryIe::RecoveryIe() 
{
    ieType = 3;
    // TODO

}

RecoveryIe::~RecoveryIe() {
    // TODO Auto-generated destructor stub
}

bool RecoveryIe::encodeRecoveryIe(MsgBuffer &buffer, RecoveryIeData const &data)
{
    if (!(buffer.writeUint8(data.restartCounter)))
    {
        errorStream.add("Encoding of restartCounter failed\n");
        return false;
    }

    return true;
}

bool RecoveryIe::decodeRecoveryIe(MsgBuffer &buffer, RecoveryIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.restartCounter);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: restartCounter\n");
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
        errorStream.add("Unable to decode IE RecoveryIe\n");
        return false;
    }
}
void RecoveryIe::displayRecoveryIe_v(RecoveryIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("RecoveryIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("restartCounter: ");
    stream.add(data.restartCounter);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
