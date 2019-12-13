/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef THROTTLINGIE_H_
#define THROTTLINGIE_H_

#include "manual/gtpV2Ie.h"



class ThrottlingIe: public GtpV2Ie {
public:
    ThrottlingIe();
    virtual ~ThrottlingIe();

    bool encodeThrottlingIe(MsgBuffer &buffer,
                 ThrottlingIeData const &data);
    bool decodeThrottlingIe(MsgBuffer &buffer,
                 ThrottlingIeData &data, Uint16 length);
    void displayThrottlingIe_v(ThrottlingIeData const &data,
                 Debug &stream);
};

#endif /* THROTTLINGIE_H_ */