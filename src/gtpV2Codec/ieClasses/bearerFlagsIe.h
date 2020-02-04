/*
 * bearerFlagsIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef BEARERFLAGSIE_H_
#define BEARERFLAGSIE_H_

#include "manual/gtpV2Ie.h"



class BearerFlagsIe: public GtpV2Ie {
public:
    BearerFlagsIe();
    virtual ~BearerFlagsIe();

    bool encodeBearerFlagsIe(MsgBuffer &buffer,
                 BearerFlagsIeData const &data);
    bool decodeBearerFlagsIe(MsgBuffer &buffer,
                 BearerFlagsIeData &data, Uint16 length);
    void displayBearerFlagsIe_v(BearerFlagsIeData const &data,
                 Debug &stream);
};

#endif /* BEARERFLAGSIE_H_ */