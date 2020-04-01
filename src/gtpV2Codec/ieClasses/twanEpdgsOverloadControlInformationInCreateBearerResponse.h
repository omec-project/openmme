/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef TWANEPDGSOVERLOADCONTROLINFORMATIONINCREATEBEARERRESPONSE_H_
#define TWANEPDGSOVERLOADCONTROLINFORMATIONINCREATEBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class TwanEpdgsOverloadControlInformationInCreateBearerResponse:public GtpV2GroupedIe
{
public:
    TwanEpdgsOverloadControlInformationInCreateBearerResponse();
    virtual ~TwanEpdgsOverloadControlInformationInCreateBearerResponse();
    bool encodeTwanEpdgsOverloadControlInformationInCreateBearerResponse(MsgBuffer &buffer,
                             TwanEpdgsOverloadControlInformationInCreateBearerResponseData
                              const &data);

    bool decodeTwanEpdgsOverloadControlInformationInCreateBearerResponse (MsgBuffer &buffer,
                             TwanEpdgsOverloadControlInformationInCreateBearerResponseData 
                             & data, Uint16 length);

    void displayTwanEpdgsOverloadControlInformationInCreateBearerResponseData_v
    (TwanEpdgsOverloadControlInformationInCreateBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif