/*
 * delayValueIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef DELAYVALUEIE_H_
#define DELAYVALUEIE_H_

#include "manual/gtpV2Ie.h"



class DelayValueIe: public GtpV2Ie {
public:
    DelayValueIe();
    virtual ~DelayValueIe();

    bool encodeDelayValueIe(MsgBuffer &buffer,
                 DelayValueIeData const &data);
    bool decodeDelayValueIe(MsgBuffer &buffer,
                 DelayValueIeData &data, Uint16 length);
    void displayDelayValueIe_v(DelayValueIeData const &data,
                 Debug &stream);
};

#endif /* DELAYVALUEIE_H_ */