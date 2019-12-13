/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSNODELEVELLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_
#define SGWSNODELEVELLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsNodeLevelLoadControlInformationInCreateSessionResponse:public GtpV2GroupedIe
{
public:
    SgwsNodeLevelLoadControlInformationInCreateSessionResponse();
    virtual ~SgwsNodeLevelLoadControlInformationInCreateSessionResponse();
    bool encodeSgwsNodeLevelLoadControlInformationInCreateSessionResponse(MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInCreateSessionResponseData
                              const &data);

    bool decodeSgwsNodeLevelLoadControlInformationInCreateSessionResponse (MsgBuffer &buffer,
                             SgwsNodeLevelLoadControlInformationInCreateSessionResponseData 
                             & data, Uint16 length);

    void displaySgwsNodeLevelLoadControlInformationInCreateSessionResponseData_v
    (SgwsNodeLevelLoadControlInformationInCreateSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif