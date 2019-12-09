/*
* Copyright (c) 2019 Infosys Limited
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

#include "remoteUeContextIe.h"
#include "gtpV2GrpIeDataTypes.h"
#include "manual/gtpV2GroupedIe.h"

#include "remoteUeContextConnectedInCreateSessionRequest.h"

RemoteUeContextIe::RemoteUeContextIe()
{
    ieType = RemoteUeContextIeType;
   
    RemoteUeContextConnectedInCreateSessionRequest* remoteUeContextConnectedInCreateSessionRequest_p = new (RemoteUeContextConnectedInCreateSessionRequest);
    insertGroupedIeObject(CreateSessionRequestMsgType, 0, remoteUeContextConnectedInCreateSessionRequest_p);
}

RemoteUeContextIe::~RemoteUeContextIe() {
// TODO Auto-generated destructor stub
}

GtpV2GroupedIe& RemoteUeContextIe::getGroupedIe(Uint8 msgType, Uint8 instance)
{
    std::map<Uint16, GtpV2GroupedIe*>::iterator it;
    Uint16 key = msgType;
    key = (key << 8) + instance;
    it = groupedIeObjectContainer.find(key);
    return *(it->second);
}

void RemoteUeContextIe::insertGroupedIeObject(Uint8 msgType, Uint8 instance, GtpV2GroupedIe* grpIe_p)
{

    Uint16 key = msgType;
    key = (key << 8) + instance;

    groupedIeObjectContainer.insert(std::pair<Uint16, GtpV2GroupedIe*>(key, grpIe_p));

}  