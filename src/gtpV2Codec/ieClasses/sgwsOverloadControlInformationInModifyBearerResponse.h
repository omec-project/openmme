/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSOVERLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_
#define SGWSOVERLOADCONTROLINFORMATIONINMODIFYBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInModifyBearerResponse:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInModifyBearerResponse();
    virtual ~SgwsOverloadControlInformationInModifyBearerResponse();
    bool encodeSgwsOverloadControlInformationInModifyBearerResponse(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInModifyBearerResponseData
                              const &data);

    bool decodeSgwsOverloadControlInformationInModifyBearerResponse (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInModifyBearerResponseData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInModifyBearerResponseData_v
    (SgwsOverloadControlInformationInModifyBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif