/*
 * gtpV2Stack.h
 *
 *  Created on: Jul 11, 2014
 *      Author: hariharanb
 */

#ifndef GTPV2STACK_H_
#define GTPV2STACK_H_

#include <sstream>
#include <basicTypes.h>
#include <msgBuffer.h>
#include "msgClasses/gtpV2MsgDataTypes.h"

class GtpV2Stack {
public:
    GtpV2Stack();
    virtual ~GtpV2Stack();

    // Public datastructures that hold decoded data or data to be encoded
    CreateSessionRequestMsgData createSessionRequestStackData;
    CreateSessionResponseMsgData createSessionResponseStackData;
    ModifyBearerRequestMsgData modifyBearerRequestStackData;
    ModifyBearerResponseMsgData modifyBearerResponseStackData;
    DeleteSessionRequestMsgData deleteSessionRequestStackData;
    DeleteSessionResponseMsgData deleteSessionResponseStackData;
    ReleaseAccessBearersRequestMsgData releaseAccessBearersRequestStackData;
    ReleaseAccessBearersResponseMsgData releaseAccessBearersResponseStackData;
    CreateBearerRequestMsgData createBearerRequestStackData;
    CreateBearerResponseMsgData createBearerResponseStackData;
    DeleteBearerRequestMsgData deleteBearerRequestStackData;
    DeleteBearerResponseMsgData deleteBearerResponseStackData;
    DownlinkDataNotificationMsgData downlinkDataNotificationStackData;
    DownlinkDataNotificationAcknowledgeMsgData downlinkDataNotificationAcknowledgeStackData;
    DownlinkDataNotificationFailureIndicationMsgData downlinkDataNotificationFailureIndicationStackData;

    bool encodeMessage(GtpV2MessageHeader& msgHeader, MsgBuffer& buffer,
                 void* data_p = NULL);
    bool decodeGtpMessageHeader(GtpV2MessageHeader& msgHeader, MsgBuffer& buffer);
    bool decodeMessage(GtpV2MessageHeader& msgHeader, MsgBuffer& buffer,
                 void* data_p = NULL);
    void display_v(Uint8 msgType, Debug& stream, void* data_p = NULL);
};

#endif /* GTPV2STACK_H_ */
