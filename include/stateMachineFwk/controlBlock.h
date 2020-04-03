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

#ifndef CONTROLBLOCK_H_
#define CONTROLBLOCK_H_

#include <mutex>
#include <queue>
#include <deque>
#include <stdint.h>
#include <time.h>
#include "permDataBlock.h"
#include <smTypes.h>
#include "tempDataBlock.h"

class Event;
class State;

using namespace std;

namespace SM
{
	typedef struct debugEventInfo
	{
        	Event_e event;
	        State_e state;
        	time_t evt_time;

        	debugEventInfo(Event_e evt, State_e st, time_t t)
        	{
        		event = evt;
        		state = st;
        		evt_time = t;
        	}

	}debugEventInfo;

	class Event;
	class State;
	class ControlBlock
	{
   	public:
			static const unsigned short MAX_FAST_BLOCK_IDX = 5;
			static uint32_t controlBlockArrayIdx;

      		ControlBlock();
      		virtual ~ControlBlock();

      		void reset();

      		uint32_t getCBIndex();

      		void addEventToProcQ(Event &event);
	      	bool getCurrentEvent(Event &evt);

	      	State* getCurrentState();
      		void setNextState(State* state);

      		PermDataBlock* getFastAccessBlock(unsigned short idx) const;
      		void setFastAccessBlock(PermDataBlock* pdb_p, unsigned short idx);

      		PermDataBlock* getPermDataBlock() const;
      		void setPermDataBlock(PermDataBlock* pdb_p);

      		TempDataBlock* getTempDataBlock() const;
      		void setTempDataBlock(TempDataBlock* tdb_p); 
      		void setCurrentTempDataBlock(TempDataBlock* tdb_p);

      		void addDebugInfo(debugEventInfo& eventInfo);
      		inline deque<debugEventInfo> getDebugInfoQueue()const
			{
      			return debugEventInfoQ;
			}

      		void* getMsgData()
      		{
      			return data_p;
      		}

      		void setMsgData(void* ptr)
      		{
      			data_p = ptr;
      		}

      		void setControlBlockState(ControlBlockState state);
      		ControlBlockState getControlBlockState();

            bool isInProcQueue();
            void setProcQueueFlag(bool flag);

      		virtual void display();

   	private:
		std::mutex mutex_m;
		const uint32_t cbIndex_m;
		ControlBlockState cbState_m;

		// deallocated once the event is processed
		void* data_p;

      		PermDataBlock* pdb_mp;
      		PermDataBlock* fadb_mpa[MAX_FAST_BLOCK_IDX];
      		TempDataBlock* tdb_mp;

      		queue<Event> eventQ;
		
	    	deque<debugEventInfo> debugEventInfoQ;
		bool inProcQueue_m;
	};
}
#endif /* CONTROLBLOCK_H_ */
