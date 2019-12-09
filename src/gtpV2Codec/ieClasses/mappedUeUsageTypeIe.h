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

#ifndef MAPPEDUEUSAGETYPEIE_H_
#define MAPPEDUEUSAGETYPEIE_H_

#include "manual/gtpV2Ie.h"



class MappedUeUsageTypeIe: public GtpV2Ie {
public:
    MappedUeUsageTypeIe();
    virtual ~MappedUeUsageTypeIe();

    bool encodeMappedUeUsageTypeIe(MsgBuffer &buffer,
                 MappedUeUsageTypeIeData const &data);
    bool decodeMappedUeUsageTypeIe(MsgBuffer &buffer,
                 MappedUeUsageTypeIeData &data, Uint16 length);
    void displayMappedUeUsageTypeIe_v(MappedUeUsageTypeIeData const &data,
                 Debug &stream);
};

#endif /* MAPPEDUEUSAGETYPEIE_H_ */