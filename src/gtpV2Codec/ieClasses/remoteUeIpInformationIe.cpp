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


#include "remoteUeIpInformationIe.h"
#include "dataTypeCodecUtils.h"

RemoteUeIpInformationIe::RemoteUeIpInformationIe() 
{
    ieType = 193;
    // TODO

}

RemoteUeIpInformationIe::~RemoteUeIpInformationIe() {
    // TODO Auto-generated destructor stub
}

bool RemoteUeIpInformationIe::encodeRemoteUeIpInformationIe(MsgBuffer &buffer, RemoteUeIpInformationIeData const &data)
{
    if (!(buffer.writeUint64(data.remoteUeIpInformation)))
    {
        errorStream.add((char *)"Encoding of remoteUeIpInformation failed\n");
        return false;
    }

    return true;
}

bool RemoteUeIpInformationIe::decodeRemoteUeIpInformationIe(MsgBuffer &buffer, RemoteUeIpInformationIeData &data, Uint16 length)
{ 
    // TODO optimize the length checks
    Uint16 lengthLeft = length;
    Uint16 ieBoundary = buffer.getCurrentIndex() + length;

    buffer.readUint64(data.remoteUeIpInformation);
    if (buffer.getCurrentIndex() > ieBoundary)
    {
        errorStream.add((char *)"Attempt to read beyond IE boundary: remoteUeIpInformation\n");
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
        errorStream.add((char *)"Unable to decode IE RemoteUeIpInformationIe\n");
        return false;
    }
}
void RemoteUeIpInformationIe::displayRemoteUeIpInformationIe_v(RemoteUeIpInformationIeData const &data, Debug &stream)
{
    stream.incrIndent();
    stream.add((char *)"RemoteUeIpInformationIeData:");
    stream.incrIndent();
    stream.endOfLine();
  
    stream.add((char *)"remoteUeIpInformation: ");
    stream.add(data.remoteUeIpInformation);
    stream.endOfLine();
    stream.decrIndent();
    stream.decrIndent();
}
