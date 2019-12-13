/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef AMBRMMBRIE_H_
#define AMBRMMBRIE_H_

#include "manual/gtpV2Ie.h"



class AmbrMmbrIe: public GtpV2Ie {
public:
    AmbrMmbrIe();
    virtual ~AmbrMmbrIe();

    bool encodeAmbrMmbrIe(MsgBuffer &buffer,
                 AmbrMmbrIeData const &data);
    bool decodeAmbrMmbrIe(MsgBuffer &buffer,
                 AmbrMmbrIeData &data, Uint16 length);
    void displayAmbrMmbrIe_v(AmbrMmbrIeData const &data,
                 Debug &stream);
};

#endif /* AMBRMMBRIE_H_ */