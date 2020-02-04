/*
 * apnAndRelativeCapacityIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef APNANDRELATIVECAPACITYIE_H_
#define APNANDRELATIVECAPACITYIE_H_

#include "manual/gtpV2Ie.h"



class ApnAndRelativeCapacityIe: public GtpV2Ie {
public:
    ApnAndRelativeCapacityIe();
    virtual ~ApnAndRelativeCapacityIe();

    bool encodeApnAndRelativeCapacityIe(MsgBuffer &buffer,
                 ApnAndRelativeCapacityIeData const &data);
    bool decodeApnAndRelativeCapacityIe(MsgBuffer &buffer,
                 ApnAndRelativeCapacityIeData &data, Uint16 length);
    void displayApnAndRelativeCapacityIe_v(ApnAndRelativeCapacityIeData const &data,
                 Debug &stream);
};

#endif /* APNANDRELATIVECAPACITYIE_H_ */