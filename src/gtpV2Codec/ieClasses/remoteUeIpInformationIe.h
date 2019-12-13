/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef REMOTEUEIPINFORMATIONIE_H_
#define REMOTEUEIPINFORMATIONIE_H_

#include "manual/gtpV2Ie.h"



class RemoteUeIpInformationIe: public GtpV2Ie {
public:
    RemoteUeIpInformationIe();
    virtual ~RemoteUeIpInformationIe();

    bool encodeRemoteUeIpInformationIe(MsgBuffer &buffer,
                 RemoteUeIpInformationIeData const &data);
    bool decodeRemoteUeIpInformationIe(MsgBuffer &buffer,
                 RemoteUeIpInformationIeData &data, Uint16 length);
    void displayRemoteUeIpInformationIe_v(RemoteUeIpInformationIeData const &data,
                 Debug &stream);
};

#endif /* REMOTEUEIPINFORMATIONIE_H_ */