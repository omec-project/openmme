/*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 

#ifndef PAGINGANDSERVICEINFORMATIONIE_H_
#define PAGINGANDSERVICEINFORMATIONIE_H_

#include "manual/gtpV2Ie.h"



class PagingAndServiceInformationIe: public GtpV2Ie {
public:
    PagingAndServiceInformationIe();
    virtual ~PagingAndServiceInformationIe();

    bool encodePagingAndServiceInformationIe(MsgBuffer &buffer,
                 PagingAndServiceInformationIeData const &data);
    bool decodePagingAndServiceInformationIe(MsgBuffer &buffer,
                 PagingAndServiceInformationIeData &data, Uint16 length);
    void displayPagingAndServiceInformationIe_v(PagingAndServiceInformationIeData const &data,
                 Debug &stream);
};

#endif /* PAGINGANDSERVICEINFORMATIONIE_H_ */