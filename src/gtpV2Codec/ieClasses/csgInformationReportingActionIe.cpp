/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "csgInformationReportingActionIe.h"
#include "dataTypeCodecUtils.h"

CsgInformationReportingActionIe::CsgInformationReportingActionIe() 
{
    ieType = 146;
    // TODO

}

CsgInformationReportingActionIe::~CsgInformationReportingActionIe() {
    // TODO Auto-generated destructor stub
}

bool CsgInformationReportingActionIe::encodeCsgInformationReportingActionIe(MsgBuffer &buffer, CsgInformationReportingActionIeData const &data)
{
    buffer.skipBits(5);

    if(!(buffer.writeBits(data.uciuhc, 1)))
    {
        errorStream.add((char *)"Encoding of uciuhc failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.ucishc, 1)))
    {
        errorStream.add((char *)"Encoding of ucishc failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.ucicsg, 1)))
    {
        errorStream.add((char *)"Encoding of ucicsg failed\n");
        return false;
    }

    return true;
}

bool CsgInformationReportingActionIe::decodeCsgInformationReportingActionIe(MsgBuffer &buffer, CsgInformationReportingActionIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(5);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.uciuhc = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: uciuhc\n");
        return false;
    }
    data.ucishc = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: ucishc\n");
        return false;
    }
    data.ucicsg = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: ucicsg\n");
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
        errorStream.add((char *)"Unable to decode IE CsgInformationReportingActionIe\n");
        return false;
    }
}
void CsgInformationReportingActionIe::displayCsgInformationReportingActionIe_v(CsgInformationReportingActionIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"CsgInformationReportingActionIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"uciuhc: "); 
    stream.add((Uint8)data.uciuhc);
    stream.endOfLine();
  
    stream.add( (char *)"ucishc: "); 
    stream.add((Uint8)data.ucishc);
    stream.endOfLine();
  
    stream.add( (char *)"ucicsg: "); 
    stream.add((Uint8)data.ucicsg);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
