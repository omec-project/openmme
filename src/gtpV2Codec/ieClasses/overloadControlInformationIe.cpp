/*
 * overloadControlInformationIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "overloadControlInformationIe.h"
#include "gtpV2GrpIeDataTypes.h"
#include "manual/gtpV2GroupedIe.h"

#include "sgwsOverloadControlInformationInCreateSessionRequest.h"
#include "twanEpdgsOverloadControlInformationInCreateSessionRequest.h"
#include "mmeS4SgsnsOverloadControlInformationInCreateSessionRequest.h"
#include "pgwsOverloadControlInformationInCreateSessionResponse.h"
#include "sgwsOverloadControlInformationInCreateSessionResponse.h"
#include "mmeS4SgsnsOverloadControlInformationInModifyBearerRequest.h"
#include "sgwsOverloadControlInformationInModifyBearerRequest.h"
#include "epdgsOverloadControlInformationInModifyBearerRequest.h"
#include "sgwsOverloadControlInformationInModifyBearerResponse.h"
#include "pgwsOverloadControlInformationInModifyBearerResponse.h"
#include "mmeS4SgsnsOverloadControlInformationInDeleteSessionRequest.h"
#include "sgwsOverloadControlInformationInDeleteSessionRequest.h"
#include "twanEpdgsOverloadControlInformationInDeleteSessionRequest.h"
#include "sgwsOverloadControlInformationInDeleteSessionResponse.h"
#include "pgwsOverloadControlInformationInDeleteSessionResponse.h"
#include "sgwsOverloadControlInformationInReleaseAccessBearersResponse.h"
#include "pgwsOverloadControlInformationInCreateBearerRequest.h"
#include "sgwsOverloadControlInformationInCreateBearerRequest.h"
#include "mmeS4SgsnsOverloadControlInformationInCreateBearerResponse.h"
#include "sgwsOverloadControlInformationInCreateBearerResponse.h"
#include "twanEpdgsOverloadControlInformationInCreateBearerResponse.h"
#include "pgwsOverloadControlInformationInDeleteBearerRequest.h"
#include "sgwsOverloadControlInformationInDeleteBearerRequest.h"
#include "mmeS4SgsnsOverloadControlInformationInDeleteBearerResponse.h"
#include "sgwsOverloadControlInformationInDeleteBearerResponse.h"
#include "twanEpdgsOverloadControlInformationInDeleteBearerResponse.h"
#include "sgwsOverloadControlInformationInDownlinkDataNotification.h"

OverloadControlInformationIe::OverloadControlInformationIe()
{
    ieType = OverloadControlInformationIeType;
   
    SgwsOverloadControlInformationInCreateSessionRequest* sgwsOverloadControlInformationInCreateSessionRequest_p = new (SgwsOverloadControlInformationInCreateSessionRequest);
    insertGroupedIeObject(CreateSessionRequestMsgType, 1, sgwsOverloadControlInformationInCreateSessionRequest_p);
    TwanEpdgsOverloadControlInformationInCreateSessionRequest* twanEpdgsOverloadControlInformationInCreateSessionRequest_p = new (TwanEpdgsOverloadControlInformationInCreateSessionRequest);
    insertGroupedIeObject(CreateSessionRequestMsgType, 2, twanEpdgsOverloadControlInformationInCreateSessionRequest_p);
    MmeS4SgsnsOverloadControlInformationInCreateSessionRequest* mmeS4SgsnsOverloadControlInformationInCreateSessionRequest_p = new (MmeS4SgsnsOverloadControlInformationInCreateSessionRequest);
    insertGroupedIeObject(CreateSessionRequestMsgType, 0, mmeS4SgsnsOverloadControlInformationInCreateSessionRequest_p);
    PgwsOverloadControlInformationInCreateSessionResponse* pgwsOverloadControlInformationInCreateSessionResponse_p = new (PgwsOverloadControlInformationInCreateSessionResponse);
    insertGroupedIeObject(CreateSessionResponseMsgType, 0, pgwsOverloadControlInformationInCreateSessionResponse_p);
    SgwsOverloadControlInformationInCreateSessionResponse* sgwsOverloadControlInformationInCreateSessionResponse_p = new (SgwsOverloadControlInformationInCreateSessionResponse);
    insertGroupedIeObject(CreateSessionResponseMsgType, 1, sgwsOverloadControlInformationInCreateSessionResponse_p);
    MmeS4SgsnsOverloadControlInformationInModifyBearerRequest* mmeS4SgsnsOverloadControlInformationInModifyBearerRequest_p = new (MmeS4SgsnsOverloadControlInformationInModifyBearerRequest);
    insertGroupedIeObject(ModifyBearerRequestMsgType, 0, mmeS4SgsnsOverloadControlInformationInModifyBearerRequest_p);
    SgwsOverloadControlInformationInModifyBearerRequest* sgwsOverloadControlInformationInModifyBearerRequest_p = new (SgwsOverloadControlInformationInModifyBearerRequest);
    insertGroupedIeObject(ModifyBearerRequestMsgType, 1, sgwsOverloadControlInformationInModifyBearerRequest_p);
    EpdgsOverloadControlInformationInModifyBearerRequest* epdgsOverloadControlInformationInModifyBearerRequest_p = new (EpdgsOverloadControlInformationInModifyBearerRequest);
    insertGroupedIeObject(ModifyBearerRequestMsgType, 2, epdgsOverloadControlInformationInModifyBearerRequest_p);
    SgwsOverloadControlInformationInModifyBearerResponse* sgwsOverloadControlInformationInModifyBearerResponse_p = new (SgwsOverloadControlInformationInModifyBearerResponse);
    insertGroupedIeObject(ModifyBearerResponseMsgType, 1, sgwsOverloadControlInformationInModifyBearerResponse_p);
    PgwsOverloadControlInformationInModifyBearerResponse* pgwsOverloadControlInformationInModifyBearerResponse_p = new (PgwsOverloadControlInformationInModifyBearerResponse);
    insertGroupedIeObject(ModifyBearerResponseMsgType, 0, pgwsOverloadControlInformationInModifyBearerResponse_p);
    MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest* mmeS4SgsnsOverloadControlInformationInDeleteSessionRequest_p = new (MmeS4SgsnsOverloadControlInformationInDeleteSessionRequest);
    insertGroupedIeObject(DeleteSessionRequestMsgType, 0, mmeS4SgsnsOverloadControlInformationInDeleteSessionRequest_p);
    SgwsOverloadControlInformationInDeleteSessionRequest* sgwsOverloadControlInformationInDeleteSessionRequest_p = new (SgwsOverloadControlInformationInDeleteSessionRequest);
    insertGroupedIeObject(DeleteSessionRequestMsgType, 1, sgwsOverloadControlInformationInDeleteSessionRequest_p);
    TwanEpdgsOverloadControlInformationInDeleteSessionRequest* twanEpdgsOverloadControlInformationInDeleteSessionRequest_p = new (TwanEpdgsOverloadControlInformationInDeleteSessionRequest);
    insertGroupedIeObject(DeleteSessionRequestMsgType, 2, twanEpdgsOverloadControlInformationInDeleteSessionRequest_p);
    SgwsOverloadControlInformationInDeleteSessionResponse* sgwsOverloadControlInformationInDeleteSessionResponse_p = new (SgwsOverloadControlInformationInDeleteSessionResponse);
    insertGroupedIeObject(DeleteSessionResponseMsgType, 1, sgwsOverloadControlInformationInDeleteSessionResponse_p);
    PgwsOverloadControlInformationInDeleteSessionResponse* pgwsOverloadControlInformationInDeleteSessionResponse_p = new (PgwsOverloadControlInformationInDeleteSessionResponse);
    insertGroupedIeObject(DeleteSessionResponseMsgType, 0, pgwsOverloadControlInformationInDeleteSessionResponse_p);
    SgwsOverloadControlInformationInReleaseAccessBearersResponse* sgwsOverloadControlInformationInReleaseAccessBearersResponse_p = new (SgwsOverloadControlInformationInReleaseAccessBearersResponse);
    insertGroupedIeObject(ReleaseAccessBearersResponseMsgType, 0, sgwsOverloadControlInformationInReleaseAccessBearersResponse_p);
    PgwsOverloadControlInformationInCreateBearerRequest* pgwsOverloadControlInformationInCreateBearerRequest_p = new (PgwsOverloadControlInformationInCreateBearerRequest);
    insertGroupedIeObject(CreateBearerRequestMsgType, 0, pgwsOverloadControlInformationInCreateBearerRequest_p);
    SgwsOverloadControlInformationInCreateBearerRequest* sgwsOverloadControlInformationInCreateBearerRequest_p = new (SgwsOverloadControlInformationInCreateBearerRequest);
    insertGroupedIeObject(CreateBearerRequestMsgType, 1, sgwsOverloadControlInformationInCreateBearerRequest_p);
    MmeS4SgsnsOverloadControlInformationInCreateBearerResponse* mmeS4SgsnsOverloadControlInformationInCreateBearerResponse_p = new (MmeS4SgsnsOverloadControlInformationInCreateBearerResponse);
    insertGroupedIeObject(CreateBearerResponseMsgType, 0, mmeS4SgsnsOverloadControlInformationInCreateBearerResponse_p);
    SgwsOverloadControlInformationInCreateBearerResponse* sgwsOverloadControlInformationInCreateBearerResponse_p = new (SgwsOverloadControlInformationInCreateBearerResponse);
    insertGroupedIeObject(CreateBearerResponseMsgType, 1, sgwsOverloadControlInformationInCreateBearerResponse_p);
    TwanEpdgsOverloadControlInformationInCreateBearerResponse* twanEpdgsOverloadControlInformationInCreateBearerResponse_p = new (TwanEpdgsOverloadControlInformationInCreateBearerResponse);
    insertGroupedIeObject(CreateBearerResponseMsgType, 2, twanEpdgsOverloadControlInformationInCreateBearerResponse_p);
    PgwsOverloadControlInformationInDeleteBearerRequest* pgwsOverloadControlInformationInDeleteBearerRequest_p = new (PgwsOverloadControlInformationInDeleteBearerRequest);
    insertGroupedIeObject(DeleteBearerRequestMsgType, 0, pgwsOverloadControlInformationInDeleteBearerRequest_p);
    SgwsOverloadControlInformationInDeleteBearerRequest* sgwsOverloadControlInformationInDeleteBearerRequest_p = new (SgwsOverloadControlInformationInDeleteBearerRequest);
    insertGroupedIeObject(DeleteBearerRequestMsgType, 1, sgwsOverloadControlInformationInDeleteBearerRequest_p);
    MmeS4SgsnsOverloadControlInformationInDeleteBearerResponse* mmeS4SgsnsOverloadControlInformationInDeleteBearerResponse_p = new (MmeS4SgsnsOverloadControlInformationInDeleteBearerResponse);
    insertGroupedIeObject(DeleteBearerResponseMsgType, 0, mmeS4SgsnsOverloadControlInformationInDeleteBearerResponse_p);
    SgwsOverloadControlInformationInDeleteBearerResponse* sgwsOverloadControlInformationInDeleteBearerResponse_p = new (SgwsOverloadControlInformationInDeleteBearerResponse);
    insertGroupedIeObject(DeleteBearerResponseMsgType, 1, sgwsOverloadControlInformationInDeleteBearerResponse_p);
    TwanEpdgsOverloadControlInformationInDeleteBearerResponse* twanEpdgsOverloadControlInformationInDeleteBearerResponse_p = new (TwanEpdgsOverloadControlInformationInDeleteBearerResponse);
    insertGroupedIeObject(DeleteBearerResponseMsgType, 2, twanEpdgsOverloadControlInformationInDeleteBearerResponse_p);
    SgwsOverloadControlInformationInDownlinkDataNotification* sgwsOverloadControlInformationInDownlinkDataNotification_p = new (SgwsOverloadControlInformationInDownlinkDataNotification);
    insertGroupedIeObject(DownlinkDataNotificationMsgType, 0, sgwsOverloadControlInformationInDownlinkDataNotification_p);
}

OverloadControlInformationIe::~OverloadControlInformationIe() {
// TODO Auto-generated destructor stub
}

GtpV2GroupedIe& OverloadControlInformationIe::getGroupedIe(Uint8 msgType, Uint8 instance)
{
    std::map<Uint16, GtpV2GroupedIe*>::iterator it;
    Uint16 key = msgType;
    key = (key << 8) + instance;
    it = groupedIeObjectContainer.find(key);
    return *(it->second);
}

void OverloadControlInformationIe::insertGroupedIeObject(Uint8 msgType, Uint8 instance, GtpV2GroupedIe* grpIe_p)
{

    Uint16 key = msgType;
    key = (key << 8) + instance;

    groupedIeObjectContainer.insert(std::pair<Uint16, GtpV2GroupedIe*>(key, grpIe_p));

}  