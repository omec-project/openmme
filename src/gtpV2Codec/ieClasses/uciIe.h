/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef UCIIE_H_
#define UCIIE_H_

#include "manual/gtpV2Ie.h"



class UciIe: public GtpV2Ie {
public:
    UciIe();
    virtual ~UciIe();

    bool encodeUciIe(MsgBuffer &buffer,
                 UciIeData const &data);
    bool decodeUciIe(MsgBuffer &buffer,
                 UciIeData &data, Uint16 length);
    void displayUciIe_v(UciIeData const &data,
                 Debug &stream);
};

#endif /* UCIIE_H_ */