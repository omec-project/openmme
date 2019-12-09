/*
 * Copyright (c) 2019, Infosys Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */ 


#include "indicationIe.h"
#include "dataTypeCodecUtils.h"

IndicationIe::IndicationIe() 
{
    ieType = 77;
    // TODO

}

IndicationIe::~IndicationIe() {
    // TODO Auto-generated destructor stub
}

bool IndicationIe::encodeIndicationIe(MsgBuffer &buffer, IndicationIeData const &data)
{
    if(!(buffer.writeBits(data.iDAF, 1)))
    {
        errorStream.add((char *)"Encoding of iDAF failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iDTF, 1)))
    {
        errorStream.add((char *)"Encoding of iDTF failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iHI, 1)))
    {
        errorStream.add((char *)"Encoding of iHI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iDFI, 1)))
    {
        errorStream.add((char *)"Encoding of iDFI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iOI, 1)))
    {
        errorStream.add((char *)"Encoding of iOI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iISRSI, 1)))
    {
        errorStream.add((char *)"Encoding of iISRSI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iISRAI, 1)))
    {
        errorStream.add((char *)"Encoding of iISRAI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iSGWCI, 1)))
    {
        errorStream.add((char *)"Encoding of iSGWCI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iSQCI, 1)))
    {
        errorStream.add((char *)"Encoding of iSQCI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iUIMSI, 1)))
    {
        errorStream.add((char *)"Encoding of iUIMSI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iCFSI, 1)))
    {
        errorStream.add((char *)"Encoding of iCFSI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iCRSI, 1)))
    {
        errorStream.add((char *)"Encoding of iCRSI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iP, 1)))
    {
        errorStream.add((char *)"Encoding of iP failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iPT, 1)))
    {
        errorStream.add((char *)"Encoding of iPT failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iSI, 1)))
    {
        errorStream.add((char *)"Encoding of iSI failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iMSV, 1)))
    {
        errorStream.add((char *)"Encoding of iMSV failed\n");
        return false;
    }
    buffer.skipBits(3);

    if(!(buffer.writeBits(data.iS6AF, 1)))
    {
        errorStream.add((char *)"Encoding of iS6AF failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iS4AF, 1)))
    {
        errorStream.add((char *)"Encoding of iS4AF failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iMBMDT, 1)))
    {
        errorStream.add((char *)"Encoding of iMBMDT failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iISRAU, 1)))
    {
        errorStream.add((char *)"Encoding of iISRAU failed\n");
        return false;
    }
    if(!(buffer.writeBits(data.iCCRSI, 1)))
    {
        errorStream.add((char *)"Encoding of iCCRSI failed\n");
        return false;
    }

    return true;
}

bool IndicationIe::decodeIndicationIe(MsgBuffer &buffer, IndicationIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;
    data.iDAF = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iDAF\n");
        return false;
    }
    data.iDTF = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iDTF\n");
        return false;
    }
    data.iHI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iHI\n");
        return false;
    }
    data.iDFI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iDFI\n");
        return false;
    }
    data.iOI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iOI\n");
        return false;
    }
    data.iISRSI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iISRSI\n");
        return false;
    }
    data.iISRAI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iISRAI\n");
        return false;
    }
    data.iSGWCI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iSGWCI\n");
        return false;
    }
    data.iSQCI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iSQCI\n");
        return false;
    }
    data.iUIMSI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iUIMSI\n");
        return false;
    }
    data.iCFSI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iCFSI\n");
        return false;
    }
    data.iCRSI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iCRSI\n");
        return false;
    }
    data.iP = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iP\n");
        return false;
    }
    data.iPT = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iPT\n");
        return false;
    }
    data.iSI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iSI\n");
        return false;
    }
    data.iMSV = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iMSV\n");
        return false;
    }
    buffer.skipBits(3);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: \n");
        return false;
    }

    data.iS6AF = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iS6AF\n");
        return false;
    }
    data.iS4AF = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iS4AF\n");
        return false;
    }
    data.iMBMDT = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iMBMDT\n");
        return false;
    }
    data.iISRAU = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iISRAU\n");
        return false;
    }
    data.iCCRSI = buffer.readBits(1);
    // confirm that we are not reading beyond the IE boundary
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: iCCRSI\n");
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
        errorStream.add((char *)"Unable to decode IE IndicationIe\n");
        return false;
    }
}
void IndicationIe::displayIndicationIe_v(IndicationIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"IndicationIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add( (char *)"iDAF: "); 
    stream.add((Uint8)data.iDAF);
    stream.endOfLine();
  
    stream.add( (char *)"iDTF: "); 
    stream.add((Uint8)data.iDTF);
    stream.endOfLine();
  
    stream.add( (char *)"iHI: "); 
    stream.add((Uint8)data.iHI);
    stream.endOfLine();
  
    stream.add( (char *)"iDFI: "); 
    stream.add((Uint8)data.iDFI);
    stream.endOfLine();
  
    stream.add( (char *)"iOI: "); 
    stream.add((Uint8)data.iOI);
    stream.endOfLine();
  
    stream.add( (char *)"iISRSI: "); 
    stream.add((Uint8)data.iISRSI);
    stream.endOfLine();
  
    stream.add( (char *)"iISRAI: "); 
    stream.add((Uint8)data.iISRAI);
    stream.endOfLine();
  
    stream.add( (char *)"iSGWCI: "); 
    stream.add((Uint8)data.iSGWCI);
    stream.endOfLine();
  
    stream.add( (char *)"iSQCI: "); 
    stream.add((Uint8)data.iSQCI);
    stream.endOfLine();
  
    stream.add( (char *)"iUIMSI: "); 
    stream.add((Uint8)data.iUIMSI);
    stream.endOfLine();
  
    stream.add( (char *)"iCFSI: "); 
    stream.add((Uint8)data.iCFSI);
    stream.endOfLine();
  
    stream.add( (char *)"iCRSI: "); 
    stream.add((Uint8)data.iCRSI);
    stream.endOfLine();
  
    stream.add( (char *)"iP: "); 
    stream.add((Uint8)data.iP);
    stream.endOfLine();
  
    stream.add( (char *)"iPT: "); 
    stream.add((Uint8)data.iPT);
    stream.endOfLine();
  
    stream.add( (char *)"iSI: "); 
    stream.add((Uint8)data.iSI);
    stream.endOfLine();
  
    stream.add( (char *)"iMSV: "); 
    stream.add((Uint8)data.iMSV);
    stream.endOfLine();
  
    stream.add( (char *)"iS6AF: "); 
    stream.add((Uint8)data.iS6AF);
    stream.endOfLine();
  
    stream.add( (char *)"iS4AF: "); 
    stream.add((Uint8)data.iS4AF);
    stream.endOfLine();
  
    stream.add( (char *)"iMBMDT: "); 
    stream.add((Uint8)data.iMBMDT);
    stream.endOfLine();
  
    stream.add( (char *)"iISRAU: "); 
    stream.add((Uint8)data.iISRAU);
    stream.endOfLine();
  
    stream.add( (char *)"iCCRSI: "); 
    stream.add((Uint8)data.iCCRSI);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
