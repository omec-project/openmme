/*
 * pdnTypeIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef PDNTYPEIE_H_
#define PDNTYPEIE_H_

#include "manual/gtpV2Ie.h"



class PdnTypeIe: public GtpV2Ie {
public:
    PdnTypeIe();
    virtual ~PdnTypeIe();

    bool encodePdnTypeIe(MsgBuffer &buffer,
                 PdnTypeIeData const &data);
    bool decodePdnTypeIe(MsgBuffer &buffer,
                 PdnTypeIeData &data, Uint16 length);
    void displayPdnTypeIe_v(PdnTypeIeData const &data,
                 Debug &stream);
};

#endif /* PDNTYPEIE_H_ */