/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef MMES4SGSNSOVERLOADCONTROLINFORMATIONINDELETEBEARERRESPONSE_H_
#define MMES4SGSNSOVERLOADCONTROLINFORMATIONINDELETEBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class MmeS4SgsnsOverloadControlInformationInDeleteBearerResponse:public GtpV2GroupedIe
{
public:
    MmeS4SgsnsOverloadControlInformationInDeleteBearerResponse();
    virtual ~MmeS4SgsnsOverloadControlInformationInDeleteBearerResponse();
    bool encodeMmeS4SgsnsOverloadControlInformationInDeleteBearerResponse(MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInDeleteBearerResponseData
                              const &data);

    bool decodeMmeS4SgsnsOverloadControlInformationInDeleteBearerResponse (MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInDeleteBearerResponseData 
                             & data, Uint16 length);

    void displayMmeS4SgsnsOverloadControlInformationInDeleteBearerResponseData_v
    (MmeS4SgsnsOverloadControlInformationInDeleteBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif