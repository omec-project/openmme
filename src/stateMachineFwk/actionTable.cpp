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
#include "controlBlock.h"
#include "actionTable.h"
#include "state.h"
#include "log.h"

using namespace std;

namespace SM
{

	ActionTable::ActionTable()
		:nextStatep(NULL)
	{
	}

	ActionTable::~ActionTable()
	{
	}

	ActStatus ActionTable::executeActions(ControlBlock& cb)
	{
		ActStatus rt = PROCEED;
		for(auto it = actionsQ.begin(); it != actionsQ.end(); it++)
		{
			rt = (*it)(cb);
			if(PROCEED != rt)
			{
				// TODO: error handling
				break;
			}
		}

		if (PROCEED == rt &&
				nextStatep != NULL)
		{
			cb.setNextState(nextStatep);
		}

		return rt;
	}

	void ActionTable::addAction(ActionPointer act)
	{
		actionsQ.push_back(act);
	}

	void ActionTable::setNextState(State* st)
	{
		nextStatep = st;
	}

	void ActionTable::display()
	{
		if(NULL != nextStatep)
		{
			log_msg(LOG_DEBUG,"\nnext State : - %d \n",nextStatep->getStateId());
		}
	}
}	
