/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSNODELEVELLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_
#define SGWSNODELEVELLOADCONTROLINFORMATIONINCREATEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsNodeLevelLoadControlInformationInCreateBearerRequest:public GtpV2GroupedIe
{
public:
    SgwsNodeLevelLoadControlInformationInCreateBearerRequest();
    virtual ~SgwsNodeLevelLoadControlInformationInCreateBearerRequest();
    bool encodeSgwsNodeLevelLoadControlInformationInCreateBearerRequest(MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInCreateBearerRequestData
                              const &data);

    bool decodeSgwsNodeLevelLoadControlInformationInCreateBearerRequest (MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInCreateBearerRequestData 
                             & data, Uint16 length);

    void displaySgwsNodeLevelLoadControlInformationInCreateBearerRequestData_v
    (SgwsNodeLevelLoadControlInformationInCreateBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif