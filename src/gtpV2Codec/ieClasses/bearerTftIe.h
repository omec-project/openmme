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

#ifndef BEARERTFTIE_H_
#define BEARERTFTIE_H_

#include "manual/gtpV2Ie.h"



class BearerTftIe: public GtpV2Ie {
public:
    BearerTftIe();
    virtual ~BearerTftIe();

    bool encodeBearerTftIe(MsgBuffer &buffer,
                 BearerTftIeData const &data);
    bool decodeBearerTftIe(MsgBuffer &buffer,
                 BearerTftIeData &data, Uint16 length);
    void displayBearerTftIe_v(BearerTftIeData const &data,
                 Debug &stream);
};

#endif /* BEARERTFTIE_H_ */