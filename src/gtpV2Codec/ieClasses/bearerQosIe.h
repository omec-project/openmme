/*
 * bearerQosIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef BEARERQOSIE_H_
#define BEARERQOSIE_H_

#include "manual/gtpV2Ie.h"



class BearerQosIe: public GtpV2Ie {
public:
    BearerQosIe();
    virtual ~BearerQosIe();

    bool encodeBearerQosIe(MsgBuffer &buffer,
                 BearerQosIeData const &data);
    bool decodeBearerQosIe(MsgBuffer &buffer,
                 BearerQosIeData &data, Uint16 length);
    void displayBearerQosIe_v(BearerQosIeData const &data,
                 Debug &stream);
};

#endif /* BEARERQOSIE_H_ */