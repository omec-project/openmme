/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef EPCOIE_H_
#define EPCOIE_H_

#include "manual/gtpV2Ie.h"



class EpcoIe: public GtpV2Ie {
public:
    EpcoIe();
    virtual ~EpcoIe();

    bool encodeEpcoIe(MsgBuffer &buffer,
                 EpcoIeData const &data);
    bool decodeEpcoIe(MsgBuffer &buffer,
                 EpcoIeData &data, Uint16 length);
    void displayEpcoIe_v(EpcoIeData const &data,
                 Debug &stream);
};

#endif /* EPCOIE_H_ */