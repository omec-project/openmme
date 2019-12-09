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

#ifndef CSGINFORMATIONREPORTINGACTIONIE_H_
#define CSGINFORMATIONREPORTINGACTIONIE_H_

#include "manual/gtpV2Ie.h"



class CsgInformationReportingActionIe: public GtpV2Ie {
public:
    CsgInformationReportingActionIe();
    virtual ~CsgInformationReportingActionIe();

    bool encodeCsgInformationReportingActionIe(MsgBuffer &buffer,
                 CsgInformationReportingActionIeData const &data);
    bool decodeCsgInformationReportingActionIe(MsgBuffer &buffer,
                 CsgInformationReportingActionIeData &data, Uint16 length);
    void displayCsgInformationReportingActionIe_v(CsgInformationReportingActionIeData const &data,
                 Debug &stream);
};

#endif /* CSGINFORMATIONREPORTINGACTIONIE_H_ */