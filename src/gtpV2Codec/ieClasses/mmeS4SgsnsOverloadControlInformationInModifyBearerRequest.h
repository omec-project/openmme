/*
* Copyright (c) 2019 Infosys Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef MMES4SGSNSOVERLOADCONTROLINFORMATIONINMODIFYBEARERREQUEST_H_
#define MMES4SGSNSOVERLOADCONTROLINFORMATIONINMODIFYBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class MmeS4SgsnsOverloadControlInformationInModifyBearerRequest:public GtpV2GroupedIe
{
public:
    MmeS4SgsnsOverloadControlInformationInModifyBearerRequest();
    virtual ~MmeS4SgsnsOverloadControlInformationInModifyBearerRequest();
    bool encodeMmeS4SgsnsOverloadControlInformationInModifyBearerRequest(MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInModifyBearerRequestData
                              const &data);

    bool decodeMmeS4SgsnsOverloadControlInformationInModifyBearerRequest (MsgBuffer &buffer,
                             MmeS4SgsnsOverloadControlInformationInModifyBearerRequestData 
                             & data, Uint16 length);

    void displayMmeS4SgsnsOverloadControlInformationInModifyBearerRequestData_v
    (MmeS4SgsnsOverloadControlInformationInModifyBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif