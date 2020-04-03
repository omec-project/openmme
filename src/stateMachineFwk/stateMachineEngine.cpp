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

#include <iostream>
#include <time.h>
#include <msgBuffer.h>
#include "stateMachineEngine.h"
#include "controlBlock.h"
#include "event.h"
#include "state.h"
#include "smTypes.h"
extern "C"
{
    #include "log.h"
}
using namespace std;
using namespace cmn;
using namespace cmn::utils;

namespace SM
{
	StateMachineEngine::StateMachineEngine():
		procQ_m()
	{
	}

	
	StateMachineEngine::~StateMachineEngine()
	{
	}

	
	StateMachineEngine* StateMachineEngine::Instance()
	{
		static StateMachineEngine SM;
		return &SM;
	}
	
	
	bool StateMachineEngine::addCBToProcQ(ControlBlock* cb)
	{
            return procQ_m.push(cb);
	}

    ActStatus StateMachineEngine::handleProcedureEvent(ControlBlock& cb, State& currentState, Event& currentEvent)
    {
        time_t mytime = time(NULL);
        debugEventInfo dEventInfo(currentEvent.getEventId(), currentState.getStateId(), mytime);
        cb.addDebugInfo(dEventInfo);

        return currentState.executeActions(currentEvent.getEventId(),cb);
    }

	void StateMachineEngine::run()
	{
		
		ControlBlock* cb = procQ_m.pop();

		if(cb == NULL)
			return;

		if (cb->getControlBlockState() == FREE)
		{
		    log_msg(LOG_INFO, "Control block is freed\n");
		    return;
		}

		while (true)
		{
			Event currentEvent;
			if (cb->getCurrentEvent(currentEvent) == false)
			{
				break;
			}

			void * event_data = currentEvent.getEventData();

			State *currentState_p = cb->getCurrentState();
			if (currentState_p == NULL)
			{
				log_msg(LOG_INFO, "Current state is NULL"
						" for control block idx %d\n", cb->getCBIndex());

				if (event_data != NULL)
					delete static_cast <cmn::utils::MsgBuffer *>(event_data);

				break;
			}

						
			ActStatus ret = handleProcedureEvent(*cb, *currentState_p, currentEvent);

			if (ret == ABORT)
			{
				log_msg(LOG_INFO,"Abort Event Initiated \n");
				Event abortEvent(ABORT_EVENT,NULL);
				ret = handleProcedureEvent(*cb, *currentState_p, abortEvent);
			}

                        if (event_data != NULL)
                                delete static_cast <cmn::utils::MsgBuffer *>(event_data);

			if (ret == HALT)
				break;			

		}

		if (cb->getControlBlockState() == ALLOCATED)
		    cb->setProcQueueFlag(false);
	}
}

