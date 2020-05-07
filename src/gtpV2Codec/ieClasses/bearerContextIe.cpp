/*
 * bearerContextIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#include "bearerContextIe.h"
#include "gtpV2GrpIeDataTypes.h"
#include "manual/gtpV2GroupedIe.h"

#include "bearerContextsToBeModifiedInModifyBearerRequest.h"
#include "bearerContextsToBeRemovedInModifyBearerRequest.h"
#include "bearerContextsMarkedForRemovalInModifyBearerResponse.h"
#include "bearerContextsModifiedInModifyBearerResponse.h"
#include "bearerContextsToBeCreatedInCreateSessionRequest.h"
#include "bearerContextsToBeRemovedInCreateSessionRequest.h"
#include "bearerContextsCreatedInCreateSessionResponse.h"
#include "bearerContextsMarkedForRemovalInCreateSessionResponse.h"
#include "bearerContextsInCreateBearerRequest.h"
#include "bearerContextsInCreateBearerResponse.h"
#include "failedBearerContextsInDeleteBearerRequest.h"
#include "bearerContextsInDeleteBearerResponse.h"

BearerContextIe::BearerContextIe()
{
    ieType = BearerContextIeType;
   
    BearerContextsToBeModifiedInModifyBearerRequest* bearerContextsToBeModifiedInModifyBearerRequest_p = new (BearerContextsToBeModifiedInModifyBearerRequest);
    insertGroupedIeObject(ModifyBearerRequestMsgType, 0, bearerContextsToBeModifiedInModifyBearerRequest_p);
    BearerContextsToBeRemovedInModifyBearerRequest* bearerContextsToBeRemovedInModifyBearerRequest_p = new (BearerContextsToBeRemovedInModifyBearerRequest);
    insertGroupedIeObject(ModifyBearerRequestMsgType, 1, bearerContextsToBeRemovedInModifyBearerRequest_p);
    BearerContextsMarkedForRemovalInModifyBearerResponse* bearerContextsMarkedForRemovalInModifyBearerResponse_p = new (BearerContextsMarkedForRemovalInModifyBearerResponse);
    insertGroupedIeObject(ModifyBearerResponseMsgType, 0, bearerContextsMarkedForRemovalInModifyBearerResponse_p);
    BearerContextsModifiedInModifyBearerResponse* bearerContextsModifiedInModifyBearerResponse_p = new (BearerContextsModifiedInModifyBearerResponse);
    insertGroupedIeObject(ModifyBearerResponseMsgType, 1, bearerContextsModifiedInModifyBearerResponse_p);
    BearerContextsToBeCreatedInCreateSessionRequest* bearerContextsToBeCreatedInCreateSessionRequest_p = new (BearerContextsToBeCreatedInCreateSessionRequest);
    insertGroupedIeObject(CreateSessionRequestMsgType, 0, bearerContextsToBeCreatedInCreateSessionRequest_p);
    BearerContextsToBeRemovedInCreateSessionRequest* bearerContextsToBeRemovedInCreateSessionRequest_p = new (BearerContextsToBeRemovedInCreateSessionRequest);
    insertGroupedIeObject(CreateSessionRequestMsgType, 1, bearerContextsToBeRemovedInCreateSessionRequest_p);
    BearerContextsCreatedInCreateSessionResponse* bearerContextsCreatedInCreateSessionResponse_p = new (BearerContextsCreatedInCreateSessionResponse);
    insertGroupedIeObject(CreateSessionResponseMsgType, 0, bearerContextsCreatedInCreateSessionResponse_p);
    BearerContextsMarkedForRemovalInCreateSessionResponse* bearerContextsMarkedForRemovalInCreateSessionResponse_p = new (BearerContextsMarkedForRemovalInCreateSessionResponse);
    insertGroupedIeObject(CreateSessionResponseMsgType, 1, bearerContextsMarkedForRemovalInCreateSessionResponse_p);
    BearerContextsInCreateBearerRequest* bearerContextsInCreateBearerRequest_p = new (BearerContextsInCreateBearerRequest);
    insertGroupedIeObject(CreateBearerRequestMsgType, 0, bearerContextsInCreateBearerRequest_p);
    BearerContextsInCreateBearerResponse* bearerContextsInCreateBearerResponse_p = new (BearerContextsInCreateBearerResponse);
    insertGroupedIeObject(CreateBearerResponseMsgType, 0, bearerContextsInCreateBearerResponse_p);
    FailedBearerContextsInDeleteBearerRequest* failedBearerContextsInDeleteBearerRequest_p = new (FailedBearerContextsInDeleteBearerRequest);
    insertGroupedIeObject(DeleteBearerRequestMsgType, 0, failedBearerContextsInDeleteBearerRequest_p);
    BearerContextsInDeleteBearerResponse* bearerContextsInDeleteBearerResponse_p = new (BearerContextsInDeleteBearerResponse);
    insertGroupedIeObject(DeleteBearerResponseMsgType, 0, bearerContextsInDeleteBearerResponse_p);
}

BearerContextIe::~BearerContextIe() {
// TODO Auto-generated destructor stub
}

GtpV2GroupedIe& BearerContextIe::getGroupedIe(Uint8 msgType, Uint8 instance)
{
    std::map<Uint16, GtpV2GroupedIe*>::iterator it;
    Uint16 key = msgType;
    key = (key << 8) + instance;
    it = groupedIeObjectContainer.find(key);
    return *(it->second);
}

void BearerContextIe::insertGroupedIeObject(Uint8 msgType, Uint8 instance, GtpV2GroupedIe* grpIe_p)
{

    Uint16 key = msgType;
    key = (key << 8) + instance;

    groupedIeObjectContainer.insert(std::pair<Uint16, GtpV2GroupedIe*>(key, grpIe_p));

}  