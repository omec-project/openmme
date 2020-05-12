/*
 * traceInformationIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef TRACEINFORMATIONIE_H_
#define TRACEINFORMATIONIE_H_

#include "manual/gtpV2Ie.h"



class TraceInformationIe: public GtpV2Ie {
public:
    TraceInformationIe();
    virtual ~TraceInformationIe();

    bool encodeTraceInformationIe(MsgBuffer &buffer,
                 TraceInformationIeData const &data);
    bool decodeTraceInformationIe(MsgBuffer &buffer,
                 TraceInformationIeData &data, Uint16 length);
    void displayTraceInformationIe_v(TraceInformationIeData const &data,
                 Debug &stream);
};

#endif /* TRACEINFORMATIONIE_H_ */