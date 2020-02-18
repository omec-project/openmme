/*
 * ptiIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef PTIIE_H_
#define PTIIE_H_

#include "manual/gtpV2Ie.h"



class PtiIe: public GtpV2Ie {
public:
    PtiIe();
    virtual ~PtiIe();

    bool encodePtiIe(MsgBuffer &buffer,
                 PtiIeData const &data);
    bool decodePtiIe(MsgBuffer &buffer,
                 PtiIeData &data, Uint16 length);
    void displayPtiIe_v(PtiIeData const &data,
                 Debug &stream);
};

#endif /* PTIIE_H_ */