/*
 * millisecondTimeStampIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef MILLISECONDTIMESTAMPIE_H_
#define MILLISECONDTIMESTAMPIE_H_

#include "manual/gtpV2Ie.h"



class MillisecondTimeStampIe: public GtpV2Ie {
public:
    MillisecondTimeStampIe();
    virtual ~MillisecondTimeStampIe();

    bool encodeMillisecondTimeStampIe(MsgBuffer &buffer,
                 MillisecondTimeStampIeData const &data);
    bool decodeMillisecondTimeStampIe(MsgBuffer &buffer,
                 MillisecondTimeStampIeData &data, Uint16 length);
    void displayMillisecondTimeStampIe_v(MillisecondTimeStampIeData const &data,
                 Debug &stream);
};

#endif /* MILLISECONDTIMESTAMPIE_H_ */