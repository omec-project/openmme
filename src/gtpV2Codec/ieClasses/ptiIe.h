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

#ifndef PTIIE_H_
#define PTIIE_H_

#include "manual/gtpV2Ie.h"



class PtiIe: public GtpV2Ie {
public:
    PtiIe();
    virtual ~PtiIe();

    bool encodePtiIe(MsgBuffer &buffer,
                 PtiIeData const &data);
    bool decodePtiIe(MsgBuffer &buffer,
                 PtiIeData &data, Uint16 length);
    void displayPtiIe_v(PtiIeData const &data,
                 Debug &stream);
};

#endif /* PTIIE_H_ */