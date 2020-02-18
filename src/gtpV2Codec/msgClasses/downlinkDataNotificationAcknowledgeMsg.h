/*
 * downlinkDataNotificationAcknowledgeMsg.h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef DOWNLINKDATANOTIFICATIONACKNOWLEDGEMSG_H_
#define DOWNLINKDATANOTIFICATIONACKNOWLEDGEMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class DownlinkDataNotificationAcknowledgeMsg:public GtpV2Message
{
public:
    DownlinkDataNotificationAcknowledgeMsg();
    virtual ~DownlinkDataNotificationAcknowledgeMsg();
    bool encodeDownlinkDataNotificationAcknowledgeMsg(MsgBuffer &buffer, DownlinkDataNotificationAcknowledgeMsgData const &data);

    bool decodeDownlinkDataNotificationAcknowledgeMsg (MsgBuffer &buffer, DownlinkDataNotificationAcknowledgeMsgData& data, Uint16 length);

    void displayDownlinkDataNotificationAcknowledgeMsgData_v(DownlinkDataNotificationAcknowledgeMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif