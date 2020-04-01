/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef BEARERCONTEXTSMODIFIEDINMODIFYBEARERRESPONSE_H_
#define BEARERCONTEXTSMODIFIEDINMODIFYBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class BearerContextsModifiedInModifyBearerResponse:public GtpV2GroupedIe
{
public:
    BearerContextsModifiedInModifyBearerResponse();
    virtual ~BearerContextsModifiedInModifyBearerResponse();
    bool encodeBearerContextsModifiedInModifyBearerResponse(MsgBuffer &buffer,
                             BearerContextsModifiedInModifyBearerResponseData
                              const &data);

    bool decodeBearerContextsModifiedInModifyBearerResponse (MsgBuffer &buffer,
                             BearerContextsModifiedInModifyBearerResponseData 
                             & data, Uint16 length);

    void displayBearerContextsModifiedInModifyBearerResponseData_v
    (BearerContextsModifiedInModifyBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif