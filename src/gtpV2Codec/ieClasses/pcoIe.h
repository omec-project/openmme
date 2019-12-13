/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PCOIE_H_
#define PCOIE_H_

#include "manual/gtpV2Ie.h"



class PcoIe: public GtpV2Ie {
public:
    PcoIe();
    virtual ~PcoIe();

    bool encodePcoIe(MsgBuffer &buffer,
                 PcoIeData const &data);
    bool decodePcoIe(MsgBuffer &buffer,
                 PcoIeData &data, Uint16 length);
    void displayPcoIe_v(PcoIeData const &data,
                 Debug &stream);
};

#endif /* PCOIE_H_ */