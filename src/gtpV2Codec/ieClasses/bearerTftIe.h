/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef BEARERTFTIE_H_
#define BEARERTFTIE_H_

#include "manual/gtpV2Ie.h"



class BearerTftIe: public GtpV2Ie {
public:
    BearerTftIe();
    virtual ~BearerTftIe();

    bool encodeBearerTftIe(MsgBuffer &buffer,
                 BearerTftIeData const &data);
    bool decodeBearerTftIe(MsgBuffer &buffer,
                 BearerTftIeData &data, Uint16 length);
    void displayBearerTftIe_v(BearerTftIeData const &data,
                 Debug &stream);
};

#endif /* BEARERTFTIE_H_ */