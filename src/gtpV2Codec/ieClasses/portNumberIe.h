/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PORTNUMBERIE_H_
#define PORTNUMBERIE_H_

#include "manual/gtpV2Ie.h"



class PortNumberIe: public GtpV2Ie {
public:
    PortNumberIe();
    virtual ~PortNumberIe();

    bool encodePortNumberIe(MsgBuffer &buffer,
                 PortNumberIeData const &data);
    bool decodePortNumberIe(MsgBuffer &buffer,
                 PortNumberIeData &data, Uint16 length);
    void displayPortNumberIe_v(PortNumberIeData const &data,
                 Debug &stream);
};

#endif /* PORTNUMBERIE_H_ */