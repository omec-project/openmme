/*
 * uciIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "uciIe.h"
#include "dataTypeCodecUtils.h"

UciIe::UciIe() 
{
    ieType = 145;
    // TODO

}

UciIe::~UciIe() {
    // TODO Auto-generated destructor stub
}

bool UciIe::encodeUciIe(MsgBuffer &buffer, UciIeData const &data)
{
    if(!(buffer.writeBits(data.mccDigit2, 4)))
    {
        errorStream.add("Encoding of mccDigit2 failed\n");
        return false;
    }
    buffer.skipBits(4);

    if(!(buffer.writeBits(data.mccDigit1, 4)))
    {
        errorStream.add("Encoding of mccDigit1 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit3, 4)))
    {
        errorStream.add("Encoding of mncDigit3 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mccDigit3, 4)))
    {
        errorStream.add("Encoding of mccDigit3 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit2, 4)))
    {
        errorStream.add("Encoding of mncDigit2 failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.mncDigit1, 4)))
    {
        errorStream.add("Encoding of mncDigit1 failed\n");
        return false;
    }
    if (!(data.csgId<= 0x07FFFFFF))
    {
        errorStream.add("Data validation failure: csgId\n");
        return false; 
    }
    if (!(buffer.writeUint32(data.csgId)))
    {
        errorStream.add("Encoding of csgId failed\n");
        return false;
    }
    if (!(data.accessMode<= 1))
    {
        errorStream.add("Data validation failure: accessMode\n");
        return false; 
    }
    if(!(buffer.writeBits(data.accessMode, 2)))
    {
        errorStream.add("Encoding of accessMode failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.lcsg, 1)))
    {
        errorStream.add("Encoding of lcsg failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.cmi, 1)))
    {
        errorStream.add("Encoding of cmi failed\n");
        return false;
    }

    return true;
}

bool UciIe::decodeUciIe(MsgBuffer &buffer, UciIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.mccDigit2 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mccDigit2\n");
        return false;
    }
    buffer.skipBits(4);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.mccDigit1 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mccDigit1\n");
        return false;
    }
    data.mncDigit3 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mncDigit3\n");
        return false;
    }
    data.mccDigit3 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mccDigit3\n");
        return false;
    }
    data.mncDigit2 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mncDigit2\n");
        return false;
    }
    data.mncDigit1 = buffer.readBits(4);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: mncDigit1\n");
        return false;
    }

    buffer.readUint32(data.csgId);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: csgId\n");
        return false;
    }
    if (!(data.csgId<= 0x07FFFFFF))
    {
        errorStream.add("Data validation failure : csgId\n");
        return false; //TODO need to add validations
    }
    data.accessMode = buffer.readBits(2);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: accessMode\n");
        return false;
    }
    if (!(data.accessMode<= 1))
    {
        errorStream.add("Data validation failure : accessMode\n");
        return false; //TODO need to add validations
    }
    data.lcsg = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: lcsg\n");
        return false;
    }
    data.cmi = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add("Attempt to read beyond IE boundary: cmi\n");
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
        errorStream.add("Unable to decode IE UciIe\n");
        return false;
    }
}
void UciIe::displayUciIe_v(UciIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add("UciIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( "mccDigit2: "); 
    stream.add((Uint8)data.mccDigit2);
    stream.endOfLine();
  
    stream.add( "mccDigit1: "); 
    stream.add((Uint8)data.mccDigit1);
    stream.endOfLine();
  
    stream.add( "mncDigit3: "); 
    stream.add((Uint8)data.mncDigit3);
    stream.endOfLine();
  
    stream.add( "mccDigit3: "); 
    stream.add((Uint8)data.mccDigit3);
    stream.endOfLine();
  
    stream.add( "mncDigit2: "); 
    stream.add((Uint8)data.mncDigit2);
    stream.endOfLine();
  
    stream.add( "mncDigit1: "); 
    stream.add((Uint8)data.mncDigit1);
    stream.endOfLine();
  
    stream.add("csgId: ");
    stream.add(data.csgId);
    stream.endOfLine();
  
    stream.add( "accessMode: "); 
    stream.add((Uint8)data.accessMode);
    stream.endOfLine();
  
    stream.add( "lcsg: "); 
    stream.add((Uint8)data.lcsg);
    stream.endOfLine();
  
    stream.add( "cmi: "); 
    stream.add((Uint8)data.cmi);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
