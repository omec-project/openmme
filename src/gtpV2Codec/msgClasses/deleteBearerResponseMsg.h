/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 
#ifndef DELETEBEARERRESPONSEMSG_H_
#define DELETEBEARERRESPONSEMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class DeleteBearerResponseMsg:public GtpV2Message
{
public:
    DeleteBearerResponseMsg();
    virtual ~DeleteBearerResponseMsg();
    bool encodeDeleteBearerResponseMsg(MsgBuffer &buffer, DeleteBearerResponseMsgData const &data);

    bool decodeDeleteBearerResponseMsg (MsgBuffer &buffer, DeleteBearerResponseMsgData& data, Uint16 length);

    void displayDeleteBearerResponseMsgData_v(DeleteBearerResponseMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif