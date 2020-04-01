/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef METRICIE_H_
#define METRICIE_H_

#include "manual/gtpV2Ie.h"



class MetricIe: public GtpV2Ie {
public:
    MetricIe();
    virtual ~MetricIe();

    bool encodeMetricIe(MsgBuffer &buffer,
                 MetricIeData const &data);
    bool decodeMetricIe(MsgBuffer &buffer,
                 MetricIeData &data, Uint16 length);
    void displayMetricIe_v(MetricIeData const &data,
                 Debug &stream);
};

#endif /* METRICIE_H_ */