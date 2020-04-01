/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "metricIe.h"
#include "dataTypeCodecUtils.h"

MetricIe::MetricIe() 
{
    ieType = 182;
    // TODO

}

MetricIe::~MetricIe() {
    // TODO Auto-generated destructor stub
}

bool MetricIe::encodeMetricIe(MsgBuffer &buffer, MetricIeData const &data)
{
    if (!(buffer.writeUint8(data.metric)))
    {
        errorStream.add((char *)"Encoding of metric failed\n");
        return false;
    }

    return true;
}

bool MetricIe::decodeMetricIe(MsgBuffer &buffer, MetricIeData &data, Uint16 length)
{     
    // TODO optimize the length checks
    
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint8(data.metric);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: metric\n");
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
        errorStream.add((char *)"Unable to decode IE MetricIe\n");
        return false;
    }
}
void MetricIe::displayMetricIe_v(MetricIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"MetricIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"metric: ");
    stream.add(data.metric);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
