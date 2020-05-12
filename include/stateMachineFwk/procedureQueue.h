/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
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
