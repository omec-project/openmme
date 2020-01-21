/*
 * downlinkDataNotificationMsg.h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef DOWNLINKDATANOTIFICATIONMSG_H_
#define DOWNLINKDATANOTIFICATIONMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class DownlinkDataNotificationMsg:public GtpV2Message
{
public:
    DownlinkDataNotificationMsg();
    virtual ~DownlinkDataNotificationMsg();
    bool encodeDownlinkDataNotificationMsg(MsgBuffer &buffer, DownlinkDataNotificationMsgData const &data);

    bool decodeDownlinkDataNotificationMsg (MsgBuffer &buffer, DownlinkDataNotificationMsgData& data, Uint16 length);

    void displayDownlinkDataNotificationMsgData_v(DownlinkDataNotificationMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif