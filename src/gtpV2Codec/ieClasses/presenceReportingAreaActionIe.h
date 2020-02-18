/*
 * presenceReportingAreaActionIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef PRESENCEREPORTINGAREAACTIONIE_H_
#define PRESENCEREPORTINGAREAACTIONIE_H_

#include "manual/gtpV2Ie.h"



class PresenceReportingAreaActionIe: public GtpV2Ie {
public:
    PresenceReportingAreaActionIe();
    virtual ~PresenceReportingAreaActionIe();

    bool encodePresenceReportingAreaActionIe(MsgBuffer &buffer,
                 PresenceReportingAreaActionIeData const &data);
    bool decodePresenceReportingAreaActionIe(MsgBuffer &buffer,
                 PresenceReportingAreaActionIeData &data, Uint16 length);
    void displayPresenceReportingAreaActionIe_v(PresenceReportingAreaActionIeData const &data,
                 Debug &stream);
};

#endif /* PRESENCEREPORTINGAREAACTIONIE_H_ */