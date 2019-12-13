/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 
#ifndef CREATEBEARERRESPONSEMSG_H_
#define CREATEBEARERRESPONSEMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class CreateBearerResponseMsg:public GtpV2Message
{
public:
    CreateBearerResponseMsg();
    virtual ~CreateBearerResponseMsg();
    bool encodeCreateBearerResponseMsg(MsgBuffer &buffer, CreateBearerResponseMsgData const &data);

    bool decodeCreateBearerResponseMsg (MsgBuffer &buffer, CreateBearerResponseMsgData& data, Uint16 length);

    void displayCreateBearerResponseMsgData_v(CreateBearerResponseMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif