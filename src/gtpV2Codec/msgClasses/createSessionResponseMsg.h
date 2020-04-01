/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 
#ifndef CREATESESSIONRESPONSEMSG_H_
#define CREATESESSIONRESPONSEMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class CreateSessionResponseMsg:public GtpV2Message
{
public:
    CreateSessionResponseMsg();
    virtual ~CreateSessionResponseMsg();
    bool encodeCreateSessionResponseMsg(MsgBuffer &buffer, CreateSessionResponseMsgData const &data);

    bool decodeCreateSessionResponseMsg (MsgBuffer &buffer, CreateSessionResponseMsgData& data, Uint16 length);

    void displayCreateSessionResponseMsgData_v(CreateSessionResponseMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif