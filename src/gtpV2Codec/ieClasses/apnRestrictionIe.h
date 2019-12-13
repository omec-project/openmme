/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef APNRESTRICTIONIE_H_
#define APNRESTRICTIONIE_H_

#include "manual/gtpV2Ie.h"



class ApnRestrictionIe: public GtpV2Ie {
public:
    ApnRestrictionIe();
    virtual ~ApnRestrictionIe();

    bool encodeApnRestrictionIe(MsgBuffer &buffer,
                 ApnRestrictionIeData const &data);
    bool decodeApnRestrictionIe(MsgBuffer &buffer,
                 ApnRestrictionIeData &data, Uint16 length);
    void displayApnRestrictionIe_v(ApnRestrictionIeData const &data,
                 Debug &stream);
};

#endif /* APNRESTRICTIONIE_H_ */