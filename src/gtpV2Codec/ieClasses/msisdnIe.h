/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef MSISDNIE_H_
#define MSISDNIE_H_

#include "manual/gtpV2Ie.h"



class MsisdnIe: public GtpV2Ie {
public:
    MsisdnIe();
    virtual ~MsisdnIe();

    bool encodeMsisdnIe(MsgBuffer &buffer,
                 MsisdnIeData const &data);
    bool decodeMsisdnIe(MsgBuffer &buffer,
                 MsisdnIeData &data, Uint16 length);
    void displayMsisdnIe_v(MsisdnIeData const &data,
                 Debug &stream);
};

#endif /* MSISDNIE_H_ */