/*
 * pcoIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "pcoIe.h"
#include "dataTypeCodecUtils.h"
#include "stdio.h"
#include "assert.h"

PcoIe::PcoIe() 
{
    ieType = 78;
    // TODO

}

PcoIe::~PcoIe() {
    // TODO Auto-generated destructor stub
}

bool PcoIe::encodePcoIe(MsgBuffer &buffer, PcoIeData const &data)
{
    if (!(DataTypeCodecUtils::encodeUint8Array512(buffer, data.pcoValue)))
    {
    errorStream.add("Encoding of pcoValue failed\n");
    return false;
    }

    return true;
}

bool PcoIe::decodePcoIe(MsgBuffer &buffer, PcoIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    if (!(DataTypeCodecUtils::decodeUint8Array512(buffer, data.pcoValue, length, 0)))
    {
        errorStream.add("Failed to decode: pcoValue\n");
	assert(0);
        return false;
    }
   return true;
}
void PcoIe::displayPcoIe_v(PcoIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("PcoIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add("pcoValue:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array512_v(data.pcoValue, stream);
    stream.decrIndent();
    stream.decrIndent();
}
