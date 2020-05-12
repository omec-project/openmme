/*
 * deleteSessionResponseMsg.h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef DELETESESSIONRESPONSEMSG_H_
#define DELETESESSIONRESPONSEMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class DeleteSessionResponseMsg:public GtpV2Message
{
public:
    DeleteSessionResponseMsg();
    virtual ~DeleteSessionResponseMsg();
    bool encodeDeleteSessionResponseMsg(MsgBuffer &buffer, DeleteSessionResponseMsgData const &data);

    bool decodeDeleteSessionResponseMsg (MsgBuffer &buffer, DeleteSessionResponseMsgData& data, Uint16 length);

    void displayDeleteSessionResponseMsgData_v(DeleteSessionResponseMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif