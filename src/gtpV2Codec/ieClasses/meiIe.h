/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef MEIIE_H_
#define MEIIE_H_

#include "manual/gtpV2Ie.h"



class MeiIe: public GtpV2Ie {
public:
    MeiIe();
    virtual ~MeiIe();

    bool encodeMeiIe(MsgBuffer &buffer,
                 MeiIeData const &data);
    bool decodeMeiIe(MsgBuffer &buffer,
                 MeiIeData &data, Uint16 length);
    void displayMeiIe_v(MeiIeData const &data,
                 Debug &stream);
};

#endif /* MEIIE_H_ */