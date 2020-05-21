/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <map>

#include "smEnumTypes.h"

using namespace std;

namespace SM
{
	class Event
	{
   	public:
		Event();
      		Event(Event_e evtID, void* eventData);
      		virtual ~Event();

      		inline Event_e getEventId()const
      		{
      			return eventID;
      		}

      		void* getEventData() const;

      		virtual void display();
 
   	private:
	      	Event_e eventID;
	      	void * eventData_p;
	};
}

#endif /* EVENT_H_ */
