/*
 * deleteSessionRequestMsg.h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef DELETESESSIONREQUESTMSG_H_
#define DELETESESSIONREQUESTMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class DeleteSessionRequestMsg:public GtpV2Message
{
public:
    DeleteSessionRequestMsg();
    virtual ~DeleteSessionRequestMsg();
    bool encodeDeleteSessionRequestMsg(MsgBuffer &buffer, DeleteSessionRequestMsgData const &data);

    bool decodeDeleteSessionRequestMsg (MsgBuffer &buffer, DeleteSessionRequestMsgData& data, Uint16 length);

    void displayDeleteSessionRequestMsgData_v(DeleteSessionRequestMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif