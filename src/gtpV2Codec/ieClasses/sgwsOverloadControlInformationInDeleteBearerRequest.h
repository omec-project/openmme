/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSOVERLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_
#define SGWSOVERLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInDeleteBearerRequest:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInDeleteBearerRequest();
    virtual ~SgwsOverloadControlInformationInDeleteBearerRequest();
    bool encodeSgwsOverloadControlInformationInDeleteBearerRequest(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDeleteBearerRequestData
                              const &data);

    bool decodeSgwsOverloadControlInformationInDeleteBearerRequest (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInDeleteBearerRequestData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInDeleteBearerRequestData_v
    (SgwsOverloadControlInformationInDeleteBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif