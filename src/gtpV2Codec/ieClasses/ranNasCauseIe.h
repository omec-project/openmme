/*
 * ranNasCauseIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef RANNASCAUSEIE_H_
#define RANNASCAUSEIE_H_

#include "manual/gtpV2Ie.h"



class RanNasCauseIe: public GtpV2Ie {
public:
    RanNasCauseIe();
    virtual ~RanNasCauseIe();

    bool encodeRanNasCauseIe(MsgBuffer &buffer,
                 RanNasCauseIeData const &data);
    bool decodeRanNasCauseIe(MsgBuffer &buffer,
                 RanNasCauseIeData &data, Uint16 length);
    void displayRanNasCauseIe_v(RanNasCauseIeData const &data,
                 Debug &stream);
};

#endif /* RANNASCAUSEIE_H_ */