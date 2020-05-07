/*
 * uliIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef ULIIE_H_
#define ULIIE_H_

#include "manual/gtpV2Ie.h"



class UliIe: public GtpV2Ie {
public:
    UliIe();
    virtual ~UliIe();

    bool encodeUliIe(MsgBuffer &buffer,
                 UliIeData const &data);
    bool decodeUliIe(MsgBuffer &buffer,
                 UliIeData &data, Uint16 length);
    void displayUliIe_v(UliIeData const &data,
                 Debug &stream);
};

#endif /* ULIIE_H_ */