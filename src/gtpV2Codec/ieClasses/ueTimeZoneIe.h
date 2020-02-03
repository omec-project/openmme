/*
 * ueTimeZoneIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef UETIMEZONEIE_H_
#define UETIMEZONEIE_H_

#include "manual/gtpV2Ie.h"



class UeTimeZoneIe: public GtpV2Ie {
public:
    UeTimeZoneIe();
    virtual ~UeTimeZoneIe();

    bool encodeUeTimeZoneIe(MsgBuffer &buffer,
                 UeTimeZoneIeData const &data);
    bool decodeUeTimeZoneIe(MsgBuffer &buffer,
                 UeTimeZoneIeData &data, Uint16 length);
    void displayUeTimeZoneIe_v(UeTimeZoneIeData const &data,
                 Debug &stream);
};

#endif /* UETIMEZONEIE_H_ */