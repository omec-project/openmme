/*
 * ratTypeIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef RATTYPEIE_H_
#define RATTYPEIE_H_

#include "manual/gtpV2Ie.h"



class RatTypeIe: public GtpV2Ie {
public:
    RatTypeIe();
    virtual ~RatTypeIe();

    bool encodeRatTypeIe(MsgBuffer &buffer,
                 RatTypeIeData const &data);
    bool decodeRatTypeIe(MsgBuffer &buffer,
                 RatTypeIeData &data, Uint16 length);
    void displayRatTypeIe_v(RatTypeIeData const &data,
                 Debug &stream);
};

#endif /* RATTYPEIE_H_ */