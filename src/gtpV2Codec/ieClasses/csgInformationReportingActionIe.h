/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef CSGINFORMATIONREPORTINGACTIONIE_H_
#define CSGINFORMATIONREPORTINGACTIONIE_H_

#include "manual/gtpV2Ie.h"



class CsgInformationReportingActionIe: public GtpV2Ie {
public:
    CsgInformationReportingActionIe();
    virtual ~CsgInformationReportingActionIe();

    bool encodeCsgInformationReportingActionIe(MsgBuffer &buffer,
                 CsgInformationReportingActionIeData const &data);
    bool decodeCsgInformationReportingActionIe(MsgBuffer &buffer,
                 CsgInformationReportingActionIeData &data, Uint16 length);
    void displayCsgInformationReportingActionIe_v(CsgInformationReportingActionIeData const &data,
                 Debug &stream);
};

#endif /* CSGINFORMATIONREPORTINGACTIONIE_H_ */