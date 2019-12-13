/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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
        errorStream.add((char *)"Encoding of procedureTransactionId failed\n");
        return false;
    }

    return true;
}

bool PtiIe::decodePtiIe(MsgBuffer &buffer, PtiIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.procedureTransactionId);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: procedureTransactionId\n");
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
        errorStream.add((char *)"Unable to decode IE PtiIe\n");
        return false;
    }
}
void PtiIe::displayPtiIe_v(PtiIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"PtiIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"procedureTransactionId: ");
    stream.add(data.procedureTransactionId);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
