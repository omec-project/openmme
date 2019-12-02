/*
 * fContainerIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef FCONTAINERIE_H_
#define FCONTAINERIE_H_

#include "manual/gtpV2Ie.h"



class FContainerIe: public GtpV2Ie {
public:
    FContainerIe();
    virtual ~FContainerIe();

    bool encodeFContainerIe(MsgBuffer &buffer,
                 FContainerIeData const &data);
    bool decodeFContainerIe(MsgBuffer &buffer,
                 FContainerIeData &data, Uint16 length);
    void displayFContainerIe_v(FContainerIeData const &data,
                 Debug &stream);
};

#endif /* FCONTAINERIE_H_ */