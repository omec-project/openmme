/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#include "loadControlInformationIe.h"
#include "gtpV2GrpIeDataTypes.h"
#include "manual/gtpV2GroupedIe.h"

#include "pgwsNodeLevelLoadControlInformationInCreateSessionResponse.h"
#include "pgwsApnLevelLoadControlInformationInCreateSessionResponse.h"
#include "sgwsNodeLevelLoadControlInformationInCreateSessionResponse.h"
#include "sgwsNodeLevelLoadControlInformationInModifyBearerResponse.h"
#include "pgwsApnLevelLoadControlInformationInModifyBearerResponse.h"
#include "pgwsNodeLevelLoadControlInformationInModifyBearerResponse.h"
#include "pgwsNodeLevelLoadControlInformationInDeleteSessionResponse.h"
#include "pgwsApnLevelLoadControlInformationInDeleteSessionResponse.h"
#include "sgwsNodeLevelLoadControlInformationInDeleteSessionResponse.h"
#include "sgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse.h"
#include "pgwsNodeLevelLoadControlInformationInCreateBearerRequest.h"
#include "pgwsApnLevelLoadControlInformationInCreateBearerRequest.h"
#include "sgwsNodeLevelLoadControlInformationInCreateBearerRequest.h"
#include "pgwsNodeLevelLoadControlInformationInDeleteBearerRequest.h"
#include "pgwsApnLevelLoadControlInformationInDeleteBearerRequest.h"
#include "sgwsNodeLevelLoadControlInformationInDeleteBearerRequest.h"
#include "sgwsNodeLevelLoadControlInformationInDownlinkDataNotification.h"

