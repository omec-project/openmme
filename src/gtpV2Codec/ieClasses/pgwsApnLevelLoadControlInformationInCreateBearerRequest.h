/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSAPNLEVELLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_
#define PGWSAPNLEVELLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsApnLevelLoadControlInformationInCreateBearerRequest:public GtpV2GroupedIe
{
public:
    PgwsApnLevelLoadControlInformationInCreateBearerRequest();
    virtual ~PgwsApnLevelLoadControlInformationInCreateBearerRequest();
    bool encodePgwsApnLevelLoadControlInformationInCreateBearerRequest(MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInCreateBearerRequestData
                              const &data);

    bool decodePgwsApnLevelLoadControlInformationInCreateBearerRequest (MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInCreateBearerRequestData 
                             & data, Uint16 length);

    void displayPgwsApnLevelLoadControlInformationInCreateBearerRequestData_v
    (PgwsApnLevelLoadControlInformationInCreateBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif