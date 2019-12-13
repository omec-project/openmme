/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef CHANGEREPORTINGACTIONIE_H_
#define CHANGEREPORTINGACTIONIE_H_

#include "manual/gtpV2Ie.h"



class ChangeReportingActionIe: public GtpV2Ie {
public:
    ChangeReportingActionIe();
    virtual ~ChangeReportingActionIe();

    bool encodeChangeReportingActionIe(MsgBuffer &buffer,
                 ChangeReportingActionIeData const &data);
    bool decodeChangeReportingActionIe(MsgBuffer &buffer,
                 ChangeReportingActionIeData &data, Uint16 length);
    void displayChangeReportingActionIe_v(ChangeReportingActionIeData const &data,
                 Debug &stream);
};

#endif /* CHANGEREPORTINGACTIONIE_H_ */