/*
 * createSessionRequestMsg.h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef CREATESESSIONREQUESTMSG_H_
#define CREATESESSIONREQUESTMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class CreateSessionRequestMsg:public GtpV2Message
{
public:
    CreateSessionRequestMsg();
    virtual ~CreateSessionRequestMsg();
    bool encodeCreateSessionRequestMsg(MsgBuffer &buffer, CreateSessionRequestMsgData const &data);

    bool decodeCreateSessionRequestMsg (MsgBuffer &buffer, CreateSessionRequestMsgData& data, Uint16 length);

    void displayCreateSessionRequestMsgData_v(CreateSessionRequestMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif