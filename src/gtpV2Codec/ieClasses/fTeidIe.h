/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef FTEIDIE_H_
#define FTEIDIE_H_

#include "manual/gtpV2Ie.h"



class FTeidIe: public GtpV2Ie {
public:
    FTeidIe();
    virtual ~FTeidIe();

    bool encodeFTeidIe(MsgBuffer &buffer,
                 FTeidIeData const &data);
    bool decodeFTeidIe(MsgBuffer &buffer,
                 FTeidIeData &data, Uint16 length);
    void displayFTeidIe_v(FTeidIeData const &data,
                 Debug &stream);
};

#endif /* FTEIDIE_H_ */