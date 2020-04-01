/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSOVERLOADCONTROLINFORMATIONINMODIFYBEARERREQUEST_H_
#define SGWSOVERLOADCONTROLINFORMATIONINMODIFYBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInModifyBearerRequest:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInModifyBearerRequest();
    virtual ~SgwsOverloadControlInformationInModifyBearerRequest();
    bool encodeSgwsOverloadControlInformationInModifyBearerRequest(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInModifyBearerRequestData
                              const &data);

    bool decodeSgwsOverloadControlInformationInModifyBearerRequest (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInModifyBearerRequestData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInModifyBearerRequestData_v
    (SgwsOverloadControlInformationInModifyBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif