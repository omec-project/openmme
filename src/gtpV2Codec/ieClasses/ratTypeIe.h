/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef RATTYPEIE_H_
#define RATTYPEIE_H_

#include "manual/gtpV2Ie.h"



class RatTypeIe: public GtpV2Ie {
public:
    RatTypeIe();
    virtual ~RatTypeIe();

    bool encodeRatTypeIe(MsgBuffer &buffer,
                 RatTypeIeData const &data);
    bool decodeRatTypeIe(MsgBuffer &buffer,
                 RatTypeIeData &data, Uint16 length);
    void displayRatTypeIe_v(RatTypeIeData const &data,
                 Debug &stream);
};

#endif /* RATTYPEIE_H_ */