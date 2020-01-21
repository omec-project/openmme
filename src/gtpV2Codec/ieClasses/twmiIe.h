/*
 * twmiIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef TWMIIE_H_
#define TWMIIE_H_

#include "manual/gtpV2Ie.h"



class TwmiIe: public GtpV2Ie {
public:
    TwmiIe();
    virtual ~TwmiIe();

    bool encodeTwmiIe(MsgBuffer &buffer,
                 TwmiIeData const &data);
    bool decodeTwmiIe(MsgBuffer &buffer,
                 TwmiIeData &data, Uint16 length);
    void displayTwmiIe_v(TwmiIeData const &data,
                 Debug &stream);
};

#endif /* TWMIIE_H_ */