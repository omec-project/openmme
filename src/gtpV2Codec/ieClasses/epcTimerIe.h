/*
 * epcTimerIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef EPCTIMERIE_H_
#define EPCTIMERIE_H_

#include "manual/gtpV2Ie.h"



class EpcTimerIe: public GtpV2Ie {
public:
    EpcTimerIe();
    virtual ~EpcTimerIe();

    bool encodeEpcTimerIe(MsgBuffer &buffer,
                 EpcTimerIeData const &data);
    bool decodeEpcTimerIe(MsgBuffer &buffer,
                 EpcTimerIeData &data, Uint16 length);
    void displayEpcTimerIe_v(EpcTimerIeData const &data,
                 Debug &stream);
};

#endif /* EPCTIMERIE_H_ */