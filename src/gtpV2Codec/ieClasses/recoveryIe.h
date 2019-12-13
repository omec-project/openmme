/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef RECOVERYIE_H_
#define RECOVERYIE_H_

#include "manual/gtpV2Ie.h"



class RecoveryIe: public GtpV2Ie {
public:
    RecoveryIe();
    virtual ~RecoveryIe();

    bool encodeRecoveryIe(MsgBuffer &buffer,
                 RecoveryIeData const &data);
    bool decodeRecoveryIe(MsgBuffer &buffer,
                 RecoveryIeData &data, Uint16 length);
    void displayRecoveryIe_v(RecoveryIeData const &data,
                 Debug &stream);
};

#endif /* RECOVERYIE_H_ */