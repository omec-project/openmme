/*
 * localDistinguishedNameIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef LOCALDISTINGUISHEDNAMEIE_H_
#define LOCALDISTINGUISHEDNAMEIE_H_

#include "manual/gtpV2Ie.h"



class LocalDistinguishedNameIe: public GtpV2Ie {
public:
    LocalDistinguishedNameIe();
    virtual ~LocalDistinguishedNameIe();

    bool encodeLocalDistinguishedNameIe(MsgBuffer &buffer,
                 LocalDistinguishedNameIeData const &data);
    bool decodeLocalDistinguishedNameIe(MsgBuffer &buffer,
                 LocalDistinguishedNameIeData &data, Uint16 length);
    void displayLocalDistinguishedNameIe_v(LocalDistinguishedNameIeData const &data,
                 Debug &stream);
};

#endif /* LOCALDISTINGUISHEDNAMEIE_H_ */