/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSAPNLEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_
#define PGWSAPNLEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsApnLevelLoadControlInformationInDeleteBearerRequest:public GtpV2GroupedIe
{
public:
    PgwsApnLevelLoadControlInformationInDeleteBearerRequest();
    virtual ~PgwsApnLevelLoadControlInformationInDeleteBearerRequest();
    bool encodePgwsApnLevelLoadControlInformationInDeleteBearerRequest(MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInDeleteBearerRequestData
                              const &data);

    bool decodePgwsApnLevelLoadControlInformationInDeleteBearerRequest (MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInDeleteBearerRequestData 
                             & data, Uint16 length);

    void displayPgwsApnLevelLoadControlInformationInDeleteBearerRequestData_v
    (PgwsApnLevelLoadControlInformationInDeleteBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif