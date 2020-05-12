/*
 * releaseAccessBearersResponseMsg.h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef RELEASEACCESSBEARERSRESPONSEMSG_H_
#define RELEASEACCESSBEARERSRESPONSEMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class ReleaseAccessBearersResponseMsg:public GtpV2Message
{
public:
    ReleaseAccessBearersResponseMsg();
    virtual ~ReleaseAccessBearersResponseMsg();
    bool encodeReleaseAccessBearersResponseMsg(MsgBuffer &buffer, ReleaseAccessBearersResponseMsgData const &data);

    bool decodeReleaseAccessBearersResponseMsg (MsgBuffer &buffer, ReleaseAccessBearersResponseMsgData& data, Uint16 length);

    void displayReleaseAccessBearersResponseMsgData_v(ReleaseAccessBearersResponseMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif