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

#ifndef PDNTYPEIE_H_
#define PDNTYPEIE_H_

#include "manual/gtpV2Ie.h"



class PdnTypeIe: public GtpV2Ie {
public:
    PdnTypeIe();
    virtual ~PdnTypeIe();

    bool encodePdnTypeIe(MsgBuffer &buffer,
                 PdnTypeIeData const &data);
    bool decodePdnTypeIe(MsgBuffer &buffer,
                 PdnTypeIeData &data, Uint16 length);
    void displayPdnTypeIe_v(PdnTypeIeData const &data,
                 Debug &stream);
};

#endif /* PDNTYPEIE_H_ */