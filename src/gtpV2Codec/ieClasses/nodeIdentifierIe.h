/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef NODEIDENTIFIERIE_H_
#define NODEIDENTIFIERIE_H_

#include "manual/gtpV2Ie.h"



class NodeIdentifierIe: public GtpV2Ie {
public:
    NodeIdentifierIe();
    virtual ~NodeIdentifierIe();

    bool encodeNodeIdentifierIe(MsgBuffer &buffer,
                 NodeIdentifierIeData const &data);
    bool decodeNodeIdentifierIe(MsgBuffer &buffer,
                 NodeIdentifierIeData &data, Uint16 length);
    void displayNodeIdentifierIe_v(NodeIdentifierIeData const &data,
                 Debug &stream);
};

#endif /* NODEIDENTIFIERIE_H_ */