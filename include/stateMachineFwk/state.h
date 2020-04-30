/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <map>
#include "smTypes.h"

using namespace std;

namespace SM
{
	class State
	{
  	public:
		State(State_e sID);
      		virtual ~State();

	      	virtual void display();

      		ActStatus executeActions(Event_e evtId,ControlBlock& cb);

	      	inline State_e getStateId()const
      		{
			return stateID;
      		}

   	protected:
      		State_e stateID;
	      	EventToActionTableMap eventToActionsMap;
	};
}
#endif /* STATE_H_ */
