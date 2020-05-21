/*
 * remoteUeContextIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
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