/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef TWANEPDGSOVERLOADCONTROLINFORMATIONINDELETEBEARERRESPONSE_H_
#define TWANEPDGSOVERLOADCONTROLINFORMATIONINDELETEBEARERRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class TwanEpdgsOverloadControlInformationInDeleteBearerResponse:public GtpV2GroupedIe
{
public:
    TwanEpdgsOverloadControlInformationInDeleteBearerResponse();
    virtual ~TwanEpdgsOverloadControlInformationInDeleteBearerResponse();
    bool encodeTwanEpdgsOverloadControlInformationInDeleteBearerResponse(MsgBuffer &buffer,
                             TwanEpdgsOverloadControlInformationInDeleteBearerResponseData
                              const &data);

    bool decodeTwanEpdgsOverloadControlInformationInDeleteBearerResponse (MsgBuffer &buffer,
                             TwanEpdgsOverloadControlInformationInDeleteBearerResponseData 
                             & data, Uint16 length);

    void displayTwanEpdgsOverloadControlInformationInDeleteBearerResponseData_v
    (TwanEpdgsOverloadControlInformationInDeleteBearerResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif