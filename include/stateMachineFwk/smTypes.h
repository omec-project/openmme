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

#ifndef INCLUDE_STATEMACHFWK_SMTYPES_H_
#define INCLUDE_STATEMACHFWK_SMTYPES_H_

#include <map>
#include <smEnumTypes.h>

using namespace std;

namespace SM{

class ControlBlock;
class State;
class ActionTable;

enum ActStatus
{
	PROCEED,
	HALT,
	ABORT
};

enum ControlBlockState
{
    FREE,
    ALLOCATED,
    MAX_STATE
};

using ActionPointer = ActStatus(*)(ControlBlock&);
using EventToActionTableMap = std::map <Event_e, ActionTable>;

};

#endif /* INCLUDE_STATEMACHFWK_SMTYPES_H_ */
