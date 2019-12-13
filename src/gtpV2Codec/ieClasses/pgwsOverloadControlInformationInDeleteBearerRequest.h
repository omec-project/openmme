/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSOVERLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_
#define PGWSOVERLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsOverloadControlInformationInDeleteBearerRequest:public GtpV2GroupedIe
{
public:
    PgwsOverloadControlInformationInDeleteBearerRequest();
    virtual ~PgwsOverloadControlInformationInDeleteBearerRequest();
    bool encodePgwsOverloadControlInformationInDeleteBearerRequest(MsgBuffer &buffer,
                             PgwsOverloadControlInformationInDeleteBearerRequestData
                              const &data);

    bool decodePgwsOverloadControlInformationInDeleteBearerRequest (MsgBuffer &buffer,
                             PgwsOverloadControlInformationInDeleteBearerRequestData 
                             & data, Uint16 length);

    void displayPgwsOverloadControlInformationInDeleteBearerRequestData_v
    (PgwsOverloadControlInformationInDeleteBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif