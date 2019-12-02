/*
 * henbInformationReportingIe.h
 *
 *  Revisit Header later
 *      Author: hariharanb
 */

#ifndef HENBINFORMATIONREPORTINGIE_H_
#define HENBINFORMATIONREPORTINGIE_H_

#include "manual/gtpV2Ie.h"



class HenbInformationReportingIe: public GtpV2Ie {
public:
    HenbInformationReportingIe();
    virtual ~HenbInformationReportingIe();

    bool encodeHenbInformationReportingIe(MsgBuffer &buffer,
                 HenbInformationReportingIeData const &data);
    bool decodeHenbInformationReportingIe(MsgBuffer &buffer,
                 HenbInformationReportingIeData &data, Uint16 length);
    void displayHenbInformationReportingIe_v(HenbInformationReportingIeData const &data,
                 Debug &stream);
};

#endif /* HENBINFORMATIONREPORTINGIE_H_ */