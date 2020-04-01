/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef GTPV2IEFACTORY_H_
#define GTPV2IEFACTORY_H_

#include <map>
#include "manual/gtpV2Ie.h"

class GtpV2IeFactory {
public:
    GtpV2IeFactory();
    virtual ~GtpV2IeFactory();

    static GtpV2IeFactory& getInstance();

    GtpV2Ie& getIeObject(Uint8 ieType);

private:

    map<Uint8, GtpV2Ie*> ieObjectContainer;

};


#endif /* GTPV2MSGFACTORY_H_ */