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
#include "event.h"
#include "log.h"

using namespace std;

namespace SM
{
	Event::Event():
		eventID(), eventData_p(NULL)
	{
	}

	Event::Event(Event_e evtID, void* ptr)
	  	:eventID(evtID), eventData_p(ptr)
	{
	}

	Event::~Event()
	{
	}

	void *Event::getEventData() const
	{
		return eventData_p;
	}

	void Event::display()
	{
        	log_msg(LOG_DEBUG,"Event ID - %d",eventID);
	}
}
