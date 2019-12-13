/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSOVERLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_
#define PGWSOVERLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsOverloadControlInformationInModifyBearerResponse:public GtpV2GroupedIe
{
public:
    PgwsOverloadControlInformationInModifyBearerResponse();
    virtual ~PgwsOverloadControlInformationInModifyBearerResponse();
    bool encodePgwsOverloadControlInformationInModifyBearerResponse(MsgBuffer &buffer,
                             PgwsOverloadControlInformationInModifyBearerResponseData
                              const &data);

    bool decodePgwsOverloadControlInformationInModifyBearerResponse (MsgBuffer &buffer,
                             PgwsOverloadControlInformationInModifyBearerResponseData 
                             & data, Uint16 length);

    void displayPgwsOverloadControlInformationInModifyBearerResponseData_v
    (PgwsOverloadControlInformationInModifyBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif