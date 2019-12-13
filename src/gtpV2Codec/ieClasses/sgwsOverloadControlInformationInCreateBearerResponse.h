/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSOVERLOADCONTROLINFORMATIONINCREATEBEARERRESPONSE_H_
#define SGWSOVERLOADCONTROLINFORMATIONINCREATEBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInCreateBearerResponse:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInCreateBearerResponse();
    virtual ~SgwsOverloadControlInformationInCreateBearerResponse();
    bool encodeSgwsOverloadControlInformationInCreateBearerResponse(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInCreateBearerResponseData
                              const &data);

    bool decodeSgwsOverloadControlInformationInCreateBearerResponse (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInCreateBearerResponseData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInCreateBearerResponseData_v
    (SgwsOverloadControlInformationInCreateBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif