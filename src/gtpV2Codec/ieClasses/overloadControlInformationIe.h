/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef OVERLOADCONTROLINFORMATIONIE_H_
#define OVERLOADCONTROLINFORMATIONIE_H_

#include <map>
#include "manual/gtpV2Ie.h"
#include "manual/gtpV2GroupedIe.h"
#include "gtpV2DataTypes.h"

class OverloadControlInformationIe:public GtpV2Ie
{
public:
    OverloadControlInformationIe ();
    virtual ~ OverloadControlInformationIe ();

    GtpV2GroupedIe & getGroupedIe (Uint8 msgType, Uint8 instance);
    void insertGroupedIeObject (Uint8 msgType, Uint8 instance,
                GtpV2GroupedIe * grpIe_p);

private:
    map < Uint16, GtpV2GroupedIe * >groupedIeObjectContainer;   // map[msgType || instance]
};

#endif
