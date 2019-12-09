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

#ifndef PGWSOVERLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_
#define PGWSOVERLOADCONTROLINFORMATIONINDELETESESSIONRESPONSE_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsOverloadControlInformationInDeleteSessionResponse:public GtpV2GroupedIe
{
public:
    PgwsOverloadControlInformationInDeleteSessionResponse();
    virtual ~PgwsOverloadControlInformationInDeleteSessionResponse();
    bool encodePgwsOverloadControlInformationInDeleteSessionResponse(MsgBuffer &buffer,
                             PgwsOverloadControlInformationInDeleteSessionResponseData
                              const &data);

    bool decodePgwsOverloadControlInformationInDeleteSessionResponse (MsgBuffer &buffer,
                             PgwsOverloadControlInformationInDeleteSessionResponseData 
                             & data, Uint16 length);

    void displayPgwsOverloadControlInformationInDeleteSessionResponseData_v
    (PgwsOverloadControlInformationInDeleteSessionResponseData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif