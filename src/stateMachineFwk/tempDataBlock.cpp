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

#include "tempDataBlock.h"
#include "stateMachineEngine.h"
#include "state.h"

using namespace std;

namespace SM
{
TempDataBlock::TempDataBlock(): currentStatep(NULL), next(NULL)
{
}

TempDataBlock::~TempDataBlock()
{
}

void TempDataBlock::display()
{
	if (currentStatep)
		currentStatep->display();
}

State* TempDataBlock::getCurrentState()
{
	return currentStatep;
}

void TempDataBlock::setNextState(State* state)
{
	currentStatep = state;
}

TempDataBlock* TempDataBlock::getNextTempDataBlock()
{
	return next;
}

void TempDataBlock::setNextTempDataBlock(TempDataBlock* tdb_p)
{
	next = tdb_p;
}

}
