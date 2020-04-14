/*
 * uliTimestampIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef ULITIMESTAMPIE_H_
#define ULITIMESTAMPIE_H_

#include "manual/gtpV2Ie.h"



class UliTimestampIe: public GtpV2Ie {
public:
    UliTimestampIe();
    virtual ~UliTimestampIe();

    bool encodeUliTimestampIe(MsgBuffer &buffer,
                 UliTimestampIeData const &data);
    bool decodeUliTimestampIe(MsgBuffer &buffer,
                 UliTimestampIeData &data, Uint16 length);
    void displayUliTimestampIe_v(UliTimestampIeData const &data,
                 Debug &stream);
};

#endif /* ULITIMESTAMPIE_H_ */