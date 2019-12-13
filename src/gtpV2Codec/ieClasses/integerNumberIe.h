/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef INTEGERNUMBERIE_H_
#define INTEGERNUMBERIE_H_

#include "manual/gtpV2Ie.h"



class IntegerNumberIe: public GtpV2Ie {
public:
    IntegerNumberIe();
    virtual ~IntegerNumberIe();

    bool encodeIntegerNumberIe(MsgBuffer &buffer,
                 IntegerNumberIeData const &data);
    bool decodeIntegerNumberIe(MsgBuffer &buffer,
                 IntegerNumberIeData &data, Uint16 length);
    void displayIntegerNumberIe_v(IntegerNumberIeData const &data,
                 Debug &stream);
};

#endif /* INTEGERNUMBERIE_H_ */