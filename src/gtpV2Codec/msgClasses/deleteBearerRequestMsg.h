/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 
#ifndef DELETEBEARERREQUESTMSG_H_
#define DELETEBEARERREQUESTMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class DeleteBearerRequestMsg:public GtpV2Message
{
public:
    DeleteBearerRequestMsg();
    virtual ~DeleteBearerRequestMsg();
    bool encodeDeleteBearerRequestMsg(MsgBuffer &buffer, DeleteBearerRequestMsgData const &data);

    bool decodeDeleteBearerRequestMsg (MsgBuffer &buffer, DeleteBearerRequestMsgData& data, Uint16 length);

    void displayDeleteBearerRequestMsgData_v(DeleteBearerRequestMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif