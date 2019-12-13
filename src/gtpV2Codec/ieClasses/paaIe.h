/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PAAIE_H_
#define PAAIE_H_

#include "manual/gtpV2Ie.h"



class PaaIe: public GtpV2Ie {
public:
    PaaIe();
    virtual ~PaaIe();

    bool encodePaaIe(MsgBuffer &buffer,
                 PaaIeData const &data);
    bool decodePaaIe(MsgBuffer &buffer,
                 PaaIeData &data, Uint16 length);
    void displayPaaIe_v(PaaIeData const &data,
                 Debug &stream);
};

#endif /* PAAIE_H_ */