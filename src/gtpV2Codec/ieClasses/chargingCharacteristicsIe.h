/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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