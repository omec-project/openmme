/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef EBIIE_H_
#define EBIIE_H_

#include "manual/gtpV2Ie.h"



class EbiIe: public GtpV2Ie {
public:
    EbiIe();
    virtual ~EbiIe();

    bool encodeEbiIe(MsgBuffer &buffer,
                 EbiIeData const &data);
    bool decodeEbiIe(MsgBuffer &buffer,
                 EbiIeData &data, Uint16 length);
    void displayEbiIe_v(EbiIeData const &data,
                 Debug &stream);
};

#endif /* EBIIE_H_ */