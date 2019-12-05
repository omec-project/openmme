/*
 * pagingAndServiceInformationIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "pagingAndServiceInformationIe.h"
#include "dataTypeCodecUtils.h"

PagingAndServiceInformationIe::PagingAndServiceInformationIe() 
{
    ieType = 186;
    // TODO

}

PagingAndServiceInformationIe::~PagingAndServiceInformationIe() {
    // TODO Auto-generated destructor stub
}

bool PagingAndServiceInformationIe::encodePagingAndServiceInformationIe(MsgBuffer &buffer, PagingAndServiceInformationIeData const &data)
{
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.epsBearerId, 4)))
    {
        errorStream.add("Encoding of epsBearerId failed\n");
        return false;
    }
    buffer.skipBits(7);

    buffer.skipBits(2);

    if(!(buffer.writeBits(data.ppi, 1)))
    {
        errorStream.add("Encoding of ppi failed\n");
        return false;
    }
    if (!(data.ppi==1))
    {
        errorStream.add("Data validation failure: ppi\n");
        return false; 
    }
    if(!(buffer.writeBits(data.ppi, 6)))
    {
        errorStream.add("Encoding of ppi failed\n");
        return false;
    }

    return true;
}

bool PagingAndServiceInformationIe::decodePagingAndServiceInformationIe(MsgBuffer &buffer, PagingAndServiceInformationIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    buffer.skipBits(4);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.epsBearerId = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: epsBearerId\n");
        return false;
    }
    buffer.skipBits(7);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    buffer.skipBits(2);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.ppi = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: ppi\n");
        return false;
    }
    data.ppi = buffer.readBits(6);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: ppi\n");
        return false;
    }
    if (!(data.ppi==1))
    {
        errorStream.add("Data validation failure : ppi\n");
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
        errorStream.add("Unable to decode IE PagingAndServiceInformationIe\n");
        return false;
    }
}
void PagingAndServiceInformationIe::displayPagingAndServiceInformationIe_v(PagingAndServiceInformationIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("PagingAndServiceInformationIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "epsBearerId: "); 
    stream.add((Uint8)data.epsBearerId);
    stream.endOfLine();
  
    stream.add( "ppi: "); 
    stream.add((Uint8)data.ppi);
    stream.endOfLine();
  
    stream.add( "ppi: "); 
    stream.add((Uint8)data.ppi);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
