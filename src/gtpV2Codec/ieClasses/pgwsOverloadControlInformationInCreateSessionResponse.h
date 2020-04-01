/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSOVERLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_
#define PGWSOVERLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsOverloadControlInformationInCreateSessionResponse:public GtpV2GroupedIe
{
public:
    PgwsOverloadControlInformationInCreateSessionResponse();
    virtual ~PgwsOverloadControlInformationInCreateSessionResponse();
    bool encodePgwsOverloadControlInformationInCreateSessionResponse(MsgBuffer &buffer,
                             PgwsOverloadControlInformationInCreateSessionResponseData
                              const &data);

    bool decodePgwsOverloadControlInformationInCreateSessionResponse (MsgBuffer &buffer,
                             PgwsOverloadControlInformationInCreateSessionResponseData 
                             & data, Uint16 length);

    void displayPgwsOverloadControlInformationInCreateSessionResponseData_v
    (PgwsOverloadControlInformationInCreateSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif