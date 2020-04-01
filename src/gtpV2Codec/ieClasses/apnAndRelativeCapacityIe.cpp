/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "apnAndRelativeCapacityIe.h"
#include "dataTypeCodecUtils.h"

ApnAndRelativeCapacityIe::ApnAndRelativeCapacityIe() 
{
    ieType = 184;
    // TODO

}

ApnAndRelativeCapacityIe::~ApnAndRelativeCapacityIe() {
    // TODO Auto-generated destructor stub
}

bool ApnAndRelativeCapacityIe::encodeApnAndRelativeCapacityIe(MsgBuffer &buffer, ApnAndRelativeCapacityIeData const &data)
{
    if (!(data.relativeCapacity>= 1 && data.relativeCapacity<= 100))
    {
        errorStream.add((char *)"Data validation failure: relativeCapacity\n");
        return false; 
    }
    if (!(buffer.writeUint8(data.relativeCapacity)))
    {
        errorStream.add((char *)"Encoding of relativeCapacity failed\n");
        return false;
    }
    if (!(buffer.writeUint8(data.apnLength)))
    {
        errorStream.add((char *)"Encoding of apnLength failed\n");
        return false;
    }
    if (!(DataTypeCodecUtils::encodeUint8Array32(buffer, data.apn)))
    {
    errorStream.add((char *)"Encoding of apn failed\n");
    return false;
    }

    return true;
}

bool ApnAndRelativeCapacityIe::decodeApnAndRelativeCapacityIe(MsgBuffer &buffer, ApnAndRelativeCapacityIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.relativeCapacity);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: relativeCapacity\n");
        return false;
    }
    if (!(data.relativeCapacity>= 1 && data.relativeCapacity<= 100))
    {
        errorStream.add((char *)"Data validation failure : relativeCapacity\n");
        return false; //TODO need to add validations
    }

    buffer.readUint8(data.apnLength);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: apnLength\n");
        return false;
    }

    Uint16 lengthLeft = length;
    lengthLeft = ieBoundary - buffer.getCurrentIndex();
    if (!(DataTypeCodecUtils::decodeUint8Array32(buffer, data.apn, lengthLeft, 0)))
    {
        errorStream.add((char *)"Failed to decode: apn\n");
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
        errorStream.add((char *)"Unable to decode IE ApnAndRelativeCapacityIe\n");
        return false;
    }
}
void ApnAndRelativeCapacityIe::displayApnAndRelativeCapacityIe_v(ApnAndRelativeCapacityIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"ApnAndRelativeCapacityIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"relativeCapacity: ");
    stream.add(data.relativeCapacity);
    stream.endOfLine();
  
    stream.add((char *)"apnLength: ");
    stream.add(data.apnLength);
    stream.endOfLine();
  
    stream.add((char *)"apn:");
    stream.endOfLine();
    DataTypeCodecUtils::displayUint8Array32_v(data.apn, stream);
    stream.decrIndent();
    stream.decrIndent();
}
