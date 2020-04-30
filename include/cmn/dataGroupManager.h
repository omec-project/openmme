/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
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
