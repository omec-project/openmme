/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include "gtpV2MsgFactory.h"
#include "createSessionRequestMsg.h"
#include "createSessionResponseMsg.h"
#include "modifyBearerRequestMsg.h"
#include "modifyBearerResponseMsg.h"
#include "deleteSessionRequestMsg.h"
#include "deleteSessionResponseMsg.h"
#include "releaseAccessBearersRequestMsg.h"
#include "releaseAccessBearersResponseMsg.h"
#include "createBearerRequestMsg.h"
#include "createBearerResponseMsg.h"
#include "deleteBearerRequestMsg.h"
#include "deleteBearerResponseMsg.h"
#include "downlinkDataNotificationMsg.h"
#include "downlinkDataNotificationAcknowledgeMsg.h"
#include "downlinkDataNotificationFailureIndicationMsg.h"

static GtpV2MsgFactory gtpV2MsgFactory;

GtpV2MsgFactory::GtpV2MsgFactory() 
{
    //Create Message Objects
        
    CreateSessionRequestMsg* createSessionRequestMsg_p = new (CreateSessionRequestMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(CreateSessionRequestMsgType, createSessionRequestMsg_p));

    CreateSessionResponseMsg* createSessionResponseMsg_p = new (CreateSessionResponseMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(CreateSessionResponseMsgType, createSessionResponseMsg_p));

    ModifyBearerRequestMsg* modifyBearerRequestMsg_p = new (ModifyBearerRequestMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(ModifyBearerRequestMsgType, modifyBearerRequestMsg_p));

    ModifyBearerResponseMsg* modifyBearerResponseMsg_p = new (ModifyBearerResponseMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(ModifyBearerResponseMsgType, modifyBearerResponseMsg_p));

    DeleteSessionRequestMsg* deleteSessionRequestMsg_p = new (DeleteSessionRequestMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(DeleteSessionRequestMsgType, deleteSessionRequestMsg_p));

    DeleteSessionResponseMsg* deleteSessionResponseMsg_p = new (DeleteSessionResponseMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(DeleteSessionResponseMsgType, deleteSessionResponseMsg_p));

    ReleaseAccessBearersRequestMsg* releaseAccessBearersRequestMsg_p = new (ReleaseAccessBearersRequestMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(ReleaseAccessBearersRequestMsgType, releaseAccessBearersRequestMsg_p));

    ReleaseAccessBearersResponseMsg* releaseAccessBearersResponseMsg_p = new (ReleaseAccessBearersResponseMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(ReleaseAccessBearersResponseMsgType, releaseAccessBearersResponseMsg_p));

    CreateBearerRequestMsg* createBearerRequestMsg_p = new (CreateBearerRequestMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(CreateBearerRequestMsgType, createBearerRequestMsg_p));

    CreateBearerResponseMsg* createBearerResponseMsg_p = new (CreateBearerResponseMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(CreateBearerResponseMsgType, createBearerResponseMsg_p));

    DeleteBearerRequestMsg* deleteBearerRequestMsg_p = new (DeleteBearerRequestMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(DeleteBearerRequestMsgType, deleteBearerRequestMsg_p));

    DeleteBearerResponseMsg* deleteBearerResponseMsg_p = new (DeleteBearerResponseMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(DeleteBearerResponseMsgType, deleteBearerResponseMsg_p));

    DownlinkDataNotificationMsg* downlinkDataNotificationMsg_p = new (DownlinkDataNotificationMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(DownlinkDataNotificationMsgType, downlinkDataNotificationMsg_p));

    DownlinkDataNotificationAcknowledgeMsg* downlinkDataNotificationAcknowledgeMsg_p = new (DownlinkDataNotificationAcknowledgeMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(DownlinkDataNotificationAcknowledgeMsgType, downlinkDataNotificationAcknowledgeMsg_p));

    DownlinkDataNotificationFailureIndicationMsg* downlinkDataNotificationFailureIndicationMsg_p = new (DownlinkDataNotificationFailureIndicationMsg);
    msgObjectContainer.insert(std::pair<Uint8, GtpV2Message*>(DownlinkDataNotificationFailureIndicationMsgType, downlinkDataNotificationFailureIndicationMsg_p));


}

GtpV2MsgFactory::~GtpV2MsgFactory() {
    // TODO clean up the allocated memory for message objects
}

GtpV2MsgFactory& GtpV2MsgFactory::getInstance()
{
    static GtpV2MsgFactory gtpV2MsgFactory;
    return gtpV2MsgFactory;
}

GtpV2Message& GtpV2MsgFactory::getMsgObject(Uint8 msgType)
{
    std::map<Uint8, GtpV2Message*>::iterator it;
    it = msgObjectContainer.find(msgType);
    return *(it->second);
}
