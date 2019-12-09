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

#ifndef FQDNIE_H_
#define FQDNIE_H_

#include "manual/gtpV2Ie.h"



class FqdnIe: public GtpV2Ie {
public:
    FqdnIe();
    virtual ~FqdnIe();

    bool encodeFqdnIe(MsgBuffer &buffer,
                 FqdnIeData const &data);
    bool decodeFqdnIe(MsgBuffer &buffer,
                 FqdnIeData &data, Uint16 length);
    void displayFqdnIe_v(FqdnIeData const &data,
                 Debug &stream);
};

#endif /* FQDNIE_H_ */