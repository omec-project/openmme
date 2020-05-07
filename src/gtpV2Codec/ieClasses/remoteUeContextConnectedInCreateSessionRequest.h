/*
 * .h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef REMOTEUECONTEXTCONNECTEDINCREATESESSIONREQUEST_H_
#define REMOTEUECONTEXTCONNECTEDINCREATESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class RemoteUeContextConnectedInCreateSessionRequest:public GtpV2GroupedIe
{
public:
    RemoteUeContextConnectedInCreateSessionRequest();
    virtual ~RemoteUeContextConnectedInCreateSessionRequest();
    bool encodeRemoteUeContextConnectedInCreateSessionRequest(MsgBuffer &buffer,
                             RemoteUeContextConnectedInCreateSessionRequestData
                              const &data);

    bool decodeRemoteUeContextConnectedInCreateSessionRequest (MsgBuffer &buffer,
                             RemoteUeContextConnectedInCreateSessionRequestData 
                             & data, Uint16 length);

    void displayRemoteUeContextConnectedInCreateSessionRequestData_v
    (RemoteUeContextConnectedInCreateSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif