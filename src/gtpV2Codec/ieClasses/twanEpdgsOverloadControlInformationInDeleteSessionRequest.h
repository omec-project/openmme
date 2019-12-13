/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef TWANEPDGSOVERLOADCONTROLINFORMATIONINDELETESESSIONREQUEST_H_
#define TWANEPDGSOVERLOADCONTROLINFORMATIONINDELETESESSIONREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class TwanEpdgsOverloadControlInformationInDeleteSessionRequest:public GtpV2GroupedIe
{
public:
    TwanEpdgsOverloadControlInformationInDeleteSessionRequest();
    virtual ~TwanEpdgsOverloadControlInformationInDeleteSessionRequest();
    bool encodeTwanEpdgsOverloadControlInformationInDeleteSessionRequest(MsgBuffer &buffer,
                             TwanEpdgsOverloadControlInformationInDeleteSessionRequestData
                              const &data);

    bool decodeTwanEpdgsOverloadControlInformationInDeleteSessionRequest (MsgBuffer &buffer,
                             TwanEpdgsOverloadControlInformationInDeleteSessionRequestData 
                             & data, Uint16 length);

    void displayTwanEpdgsOverloadControlInformationInDeleteSessionRequestData_v
    (TwanEpdgsOverloadControlInformationInDeleteSessionRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif