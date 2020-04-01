/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PGWSAPNLEVELLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_
#define PGWSAPNLEVELLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsApnLevelLoadControlInformationInCreateSessionResponse:public GtpV2GroupedIe
{
public:
    PgwsApnLevelLoadControlInformationInCreateSessionResponse();
    virtual ~PgwsApnLevelLoadControlInformationInCreateSessionResponse();
    bool encodePgwsApnLevelLoadControlInformationInCreateSessionResponse(MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInCreateSessionResponseData
                              const &data);

    bool decodePgwsApnLevelLoadControlInformationInCreateSessionResponse (MsgBuffer &buffer,
                             PgwsApnLevelLoadControlInformationInCreateSessionResponseData 
                             & data, Uint16 length);

    void displayPgwsApnLevelLoadControlInformationInCreateSessionResponseData_v
    (PgwsApnLevelLoadControlInformationInCreateSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif