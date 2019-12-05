/*
 * indicationIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef INDICATIONIE_H_
#define INDICATIONIE_H_

#include "manual/gtpV2Ie.h"



class IndicationIe: public GtpV2Ie {
public:
    IndicationIe();
    virtual ~IndicationIe();

    bool encodeIndicationIe(MsgBuffer &buffer,
                 IndicationIeData const &data);
    bool decodeIndicationIe(MsgBuffer &buffer,
                 IndicationIeData &data, Uint16 length);
    void displayIndicationIe_v(IndicationIeData const &data,
                 Debug &stream);
};

#endif /* INDICATIONIE_H_ */