LoadControlInformationIe::LoadControlInformationIe()
{
    ieType = LoadControlInformationIeType;
   
    PgwsNodeLevelLoadControlInformationInCreateSessionResponse* pgwsNodeLevelLoadControlInformationInCreateSessionResponse_p = new (PgwsNodeLevelLoadControlInformationInCreateSessionResponse);
    insertGroupedIeObject(CreateSessionResponseMsgType, 0, pgwsNodeLevelLoadControlInformationInCreateSessionResponse_p);
    PgwsApnLevelLoadControlInformationInCreateSessionResponse* pgwsApnLevelLoadControlInformationInCreateSessionResponse_p = new (PgwsApnLevelLoadControlInformationInCreateSessionResponse);
    insertGroupedIeObject(CreateSessionResponseMsgType, 1, pgwsApnLevelLoadControlInformationInCreateSessionResponse_p);
    SgwsNodeLevelLoadControlInformationInCreateSessionResponse* sgwsNodeLevelLoadControlInformationInCreateSessionResponse_p = new (SgwsNodeLevelLoadControlInformationInCreateSessionResponse);
    insertGroupedIeObject(CreateSessionResponseMsgType, 2, sgwsNodeLevelLoadControlInformationInCreateSessionResponse_p);
    SgwsNodeLevelLoadControlInformationInModifyBearerResponse* sgwsNodeLevelLoadControlInformationInModifyBearerResponse_p = new (SgwsNodeLevelLoadControlInformationInModifyBearerResponse);
    insertGroupedIeObject(ModifyBearerResponseMsgType, 2, sgwsNodeLevelLoadControlInformationInModifyBearerResponse_p);
    PgwsApnLevelLoadControlInformationInModifyBearerResponse* pgwsApnLevelLoadControlInformationInModifyBearerResponse_p = new (PgwsApnLevelLoadControlInformationInModifyBearerResponse);
    insertGroupedIeObject(ModifyBearerResponseMsgType, 1, pgwsApnLevelLoadControlInformationInModifyBearerResponse_p);
    PgwsNodeLevelLoadControlInformationInModifyBearerResponse* pgwsNodeLevelLoadControlInformationInModifyBearerResponse_p = new (PgwsNodeLevelLoadControlInformationInModifyBearerResponse);
    insertGroupedIeObject(ModifyBearerResponseMsgType, 0, pgwsNodeLevelLoadControlInformationInModifyBearerResponse_p);
    PgwsNodeLevelLoadControlInformationInDeleteSessionResponse* pgwsNodeLevelLoadControlInformationInDeleteSessionResponse_p = new (PgwsNodeLevelLoadControlInformationInDeleteSessionResponse);
    insertGroupedIeObject(DeleteSessionResponseMsgType, 0, pgwsNodeLevelLoadControlInformationInDeleteSessionResponse_p);
    PgwsApnLevelLoadControlInformationInDeleteSessionResponse* pgwsApnLevelLoadControlInformationInDeleteSessionResponse_p = new (PgwsApnLevelLoadControlInformationInDeleteSessionResponse);
    insertGroupedIeObject(DeleteSessionResponseMsgType, 1, pgwsApnLevelLoadControlInformationInDeleteSessionResponse_p);
    SgwsNodeLevelLoadControlInformationInDeleteSessionResponse* sgwsNodeLevelLoadControlInformationInDeleteSessionResponse_p = new (SgwsNodeLevelLoadControlInformationInDeleteSessionResponse);
    insertGroupedIeObject(DeleteSessionResponseMsgType, 2, sgwsNodeLevelLoadControlInformationInDeleteSessionResponse_p);
    SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse* sgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse_p = new (SgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse);
    insertGroupedIeObject(ReleaseAccessBearersResponseMsgType, 0, sgwsNodeLevelLoadControlInformationInReleaseAccessBearersResponse_p);
    PgwsNodeLevelLoadControlInformationInCreateBearerRequest* pgwsNodeLevelLoadControlInformationInCreateBearerRequest_p = new (PgwsNodeLevelLoadControlInformationInCreateBearerRequest);
    insertGroupedIeObject(CreateBearerRequestMsgType, 0, pgwsNodeLevelLoadControlInformationInCreateBearerRequest_p);
    PgwsApnLevelLoadControlInformationInCreateBearerRequest* pgwsApnLevelLoadControlInformationInCreateBearerRequest_p = new (PgwsApnLevelLoadControlInformationInCreateBearerRequest);
    insertGroupedIeObject(CreateBearerRequestMsgType, 1, pgwsApnLevelLoadControlInformationInCreateBearerRequest_p);
    SgwsNodeLevelLoadControlInformationInCreateBearerRequest* sgwsNodeLevelLoadControlInformationInCreateBearerRequest_p = new (SgwsNodeLevelLoadControlInformationInCreateBearerRequest);
    insertGroupedIeObject(CreateBearerRequestMsgType, 2, sgwsNodeLevelLoadControlInformationInCreateBearerRequest_p);
    PgwsNodeLevelLoadControlInformationInDeleteBearerRequest* pgwsNodeLevelLoadControlInformationInDeleteBearerRequest_p = new (PgwsNodeLevelLoadControlInformationInDeleteBearerRequest);
    insertGroupedIeObject(DeleteBearerRequestMsgType, 0, pgwsNodeLevelLoadControlInformationInDeleteBearerRequest_p);
    PgwsApnLevelLoadControlInformationInDeleteBearerRequest* pgwsApnLevelLoadControlInformationInDeleteBearerRequest_p = new (PgwsApnLevelLoadControlInformationInDeleteBearerRequest);
    insertGroupedIeObject(DeleteBearerRequestMsgType, 1, pgwsApnLevelLoadControlInformationInDeleteBearerRequest_p);
    SgwsNodeLevelLoadControlInformationInDeleteBearerRequest* sgwsNodeLevelLoadControlInformationInDeleteBearerRequest_p = new (SgwsNodeLevelLoadControlInformationInDeleteBearerRequest);
    insertGroupedIeObject(DeleteBearerRequestMsgType, 2, sgwsNodeLevelLoadControlInformationInDeleteBearerRequest_p);
    SgwsNodeLevelLoadControlInformationInDownlinkDataNotification* sgwsNodeLevelLoadControlInformationInDownlinkDataNotification_p = new (SgwsNodeLevelLoadControlInformationInDownlinkDataNotification);
    insertGroupedIeObject(DownlinkDataNotificationMsgType, 0, sgwsNodeLevelLoadControlInformationInDownlinkDataNotification_p);
}

LoadControlInformationIe::~LoadControlInformationIe() {
// TODO Auto-generated destructor stub
}

GtpV2GroupedIe& LoadControlInformationIe::getGroupedIe(Uint8 msgType, Uint8 instance)
{
    std::map<Uint16, GtpV2GroupedIe*>::iterator it;
    Uint16 key = msgType;
    key = (key << 8) + instance;
    it = groupedIeObjectContainer.find(key);
    return *(it->second);
}

void LoadControlInformationIe::insertGroupedIeObject(Uint8 msgType, Uint8 instance, GtpV2GroupedIe* grpIe_p)
{

    Uint16 key = msgType;
    key = (key << 8) + instance;

    groupedIeObjectContainer.insert(std::pair<Uint16, GtpV2GroupedIe*>(key, grpIe_p));

}  