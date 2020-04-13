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
#include <string>
#include "controlBlock.h"
#include "event.h"
#include "log.h"
#include "tempDataBlock.h"
#include <stateMachineEngine.h>

using namespace std;

namespace SM
{
	uint32_t ControlBlock::controlBlockArrayIdx = 0;

	ControlBlock::ControlBlock():mutex_m(), cbIndex_m(++controlBlockArrayIdx),
	        cbState_m(FREE), data_p(NULL), pdb_mp(NULL),
	        tdb_mp(NULL), inProcQueue_m(false)
	{
        for (int i = 0; i < MAX_FAST_BLOCK_IDX; i++)
            fadb_mpa[i] = NULL;

        std::queue<Event> emptyQ;
        std::swap( eventQ, emptyQ );

        std::deque<debugEventInfo> emptyDQ;
        std::swap(debugEventInfoQ, emptyDQ);
	}

	void ControlBlock::reset()
	{
		std::lock_guard<std::mutex> lock(mutex_m);

		cbState_m = FREE;

		data_p = NULL;
		pdb_mp = NULL;

		for (int i = 0; i < MAX_FAST_BLOCK_IDX; i++)
			fadb_mpa[i] = NULL;

		tdb_mp = NULL;

		inProcQueue_m = false;

		std::queue<Event> emptyQ;
		std::swap( eventQ, emptyQ );

		std::deque<debugEventInfo> emptyDQ;
		std::swap(debugEventInfoQ, emptyDQ);
	}

	ControlBlock::~ControlBlock()
	{
	}

	bool ControlBlock::getCurrentEvent(Event &evt)
	{
		std::lock_guard<std::mutex> lock(mutex_m);

		if(eventQ.empty())
			return false;

		evt = eventQ.front();
		eventQ.pop();

		setMsgData(evt.getEventData());

		return true;
	}
    
	State* ControlBlock::getCurrentState()
	{
		return tdb_mp->getCurrentState();
	}
      
	void ControlBlock::display()
	{
		log_msg(LOG_DEBUG,"Displaying control block");

		pdb_mp->display();

		tdb_mp->display();

	}

	void ControlBlock::addEventToProcQ(Event &event)
	{
		std::lock_guard<std::mutex> lock(mutex_m);

		if (cbState_m == ALLOCATED)
		{
		    eventQ.push(event);
		    if (inProcQueue_m == false)
		    {
		        inProcQueue_m = true;
		        if (!SM::StateMachineEngine::Instance()->addCBToProcQ(this))
		        {
		            inProcQueue_m = false;
		        }
		    }
		}
	}

	void ControlBlock::setNextState(State* state)
	{
		if (tdb_mp != NULL)
			tdb_mp->setNextState(state);
	}

	PermDataBlock* ControlBlock::getFastAccessBlock(unsigned short idx) const
	{
		PermDataBlock* permBlock_p = NULL;

		if (idx < ControlBlock::MAX_FAST_BLOCK_IDX)
			permBlock_p = fadb_mpa[idx];

		return permBlock_p;
	}

	void ControlBlock::setFastAccessBlock(
		PermDataBlock* pdb_p, unsigned short idx)
	{
		if (idx < ControlBlock::MAX_FAST_BLOCK_IDX)
			fadb_mpa[idx] = pdb_p;
	}

	PermDataBlock* ControlBlock::getPermDataBlock() const
	{
		return pdb_mp;
	}

	void ControlBlock::setPermDataBlock(PermDataBlock* pdb_p)
	{
		pdb_mp = pdb_p;
	}

    TempDataBlock* ControlBlock::getTempDataBlock() const
    {
    	return tdb_mp;
    }

    void ControlBlock::setTempDataBlock(TempDataBlock* tdb_p)
    {
    	if (tdb_p == NULL)
    		return;

    	tdb_mp = tdb_p;
    }

    void ControlBlock::setCurrentTempDataBlock(TempDataBlock* tdb_p)
    {
    	if (tdb_p == NULL)
    		return;

        if (tdb_mp != NULL)
        {
        	tdb_p->setNextTempDataBlock(tdb_mp);
        }

    	tdb_mp = tdb_p;
    }	
	
	void ControlBlock::addDebugInfo(debugEventInfo& eventInfo)
	{
		if(debugEventInfoQ.size()>=10)
		{
			debugEventInfoQ.pop_front();
		}
		debugEventInfoQ.push_back(eventInfo);
	}

	uint32_t ControlBlock::getCBIndex()
	{
		return cbIndex_m;
	}

    void ControlBlock::setControlBlockState(ControlBlockState state)
    {
        std::lock_guard<std::mutex> lock(mutex_m);
        
        log_msg(LOG_INFO, "CB state transition from %d to %d\n", cbState_m, state);

        cbState_m = state;
    }

    ControlBlockState ControlBlock::getControlBlockState()
    {
        std::lock_guard<std::mutex> lock(mutex_m);

        return cbState_m;
    }

    void ControlBlock::setProcQueueFlag(bool flag)
    {
        std::lock_guard<std::mutex> lock(mutex_m);
        inProcQueue_m = flag;
    }

    bool ControlBlock::isInProcQueue()
    {
        std::lock_guard<std::mutex> lock(mutex_m);
        return inProcQueue_m;
    }
}
