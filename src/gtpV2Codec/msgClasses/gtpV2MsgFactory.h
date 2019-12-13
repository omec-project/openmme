/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef GTPV2MSGFACTORY_H_
#define GTPV2MSGFACTORY_H_

#include <map>
#include "manual/gtpV2Message.h"

class GtpV2MsgFactory {
public:
    GtpV2MsgFactory();
    virtual ~GtpV2MsgFactory();

    static GtpV2MsgFactory& getInstance();
    GtpV2Message& getMsgObject(Uint8 msgType);

private:

    map<Uint8, GtpV2Message*> msgObjectContainer;

};


#endif /* GTPV2MSGFACTORY_H_ */