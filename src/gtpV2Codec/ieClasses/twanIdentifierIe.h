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

#ifndef TWANIDENTIFIERIE_H_
#define TWANIDENTIFIERIE_H_

#include "manual/gtpV2Ie.h"



class TwanIdentifierIe: public GtpV2Ie {
public:
    TwanIdentifierIe();
    virtual ~TwanIdentifierIe();

    bool encodeTwanIdentifierIe(MsgBuffer &buffer,
                 TwanIdentifierIeData const &data);
    bool decodeTwanIdentifierIe(MsgBuffer &buffer,
                 TwanIdentifierIeData &data, Uint16 length);
    void displayTwanIdentifierIe_v(TwanIdentifierIeData const &data,
                 Debug &stream);
};

#endif /* TWANIDENTIFIERIE_H_ */