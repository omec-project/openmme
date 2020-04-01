/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSNODELEVELLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_
#define PGWSNODELEVELLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsNodeLevelLoadControlInformationInCreateBearerRequest:public GtpV2GroupedIe
{
public:
    PgwsNodeLevelLoadControlInformationInCreateBearerRequest();
    virtual ~PgwsNodeLevelLoadControlInformationInCreateBearerRequest();
    bool encodePgwsNodeLevelLoadControlInformationInCreateBearerRequest(MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInCreateBearerRequestData
                              const &data);

    bool decodePgwsNodeLevelLoadControlInformationInCreateBearerRequest (MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInCreateBearerRequestData 
                             & data, Uint16 length);

    void displayPgwsNodeLevelLoadControlInformationInCreateBearerRequestData_v
    (PgwsNodeLevelLoadControlInformationInCreateBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif