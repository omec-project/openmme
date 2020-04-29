/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TEMPDATABLOCK_H_
#define TEMPDATABLOCK_H_

namespace SM
{
class State;
class TempDataBlock
{
   public:
      TempDataBlock();
      virtual ~TempDataBlock();

      virtual void display();

      State* getCurrentState();
      void setNextState(State* state);

      TempDataBlock* getNextTempDataBlock();
      void setNextTempDataBlock(TempDataBlock* tdb_p);

   protected:
      State* currentStatep;
      TempDataBlock* next;
};
}

#endif /* TEMPDATABLOCK_H_ */

