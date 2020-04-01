/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef NODETYPEIE_H_
#define NODETYPEIE_H_

#include "manual/gtpV2Ie.h"



class NodeTypeIe: public GtpV2Ie {
public:
    NodeTypeIe();
    virtual ~NodeTypeIe();

    bool encodeNodeTypeIe(MsgBuffer &buffer,
                 NodeTypeIeData const &data);
    bool decodeNodeTypeIe(MsgBuffer &buffer,
                 NodeTypeIeData &data, Uint16 length);
    void displayNodeTypeIe_v(NodeTypeIeData const &data,
                 Debug &stream);
};

#endif /* NODETYPEIE_H_ */