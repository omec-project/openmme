/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
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
