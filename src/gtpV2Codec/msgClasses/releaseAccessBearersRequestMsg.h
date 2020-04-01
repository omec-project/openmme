/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 
#ifndef RELEASEACCESSBEARERSREQUESTMSG_H_
#define RELEASEACCESSBEARERSREQUESTMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class ReleaseAccessBearersRequestMsg:public GtpV2Message
{
public:
    ReleaseAccessBearersRequestMsg();
    virtual ~ReleaseAccessBearersRequestMsg();
    bool encodeReleaseAccessBearersRequestMsg(MsgBuffer &buffer, ReleaseAccessBearersRequestMsgData const &data);

    bool decodeReleaseAccessBearersRequestMsg (MsgBuffer &buffer, ReleaseAccessBearersRequestMsgData& data, Uint16 length);

    void displayReleaseAccessBearersRequestMsgData_v(ReleaseAccessBearersRequestMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif