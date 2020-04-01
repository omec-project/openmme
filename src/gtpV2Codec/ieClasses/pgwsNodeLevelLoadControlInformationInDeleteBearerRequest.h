/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSNODELEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_
#define PGWSNODELEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsNodeLevelLoadControlInformationInDeleteBearerRequest:public GtpV2GroupedIe
{
public:
    PgwsNodeLevelLoadControlInformationInDeleteBearerRequest();
    virtual ~PgwsNodeLevelLoadControlInformationInDeleteBearerRequest();
    bool encodePgwsNodeLevelLoadControlInformationInDeleteBearerRequest(MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData
                              const &data);

    bool decodePgwsNodeLevelLoadControlInformationInDeleteBearerRequest (MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData 
                             & data, Uint16 length);

    void displayPgwsNodeLevelLoadControlInformationInDeleteBearerRequestData_v
    (PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif