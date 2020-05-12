/*
 * counterIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef COUNTERIE_H_
#define COUNTERIE_H_

#include "manual/gtpV2Ie.h"



class CounterIe: public GtpV2Ie {
public:
    CounterIe();
    virtual ~CounterIe();

    bool encodeCounterIe(MsgBuffer &buffer,
                 CounterIeData const &data);
    bool decodeCounterIe(MsgBuffer &buffer,
                 CounterIeData &data, Uint16 length);
    void displayCounterIe_v(CounterIeData const &data,
                 Debug &stream);
};

#endif /* COUNTERIE_H_ */