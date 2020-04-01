/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSNODELEVELLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_
#define PGWSNODELEVELLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsNodeLevelLoadControlInformationInModifyBearerResponse:public GtpV2GroupedIe
{
public:
    PgwsNodeLevelLoadControlInformationInModifyBearerResponse();
    virtual ~PgwsNodeLevelLoadControlInformationInModifyBearerResponse();
    bool encodePgwsNodeLevelLoadControlInformationInModifyBearerResponse(MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInModifyBearerResponseData
                              const &data);

    bool decodePgwsNodeLevelLoadControlInformationInModifyBearerResponse (MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInModifyBearerResponseData 
                             & data, Uint16 length);

    void displayPgwsNodeLevelLoadControlInformationInModifyBearerResponseData_v
    (PgwsNodeLevelLoadControlInformationInModifyBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif