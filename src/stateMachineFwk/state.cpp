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

#include <string>
#include <iostream>
#include "state.h"
#include "actionTable.h"
#include "smTypes.h"
#include "log.h"

using namespace std;


namespace SM
{
	State::State(State_e sID)
	      :stateID(sID),
	       eventToActionsMap()
	{
	}

	State::~State()
	{
	}

	void State::display()	
	{
		for(auto& eventToActionsMapEntry : eventToActionsMap)
		{
			log_msg(LOG_DEBUG, "Event Id = %d \n", eventToActionsMapEntry.first);
			ActionTable& act = eventToActionsMapEntry.second;
			act.display();
		}
	}

	ActStatus State::executeActions(Event_e evt,ControlBlock& cb)
	{
		EventToActionTableMap::iterator itr = eventToActionsMap.find(evt);

		if (itr != eventToActionsMap.end())
		{
			ActionTable& actions_r = itr->second;
			return actions_r.executeActions(cb);
		}
		else
			return ActStatus::HALT;
	}
}
