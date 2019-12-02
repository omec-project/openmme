/*
 * arpIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef ARPIE_H_
#define ARPIE_H_

#include "manual/gtpV2Ie.h"



class ArpIe: public GtpV2Ie {
public:
    ArpIe();
    virtual ~ArpIe();

    bool encodeArpIe(MsgBuffer &buffer,
                 ArpIeData const &data);
    bool decodeArpIe(MsgBuffer &buffer,
                 ArpIeData &data, Uint16 length);
    void displayArpIe_v(ArpIeData const &data,
                 Debug &stream);
};

#endif /* ARPIE_H_ */