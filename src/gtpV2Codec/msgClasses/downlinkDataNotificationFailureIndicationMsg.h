/*
 * downlinkDataNotificationFailureIndicationMsg.h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef DOWNLINKDATANOTIFICATIONFAILUREINDICATIONMSG_H_
#define DOWNLINKDATANOTIFICATIONFAILUREINDICATIONMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class DownlinkDataNotificationFailureIndicationMsg:public GtpV2Message
{
public:
    DownlinkDataNotificationFailureIndicationMsg();
    virtual ~DownlinkDataNotificationFailureIndicationMsg();
    bool encodeDownlinkDataNotificationFailureIndicationMsg(MsgBuffer &buffer, DownlinkDataNotificationFailureIndicationMsgData const &data);

    bool decodeDownlinkDataNotificationFailureIndicationMsg (MsgBuffer &buffer, DownlinkDataNotificationFailureIndicationMsgData& data, Uint16 length);

    void displayDownlinkDataNotificationFailureIndicationMsgData_v(DownlinkDataNotificationFailureIndicationMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif