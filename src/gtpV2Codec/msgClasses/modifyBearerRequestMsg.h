/*
 * modifyBearerRequestMsg.h
 *
 * Revisit header later
 *      Author: hariharanb
 */
#ifndef MODIFYBEARERREQUESTMSG_H_
#define MODIFYBEARERREQUESTMSG_H_

#include <set>
#include "manual/gtpV2Message.h"
#include <msgBuffer.h>
#include <debug.h>
#include "gtpV2MsgDataTypes.h"


class ModifyBearerRequestMsg:public GtpV2Message
{
public:
    ModifyBearerRequestMsg();
    virtual ~ModifyBearerRequestMsg();
    bool encodeModifyBearerRequestMsg(MsgBuffer &buffer, ModifyBearerRequestMsgData const &data);

    bool decodeModifyBearerRequestMsg (MsgBuffer &buffer, ModifyBearerRequestMsgData& data, Uint16 length);

    void displayModifyBearerRequestMsgData_v(ModifyBearerRequestMsgData const &data, Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif