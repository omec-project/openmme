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
#include <deque>
#include "smTypes.h"

#ifndef ACTIONTABLE_H_
#define ACTIONTABLE_H_

namespace SM
{

	class ControlBlock;
	class State;

	using namespace std;

	class ActionTable
	{
   	public:
		ActionTable();
		virtual ~ActionTable();

		virtual void display();

		ActStatus executeActions(ControlBlock& cb);
		void addAction(ActionPointer act);
		void setNextState(State*st);
	private:
     		deque<ActionPointer> actionsQ;
        	State* nextStatep;
	};
}
#endif /* ACTIONTABLE_H_ */
