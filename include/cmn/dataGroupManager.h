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

#ifndef DATA_GROUP_MANAGER_H
#define DATA_GROUP_MANAGER_H

#include <deque>
#include "controlBlock.h"
#include <mutex>

using namespace SM;

namespace cmn {
namespace DGM
{
	class DataGroupManager
	{
		public:
		
			DataGroupManager();
			virtual ~DataGroupManager();
			
			void initializeCBStore( int DataCount );
			virtual ControlBlock* allocateCB();
			virtual void deAllocateCB( uint32_t cbIndex );
			SM::ControlBlock* findControlBlock( uint32_t index );

		protected:
			ControlBlock* cbstore_m;		// Indexed Store

		private:
			std::deque<ControlBlock*> freeQ_m;	// free Q
			std::mutex mutex_m;

	};
};
};
#endif
