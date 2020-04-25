/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PERMDATABLOCK_H_
#define PERMDATABLOCK_H_

namespace SM
{
class PermDataBlock
{
   public:
      PermDataBlock();
      virtual ~PermDataBlock();
      virtual void display();
      
   private:
      // Add permanant data fields here
      unsigned int contextID;
};
}

#endif /* PERMDATABLOCK_H_ */
