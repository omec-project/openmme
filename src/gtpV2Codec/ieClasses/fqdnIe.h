/*
 * fqdnIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef FQDNIE_H_
#define FQDNIE_H_

#include "manual/gtpV2Ie.h"



class FqdnIe: public GtpV2Ie {
public:
    FqdnIe();
    virtual ~FqdnIe();

    bool encodeFqdnIe(MsgBuffer &buffer,
                 FqdnIeData const &data);
    bool decodeFqdnIe(MsgBuffer &buffer,
                 FqdnIeData &data, Uint16 length);
    void displayFqdnIe_v(FqdnIeData const &data,
                 Debug &stream);
};

#endif /* FQDNIE_H_ */