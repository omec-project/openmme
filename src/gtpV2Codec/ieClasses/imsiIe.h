/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef IMSIIE_H_
#define IMSIIE_H_

#include "manual/gtpV2Ie.h"



class ImsiIe: public GtpV2Ie {
public:
    ImsiIe();
    virtual ~ImsiIe();

    bool encodeImsiIe(MsgBuffer &buffer,
                 ImsiIeData const &data);
    bool decodeImsiIe(MsgBuffer &buffer,
                 ImsiIeData &data, Uint16 length);
    void displayImsiIe_v(ImsiIeData const &data,
                 Debug &stream);
};

#endif /* IMSIIE_H_ */