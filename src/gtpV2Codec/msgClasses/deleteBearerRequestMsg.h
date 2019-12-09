/*
* Copyright (c) 2019 Infosys Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
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