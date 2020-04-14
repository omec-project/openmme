/*
 * ambrIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef AMBRIE_H_
#define AMBRIE_H_

#include "manual/gtpV2Ie.h"



class AmbrIe: public GtpV2Ie {
public:
    AmbrIe();
    virtual ~AmbrIe();

    bool encodeAmbrIe(MsgBuffer &buffer,
                 AmbrIeData const &data);
    bool decodeAmbrIe(MsgBuffer &buffer,
                 AmbrIeData &data, Uint16 length);
    void displayAmbrIe_v(AmbrIeData const &data,
                 Debug &stream);
};

#endif /* AMBRIE_H_ */