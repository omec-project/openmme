/*
 * Copyright 2019-present, Infosys Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef WRAPPERSTRUCTURES_H
#define WRAPPERSTRUCTURES_H
/**************************************
 *
 ***************************************/
#include "s1ap_structs.h"

#define INVALID_ENTRY    0xFFFFFFFF
#define INVALID_CB_INDEX 0xFFFFFFFF
struct EnbStruct
{
    int enbFd_m;
    int enbId_m;
    int s1apEnbUeId_m;
    struct TAI tai_m;
};

#endif
