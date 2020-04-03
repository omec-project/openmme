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

#include <bits/stdc++.h>
#include <iostream>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include "procedureQueue.h"
#include "controlBlock.h"

namespace SM
{
const size_t PROC_QUE_MAX_SIZE = 1000;

ProcedureQueue::ProcedureQueue():cbQ(), mutex_m()
{
	sem_init(&pop_semaphore, 0, 0);
}

ProcedureQueue::~ProcedureQueue()
{
    queue<ControlBlock*> q;
    swap( cbQ, q);
    sem_destroy(&pop_semaphore);
}

ControlBlock* ProcedureQueue::pop()
{
	sem_wait(&pop_semaphore);

	std::lock_guard<std::mutex> lock(mutex_m);

	ControlBlock* cb = NULL;

	if(cbQ.empty())
	{
		return NULL;
	}

	cb = cbQ.front();
	cbQ.pop();

	return cb;
}

bool ProcedureQueue::push(ControlBlock* cb)
{
	std::lock_guard<std::mutex> lock(mutex_m);

	if(PROC_QUE_MAX_SIZE == cbQ.size())
	{
		return false;
	}

	cbQ.push(cb);
	sem_post(&pop_semaphore);

	return true;
}
}
