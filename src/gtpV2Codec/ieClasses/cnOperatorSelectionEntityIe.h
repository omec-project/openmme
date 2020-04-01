/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef CNOPERATORSELECTIONENTITYIE_H_
#define CNOPERATORSELECTIONENTITYIE_H_

#include "manual/gtpV2Ie.h"



class CnOperatorSelectionEntityIe: public GtpV2Ie {
public:
    CnOperatorSelectionEntityIe();
    virtual ~CnOperatorSelectionEntityIe();

    bool encodeCnOperatorSelectionEntityIe(MsgBuffer &buffer,
                 CnOperatorSelectionEntityIeData const &data);
    bool decodeCnOperatorSelectionEntityIe(MsgBuffer &buffer,
                 CnOperatorSelectionEntityIeData &data, Uint16 length);
    void displayCnOperatorSelectionEntityIe_v(CnOperatorSelectionEntityIeData const &data,
                 Debug &stream);
};

#endif /* CNOPERATORSELECTIONENTITYIE_H_ */