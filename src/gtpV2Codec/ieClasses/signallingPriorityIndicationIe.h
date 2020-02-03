/*
 * signallingPriorityIndicationIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef SIGNALLINGPRIORITYINDICATIONIE_H_
#define SIGNALLINGPRIORITYINDICATIONIE_H_

#include "manual/gtpV2Ie.h"



class SignallingPriorityIndicationIe: public GtpV2Ie {
public:
    SignallingPriorityIndicationIe();
    virtual ~SignallingPriorityIndicationIe();

    bool encodeSignallingPriorityIndicationIe(MsgBuffer &buffer,
                 SignallingPriorityIndicationIeData const &data);
    bool decodeSignallingPriorityIndicationIe(MsgBuffer &buffer,
                 SignallingPriorityIndicationIeData &data, Uint16 length);
    void displaySignallingPriorityIndicationIe_v(SignallingPriorityIndicationIeData const &data,
                 Debug &stream);
};

#endif /* SIGNALLINGPRIORITYINDICATIONIE_H_ */