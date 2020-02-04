/*
 * twanIdentifierIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef TWANIDENTIFIERIE_H_
#define TWANIDENTIFIERIE_H_

#include "manual/gtpV2Ie.h"



class TwanIdentifierIe: public GtpV2Ie {
public:
    TwanIdentifierIe();
    virtual ~TwanIdentifierIe();

    bool encodeTwanIdentifierIe(MsgBuffer &buffer,
                 TwanIdentifierIeData const &data);
    bool decodeTwanIdentifierIe(MsgBuffer &buffer,
                 TwanIdentifierIeData &data, Uint16 length);
    void displayTwanIdentifierIe_v(TwanIdentifierIeData const &data,
                 Debug &stream);
};

#endif /* TWANIDENTIFIERIE_H_ */