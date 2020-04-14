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

#ifndef PROCEDUREQUEUE_H_
#define PROCEDUREQUEUE_H_

#include <queue>
#include <mutex>
#include <semaphore.h>

using namespace std;

namespace SM
{

class ControlBlock;

class ProcedureQueue
{
   public:
      ProcedureQueue();
      ~ProcedureQueue();

      ControlBlock* pop();
      bool push(ControlBlock* cb);

   private:
      queue <ControlBlock*> cbQ;
      std::mutex mutex_m;
      sem_t pop_semaphore;
};
}
#endif /* PROCEDUREQUEUE_H_ */
