/*
 * chargingIdIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef CHARGINGIDIE_H_
#define CHARGINGIDIE_H_

#include "manual/gtpV2Ie.h"



class ChargingIdIe: public GtpV2Ie {
public:
    ChargingIdIe();
    virtual ~ChargingIdIe();

    bool encodeChargingIdIe(MsgBuffer &buffer,
                 ChargingIdIeData const &data);
    bool decodeChargingIdIe(MsgBuffer &buffer,
                 ChargingIdIeData &data, Uint16 length);
    void displayChargingIdIe_v(ChargingIdIeData const &data,
                 Debug &stream);
};

#endif /* CHARGINGIDIE_H_ */