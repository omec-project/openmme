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

#ifndef CHARGINGCHARACTERISTICSIE_H_
#define CHARGINGCHARACTERISTICSIE_H_

#include "manual/gtpV2Ie.h"



class ChargingCharacteristicsIe: public GtpV2Ie {
public:
    ChargingCharacteristicsIe();
    virtual ~ChargingCharacteristicsIe();

    bool encodeChargingCharacteristicsIe(MsgBuffer &buffer,
                 ChargingCharacteristicsIeData const &data);
    bool decodeChargingCharacteristicsIe(MsgBuffer &buffer,
                 ChargingCharacteristicsIeData &data, Uint16 length);
    void displayChargingCharacteristicsIe_v(ChargingCharacteristicsIeData const &data,
                 Debug &stream);
};

#endif /* CHARGINGCHARACTERISTICSIE_H_ */