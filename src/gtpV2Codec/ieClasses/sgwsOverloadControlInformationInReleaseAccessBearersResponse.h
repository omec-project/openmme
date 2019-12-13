/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SGWSOVERLOADCONTROLINFORMATIONINRELEASEACCESSBEARERSRESPONSE_H_
#define SGWSOVERLOADCONTROLINFORMATIONINRELEASEACCESSBEARERSRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class SgwsOverloadControlInformationInReleaseAccessBearersResponse:public GtpV2GroupedIe
{
public:
    SgwsOverloadControlInformationInReleaseAccessBearersResponse();
    virtual ~SgwsOverloadControlInformationInReleaseAccessBearersResponse();
    bool encodeSgwsOverloadControlInformationInReleaseAccessBearersResponse(MsgBuffer &buffer,
                             SgwsOverloadControlInformationInReleaseAccessBearersResponseData
                              const &data);

    bool decodeSgwsOverloadControlInformationInReleaseAccessBearersResponse (MsgBuffer &buffer,
                             SgwsOverloadControlInformationInReleaseAccessBearersResponseData 
                             & data, Uint16 length);

    void displaySgwsOverloadControlInformationInReleaseAccessBearersResponseData_v
    (SgwsOverloadControlInformationInReleaseAccessBearersResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif