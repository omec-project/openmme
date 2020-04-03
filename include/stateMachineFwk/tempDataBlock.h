/*
 * Copyright (c) 2019, Infosys Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

