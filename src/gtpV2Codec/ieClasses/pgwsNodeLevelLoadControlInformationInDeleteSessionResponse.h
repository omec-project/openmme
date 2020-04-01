/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSNODELEVELLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_
#define PGWSNODELEVELLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsNodeLevelLoadControlInformationInDeleteSessionResponse:public GtpV2GroupedIe
{
public:
    PgwsNodeLevelLoadControlInformationInDeleteSessionResponse();
    virtual ~PgwsNodeLevelLoadControlInformationInDeleteSessionResponse();
    bool encodePgwsNodeLevelLoadControlInformationInDeleteSessionResponse(MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInDeleteSessionResponseData
                              const &data);

    bool decodePgwsNodeLevelLoadControlInformationInDeleteSessionResponse (MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInDeleteSessionResponseData 
                             & data, Uint16 length);

    void displayPgwsNodeLevelLoadControlInformationInDeleteSessionResponseData_v
    (PgwsNodeLevelLoadControlInformationInDeleteSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif