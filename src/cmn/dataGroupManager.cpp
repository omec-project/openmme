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

#include "dataGroupManager.h"
#include "memPoolManager.h"

namespace cmn {
namespace DGM
{
	DataGroupManager::DataGroupManager():cbstore_m(NULL)
	{

	}
	
	DataGroupManager::~DataGroupManager()
	{
		delete[] cbstore_m;
	}
	
	void DataGroupManager::initializeCBStore( int DataCount )
	{
		cbstore_m = new ControlBlock[DataCount];
		for( int idx = 0; idx < DataCount; idx ++ )
		{
			freeQ_m.push_back( &cbstore_m[idx] );
		}
	}
	
	ControlBlock* DataGroupManager::allocateCB()
	{
		std::lock_guard<std::mutex> lock(mutex_m);

		ControlBlock* cbp = freeQ_m.front();
		freeQ_m.pop_front();

		if (cbp != NULL)
		{
		    cbp->setControlBlockState(ALLOCATED);
		}

		return cbp;
	}

	ControlBlock* DataGroupManager::findControlBlock(uint32_t cbIndex)
	{
		ControlBlock* cbp = &cbstore_m[cbIndex - 1];
		if (cbp != NULL && cbp->getControlBlockState() != FREE)
		    return cbp;
		else
		    return NULL;
	}
	
	void DataGroupManager::deAllocateCB( uint32_t cbIndex )
	{
        cbstore_m[cbIndex - 1].reset();

		std::lock_guard<std::mutex> lock(mutex_m);
		freeQ_m.push_back( &cbstore_m[cbIndex - 1]);
	}
};
};
