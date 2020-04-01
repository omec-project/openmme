/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 
#ifndef MODIFYBEARERRESPONSEMSG_H_
#define MODIFYBEARERRESPONSEMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class ModifyBearerResponseMsg:public GtpV2Message
{
public:
    ModifyBearerResponseMsg();
    virtual ~ModifyBearerResponseMsg();
    bool encodeModifyBearerResponseMsg(MsgBuffer &buffer, ModifyBearerResponseMsgData const &data);

    bool decodeModifyBearerResponseMsg (MsgBuffer &buffer, ModifyBearerResponseMsgData& data, Uint16 length);

    void displayModifyBearerResponseMsgData_v(ModifyBearerResponseMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif