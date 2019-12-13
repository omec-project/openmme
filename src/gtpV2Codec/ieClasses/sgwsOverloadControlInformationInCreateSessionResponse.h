/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSOVERLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_
#define SGWSOVERLOADCONTROLINFORMATIONINCREATESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInCreateSessionResponse:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInCreateSessionResponse();
    virtual ~SgwsOverloadControlInformationInCreateSessionResponse();
    bool encodeSgwsOverloadControlInformationInCreateSessionResponse(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInCreateSessionResponseData
                              const &data);

    bool decodeSgwsOverloadControlInformationInCreateSessionResponse (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInCreateSessionResponseData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInCreateSessionResponseData_v
    (SgwsOverloadControlInformationInCreateSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif