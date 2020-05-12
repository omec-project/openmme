/*
 * sequenceNumberIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef SEQUENCENUMBERIE_H_
#define SEQUENCENUMBERIE_H_

#include "manual/gtpV2Ie.h"



class SequenceNumberIe: public GtpV2Ie {
public:
    SequenceNumberIe();
    virtual ~SequenceNumberIe();

    bool encodeSequenceNumberIe(MsgBuffer &buffer,
                 SequenceNumberIeData const &data);
    bool decodeSequenceNumberIe(MsgBuffer &buffer,
                 SequenceNumberIeData &data, Uint16 length);
    void displaySequenceNumberIe_v(SequenceNumberIeData const &data,
                 Debug &stream);
};

#endif /* SEQUENCENUMBERIE_H_ */