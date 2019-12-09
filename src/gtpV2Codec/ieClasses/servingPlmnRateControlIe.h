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

#ifndef SERVINGPLMNRATECONTROLIE_H_
#define SERVINGPLMNRATECONTROLIE_H_

#include "manual/gtpV2Ie.h"



class ServingPlmnRateControlIe: public GtpV2Ie {
public:
    ServingPlmnRateControlIe();
    virtual ~ServingPlmnRateControlIe();

    bool encodeServingPlmnRateControlIe(MsgBuffer &buffer,
                 ServingPlmnRateControlIeData const &data);
    bool decodeServingPlmnRateControlIe(MsgBuffer &buffer,
                 ServingPlmnRateControlIeData &data, Uint16 length);
    void displayServingPlmnRateControlIe_v(ServingPlmnRateControlIeData const &data,
                 Debug &stream);
};

#endif /* SERVINGPLMNRATECONTROLIE_H_ */