/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef RANNASCAUSEIE_H_
#define RANNASCAUSEIE_H_

#include "manual/gtpV2Ie.h"



class RanNasCauseIe: public GtpV2Ie {
public:
    RanNasCauseIe();
    virtual ~RanNasCauseIe();

    bool encodeRanNasCauseIe(MsgBuffer &buffer,
                 RanNasCauseIeData const &data);
    bool decodeRanNasCauseIe(MsgBuffer &buffer,
                 RanNasCauseIeData &data, Uint16 length);
    void displayRanNasCauseIe_v(RanNasCauseIeData const &data,
                 Debug &stream);
};

#endif /* RANNASCAUSEIE_H_ */