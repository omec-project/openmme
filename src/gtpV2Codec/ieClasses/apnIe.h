/*
 * apnIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef APNIE_H_
#define APNIE_H_

#include "manual/gtpV2Ie.h"



class ApnIe: public GtpV2Ie {
public:
    ApnIe();
    virtual ~ApnIe();

    bool encodeApnIe(MsgBuffer &buffer,
                 ApnIeData const &data);
    bool decodeApnIe(MsgBuffer &buffer,
                 ApnIeData &data, Uint16 length);
    void displayApnIe_v(ApnIeData const &data,
                 Debug &stream);
};

#endif /* APNIE_H_ */