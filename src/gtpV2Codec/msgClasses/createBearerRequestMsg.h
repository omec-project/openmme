/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 
#ifndef CREATEBEARERREQUESTMSG_H_
#define CREATEBEARERREQUESTMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class CreateBearerRequestMsg:public GtpV2Message
{
public:
    CreateBearerRequestMsg();
    virtual ~CreateBearerRequestMsg();
    bool encodeCreateBearerRequestMsg(MsgBuffer &buffer, CreateBearerRequestMsgData const &data);

    bool decodeCreateBearerRequestMsg (MsgBuffer &buffer, CreateBearerRequestMsgData& data, Uint16 length);

    void displayCreateBearerRequestMsgData_v(CreateBearerRequestMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif