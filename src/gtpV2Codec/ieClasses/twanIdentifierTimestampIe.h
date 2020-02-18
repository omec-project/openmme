/*
 * twanIdentifierTimestampIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef TWANIDENTIFIERTIMESTAMPIE_H_
#define TWANIDENTIFIERTIMESTAMPIE_H_

#include "manual/gtpV2Ie.h"



class TwanIdentifierTimestampIe: public GtpV2Ie {
public:
    TwanIdentifierTimestampIe();
    virtual ~TwanIdentifierTimestampIe();

    bool encodeTwanIdentifierTimestampIe(MsgBuffer &buffer,
                 TwanIdentifierTimestampIeData const &data);
    bool decodeTwanIdentifierTimestampIe(MsgBuffer &buffer,
                 TwanIdentifierTimestampIeData &data, Uint16 length);
    void displayTwanIdentifierTimestampIe_v(TwanIdentifierTimestampIeData const &data,
                 Debug &stream);
};

#endif /* TWANIDENTIFIERTIMESTAMPIE_H_ */