/*
 * causeIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef CAUSEIE_H_
#define CAUSEIE_H_

#include "manual/gtpV2Ie.h"



class CauseIe: public GtpV2Ie {
public:
    CauseIe();
    virtual ~CauseIe();

    bool encodeCauseIe(MsgBuffer &buffer,
                 CauseIeData const &data);
    bool decodeCauseIe(MsgBuffer &buffer,
                 CauseIeData &data, Uint16 length);
    void displayCauseIe_v(CauseIeData const &data,
                 Debug &stream);
};

#endif /* CAUSEIE_H_ */