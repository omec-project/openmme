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

#ifndef INCLUDE_CMN_MEMPOOLMANAGER_H_
#define INCLUDE_CMN_MEMPOOLMANAGER_H_

#include <cstdint>
#include <memory>
#include <cstring>

namespace cmn {
	namespace memPool {
		template <typename T>
		class MemBlock
		{
		public:
                        union Data {
                                MemBlock<T>* next_mp;
                                alignas(alignof(T)) uint8_t dataBlock_m[sizeof(T)];
                        };

			MemBlock() { memset(data_m.dataBlock_m, 0, sizeof(T)); }

			void reset() { memset(data_m.dataBlock_m, 0, sizeof(T)); }

			MemBlock<T>* getNextMemBlock() { return data_m.next_mp; }
			void setNextMemBlock(MemBlock<T>* nxtBlk_p) { data_m.next_mp = nxtBlk_p; }

			T* getDataBlock() { return (reinterpret_cast<T*> (data_m.dataBlock_m)); }

		private:
			Data data_m;
		};

		template <typename T>
		class MemChunk
		{
		public:

			MemChunk(uint32_t numOfBlocks)
			{
				std::unique_ptr<MemBlock<T>[]> blkArray_p(new MemBlock<T>[numOfBlocks]);
				blockArray_mpa.reset(blkArray_p.release());

				uint32_t  i = 1;
				for (; i < numOfBlocks; i++)
				{
					blockArray_mpa[i-1].setNextMemBlock(&blockArray_mpa[i]);
				}
				blockArray_mpa[i].setNextMemBlock(NULL);
			}

			MemBlock<T>* getMemBlockArray() { return blockArray_mpa.get(); }

			void setNextMemChunk(std::unique_ptr<MemChunk> &&nxtChunk_p) { nextMemChunk_mp.reset(nxtChunk_p.release()); }

		private:
			std::unique_ptr<MemChunk<T>> nextMemChunk_mp;
			std::unique_ptr<MemBlock<T>[]> blockArray_mpa;
		};

		template <typename T>
		class MemPoolManager
		{
		public:
			MemPoolManager(size_t chunkSize):chunkSize_m(chunkSize),
					currentChunk_mp(new MemChunk<T>(chunkSize)),
					freeList_mp(currentChunk_mp->getMemBlockArray())
			{

			}

			template <typename... Args> T* allocate(Args &&... args)
			{
				if (freeList_mp == NULL)
				{
					std::unique_ptr<MemChunk<T>> newChunk_p (new MemChunk<T>(chunkSize_m));
					newChunk_p->setNextMemChunk(std::move(currentChunk_mp));
					currentChunk_mp.reset(newChunk_p.release());

					freeList_mp = currentChunk_mp->getMemBlockArray();
				}
				MemBlock<T>* currentBlock_p = freeList_mp;
				freeList_mp = freeList_mp->getNextMemBlock();

				T* dataBlock_p = currentBlock_p->getDataBlock();

				new (dataBlock_p) T(std::forward<Args>(args)...);
				return dataBlock_p;
			}

			void free(T* data_p)
			{
			    data_p->T::~T();
			    MemBlock<T>* currentBlock_p = reinterpret_cast<MemBlock<T>*>(data_p);
			    
			    currentBlock_p->reset();

			    currentBlock_p->setNextMemBlock(freeList_mp);
			    freeList_mp = currentBlock_p;
			}
		private:
			size_t chunkSize_m;
			std::unique_ptr<MemChunk<T>> currentChunk_mp;
			MemBlock<T>* freeList_mp;
		};
	}
}


#endif /* INCLUDE_CMN_MEMPOOLMANAGER_H_ */
