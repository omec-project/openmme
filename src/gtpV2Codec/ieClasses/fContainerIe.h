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

#ifndef FCONTAINERIE_H_
#define FCONTAINERIE_H_

#include "manual/gtpV2Ie.h"



class FContainerIe: public GtpV2Ie {
public:
    FContainerIe();
    virtual ~FContainerIe();

    bool encodeFContainerIe(MsgBuffer &buffer,
                 FContainerIeData const &data);
    bool decodeFContainerIe(MsgBuffer &buffer,
                 FContainerIeData &data, Uint16 length);
    void displayFContainerIe_v(FContainerIeData const &data,
                 Debug &stream);
};

#endif /* FCONTAINERIE_H_ */