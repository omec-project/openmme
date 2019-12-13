/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef UPFUNCTIONSELECTIONINDICATIONFLAGSIE_H_
#define UPFUNCTIONSELECTIONINDICATIONFLAGSIE_H_

#include "manual/gtpV2Ie.h"



class UpFunctionSelectionIndicationFlagsIe: public GtpV2Ie {
public:
    UpFunctionSelectionIndicationFlagsIe();
    virtual ~UpFunctionSelectionIndicationFlagsIe();

    bool encodeUpFunctionSelectionIndicationFlagsIe(MsgBuffer &buffer,
                 UpFunctionSelectionIndicationFlagsIeData const &data);
    bool decodeUpFunctionSelectionIndicationFlagsIe(MsgBuffer &buffer,
                 UpFunctionSelectionIndicationFlagsIeData &data, Uint16 length);
    void displayUpFunctionSelectionIndicationFlagsIe_v(UpFunctionSelectionIndicationFlagsIeData const &data,
                 Debug &stream);
};

#endif /* UPFUNCTIONSELECTIONINDICATIONFLAGSIE_H_ */