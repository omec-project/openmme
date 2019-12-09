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

#ifndef UETIMEZONEIE_H_
#define UETIMEZONEIE_H_

#include "manual/gtpV2Ie.h"



class UeTimeZoneIe: public GtpV2Ie {
public:
    UeTimeZoneIe();
    virtual ~UeTimeZoneIe();

    bool encodeUeTimeZoneIe(MsgBuffer &buffer,
                 UeTimeZoneIeData const &data);
    bool decodeUeTimeZoneIe(MsgBuffer &buffer,
                 UeTimeZoneIeData &data, Uint16 length);
    void displayUeTimeZoneIe_v(UeTimeZoneIeData const &data,
                 Debug &stream);
};

#endif /* UETIMEZONEIE_H_ */