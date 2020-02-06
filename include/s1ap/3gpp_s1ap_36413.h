/*
* Copyright (c) 2003-2020, Great Software Laboratory Pvt. Ltd.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#ifndef __S1AP_MACROS_H_
#define __S1AP_MACROS_H_

#include <stdbool.h>

/*Refrence document 3GPP TS 36.413 (http://www.arib.or.jp/english/html/overview/doc/STD-T104v3_00/5_Appendix/Rel12/36/36413-c50.pdf) */
enum e_rab_struct_val
{
  E_RAB_ID = 1, //the E-RAB ID uniquely identifies an E-RAB for one UE
  QCI = 9,  // QoS class identifier in TS 23.401[11]
  PRIORITY_LEVEL = 15, //this is Parameter of "priority of allocation and retention" and value 15 means no priority.
  PRE_EMPTION_CAPABILITY = 1, /*It applies to the allocation of resources for an E-RAB and as such it provides the trigger to the pre-emption procedures/processes of the eNB*/
  PRE_EMPTION_VULNERBILITY =1 /*It applies for the entire duration of the E-RAB(default), and indicate if E-RAB is a target of the pre-emption procedures/processes of the eNB.*/
};


#endif /*__S1AP_MACROS_H_*/
