/*
 * secondaryRatUsageDataReportIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef SECONDARYRATUSAGEDATAREPORTIE_H_
#define SECONDARYRATUSAGEDATAREPORTIE_H_

#include "manual/gtpV2Ie.h"



class SecondaryRatUsageDataReportIe: public GtpV2Ie {
public:
    SecondaryRatUsageDataReportIe();
    virtual ~SecondaryRatUsageDataReportIe();

    bool encodeSecondaryRatUsageDataReportIe(MsgBuffer &buffer,
                 SecondaryRatUsageDataReportIeData const &data);
    bool decodeSecondaryRatUsageDataReportIe(MsgBuffer &buffer,
                 SecondaryRatUsageDataReportIeData &data, Uint16 length);
    void displaySecondaryRatUsageDataReportIe_v(SecondaryRatUsageDataReportIeData const &data,
                 Debug &stream);
};

#endif /* SECONDARYRATUSAGEDATAREPORTIE_H_ */