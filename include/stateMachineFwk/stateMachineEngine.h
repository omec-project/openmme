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

#ifndef STATEMACHINEENGINE_H_
#define STATEMACHINEENGINE_H_

#include <map>
#include "smTypes.h"
#include "procedureQueue.h"
#include "event.h"

namespace SM
{
	class State;
	class StateMachineEngine
	{
	public:
		~StateMachineEngine();
		static StateMachineEngine* Instance();
	    void run();
      	bool addCBToProcQ(ControlBlock* cb);
        ActStatus handleProcedureEvent(ControlBlock& cb, State& currentState, Event& currentEvent);	
   	private:
		StateMachineEngine();

		ProcedureQueue procQ_m;
	};
}

#endif /* STATEMACHINEENGINE_H_ */
