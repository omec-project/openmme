/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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
    errorStream.add((char *)"Encoding of pcoValue failed\n");
    return false;
    }

    return true;
}

bool PcoIe::decodePcoIe(MsgBuffer &buffer, PcoIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
<<<<<<< HEAD
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    Uint16 lengthLeft = length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array255(buffer, data.pcoValue, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: pcoValue\n");
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
        errorStream.add((char *)"Unable to decode IE PcoIe\n");
        return false;
    }
=======
    if (!(DataTypeCodecUtils::decodeUint8Array512(buffer, data.pcoValue, length, 0)))
    {
        errorStream.add("Failed to decode: pcoValue\n");
	assert(0);
        return false;
    }
   return true;
>>>>>>> 729e1b7d2556e2873f92b7440d367a77f7e71d20
}
void PcoIe::displayPcoIe_v(PcoIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"PcoIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"pcoValue:");
    stream.endOfLine();
<<<<<<< HEAD
    DataTypeCodecUtils::displayUint8Array255_v(data.pcoValue, stream);
=======
    DataTypeCodecUtils::displayUint8Array512_v(data.pcoValue, stream);
>>>>>>> 729e1b7d2556e2873f92b7440d367a77f7e71d20
    stream.decrIndent();
    stream.decrIndent();
}
