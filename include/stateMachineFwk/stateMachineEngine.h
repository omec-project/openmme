/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
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
