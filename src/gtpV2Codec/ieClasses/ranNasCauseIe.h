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

#ifndef RANNASCAUSEIE_H_
#define RANNASCAUSEIE_H_

#include "manual/gtpV2Ie.h"



class RanNasCauseIe: public GtpV2Ie {
public:
    RanNasCauseIe();
    virtual ~RanNasCauseIe();

    bool encodeRanNasCauseIe(MsgBuffer &buffer,
                 RanNasCauseIeData const &data);
    bool decodeRanNasCauseIe(MsgBuffer &buffer,
                 RanNasCauseIeData &data, Uint16 length);
    void displayRanNasCauseIe_v(RanNasCauseIeData const &data,
                 Debug &stream);
};

#endif /* RANNASCAUSEIE_H_ */