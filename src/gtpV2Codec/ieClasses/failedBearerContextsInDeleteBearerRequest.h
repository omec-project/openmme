/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef FAILEDBEARERCONTEXTSINDELETEBEARERREQUEST_H_
#define FAILEDBEARERCONTEXTSINDELETEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class FailedBearerContextsInDeleteBearerRequest:public GtpV2GroupedIe
{
public:
    FailedBearerContextsInDeleteBearerRequest();
    virtual ~FailedBearerContextsInDeleteBearerRequest();
    bool encodeFailedBearerContextsInDeleteBearerRequest(MsgBuffer &buffer,
                             FailedBearerContextsInDeleteBearerRequestData
                              const &data);

    bool decodeFailedBearerContextsInDeleteBearerRequest (MsgBuffer &buffer,
                             FailedBearerContextsInDeleteBearerRequestData 
                             & data, Uint16 length);

    void displayFailedBearerContextsInDeleteBearerRequestData_v
    (FailedBearerContextsInDeleteBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif