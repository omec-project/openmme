/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef MMES4SGSNSOVERLOADCONTROLINFORMATIONINCREATEBEARERRESPONSE_H_
#define MMES4SGSNSOVERLOADCONTROLINFORMATIONINCREATEBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class MmeS4SgsnsOverloadControlInformationInCreateBearerResponse:public GtpV2GroupedIe
{
public:
    MmeS4SgsnsOverloadControlInformationInCreateBearerResponse();
    virtual ~MmeS4SgsnsOverloadControlInformationInCreateBearerResponse();
    bool encodeMmeS4SgsnsOverloadControlInformationInCreateBearerResponse(MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInCreateBearerResponseData
                              const &data);

    bool decodeMmeS4SgsnsOverloadControlInformationInCreateBearerResponse (MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInCreateBearerResponseData 
                             & data, Uint16 length);

    void displayMmeS4SgsnsOverloadControlInformationInCreateBearerResponseData_v
    (MmeS4SgsnsOverloadControlInformationInCreateBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif