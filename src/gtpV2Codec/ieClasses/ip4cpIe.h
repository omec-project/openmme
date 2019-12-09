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

#ifndef IP4CPIE_H_
#define IP4CPIE_H_

#include "manual/gtpV2Ie.h"



class Ip4cpIe: public GtpV2Ie {
public:
    Ip4cpIe();
    virtual ~Ip4cpIe();

    bool encodeIp4cpIe(MsgBuffer &buffer,
                 Ip4cpIeData const &data);
    bool decodeIp4cpIe(MsgBuffer &buffer,
                 Ip4cpIeData &data, Uint16 length);
    void displayIp4cpIe_v(Ip4cpIeData const &data,
                 Debug &stream);
};

#endif /* IP4CPIE_H_ */