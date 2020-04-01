/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSNODELEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_
#define SGWSNODELEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsNodeLevelLoadControlInformationInDeleteBearerRequest:public GtpV2GroupedIe
{
public:
    SgwsNodeLevelLoadControlInformationInDeleteBearerRequest();
    virtual ~SgwsNodeLevelLoadControlInformationInDeleteBearerRequest();
    bool encodeSgwsNodeLevelLoadControlInformationInDeleteBearerRequest(MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInDeleteBearerRequestData
                              const &data);

    bool decodeSgwsNodeLevelLoadControlInformationInDeleteBearerRequest (MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInDeleteBearerRequestData 
                             & data, Uint16 length);

    void displaySgwsNodeLevelLoadControlInformationInDeleteBearerRequestData_v
    (SgwsNodeLevelLoadControlInformationInDeleteBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif