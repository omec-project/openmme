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

#ifndef PGWSNODELEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_
#define PGWSNODELEVELLOADCONTROLINFORMATIONINDELETEBEARERREQUEST_H_

#include <set>
#include <sstream>
#include "manual/gtpV2GroupedIe.h"
#include <msgBuffer.h>
#include "gtpV2GrpIeDataTypes.h"
#include "../msgClasses/gtpV2MsgDataTypes.h"

class PgwsNodeLevelLoadControlInformationInDeleteBearerRequest:public GtpV2GroupedIe
{
public:
    PgwsNodeLevelLoadControlInformationInDeleteBearerRequest();
    virtual ~PgwsNodeLevelLoadControlInformationInDeleteBearerRequest();
    bool encodePgwsNodeLevelLoadControlInformationInDeleteBearerRequest(MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData
                              const &data);

    bool decodePgwsNodeLevelLoadControlInformationInDeleteBearerRequest (MsgBuffer &buffer,
                             PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData 
                             & data, Uint16 length);

    void displayPgwsNodeLevelLoadControlInformationInDeleteBearerRequestData_v
    (PgwsNodeLevelLoadControlInformationInDeleteBearerRequestData const &data,
     Debug &stream);

private:
    set <Uint16> mandatoryIeSet;
};

#endif