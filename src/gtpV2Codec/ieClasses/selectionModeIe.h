/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef SELECTIONMODEIE_H_
#define SELECTIONMODEIE_H_

#include "manual/gtpV2Ie.h"



class SelectionModeIe: public GtpV2Ie {
public:
    SelectionModeIe();
    virtual ~SelectionModeIe();

    bool encodeSelectionModeIe(MsgBuffer &buffer,
                 SelectionModeIeData const &data);
    bool decodeSelectionModeIe(MsgBuffer &buffer,
                 SelectionModeIeData &data, Uint16 length);
    void displaySelectionModeIe_v(SelectionModeIeData const &data,
                 Debug &stream);
};

#endif /* SELECTIONMODEIE_H_ */