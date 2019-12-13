/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef BEARERCONTEXTSTOBEREMOVEDINCREATESESSIONREQUEST_H_
#define BEARERCONTEXTSTOBEREMOVEDINCREATESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsToBeRemovedInCreateSessionRequest:public GtpV2GroupedIe
{
public:
    BearerContextsToBeRemovedInCreateSessionRequest();
    virtual ~BearerContextsToBeRemovedInCreateSessionRequest();
    bool encodeBearerContextsToBeRemovedInCreateSessionRequest(MsgBuffer &buffer,
                             BearerContextsToBeRemovedInCreateSessionRequestData
                              const &data);

    bool decodeBearerContextsToBeRemovedInCreateSessionRequest (MsgBuffer &buffer,
                             BearerContextsToBeRemovedInCreateSessionRequestData 
                             & data, Uint16 length);

    void displayBearerContextsToBeRemovedInCreateSessionRequestData_v
    (BearerContextsToBeRemovedInCreateSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif