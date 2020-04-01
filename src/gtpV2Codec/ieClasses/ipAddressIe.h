/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef IPADDRESSIE_H_
#define IPADDRESSIE_H_

#include "manual/gtpV2Ie.h"



class IpAddressIe: public GtpV2Ie {
public:
    IpAddressIe();
    virtual ~IpAddressIe();

    bool encodeIpAddressIe(MsgBuffer &buffer,
                 IpAddressIeData const &data);
    bool decodeIpAddressIe(MsgBuffer &buffer,
                 IpAddressIeData &data, Uint16 length);
    void displayIpAddressIe_v(IpAddressIeData const &data,
                 Debug &stream);
};

#endif /* IPADDRESSIE_H_ */