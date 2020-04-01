/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef BEARERCONTEXTSINCREATEBEARERREQUEST_H_
#define BEARERCONTEXTSINCREATEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsInCreateBearerRequest:public GtpV2GroupedIe
{
public:
    BearerContextsInCreateBearerRequest();
    virtual ~BearerContextsInCreateBearerRequest();
    bool encodeBearerContextsInCreateBearerRequest(MsgBuffer &buffer,
                             BearerContextsInCreateBearerRequestData
                              const &data);

    bool decodeBearerContextsInCreateBearerRequest (MsgBuffer &buffer,
                             BearerContextsInCreateBearerRequestData 
                             & data, Uint16 length);

    void displayBearerContextsInCreateBearerRequestData_v
    (BearerContextsInCreateBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif