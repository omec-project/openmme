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




#ifndef GTPV2DATATYPES_MANUAL_H_
#define GTPV2DATATYPES_MANUAL_H_

typedef struct
{
  Uint8 length;
  Uint8 digits[16];
}DigitRegister;

typedef struct
{
  Uint16 length;
  Uint8 octets[16];
}OctetArraySmall;


typedef struct
{
  Uint16 length;
  Uint8 octets[64];
}OctetArrayMedium;

typedef struct
{
  Uint16 length;
  Uint8 octets[256];
}OctetArrayLarge;


#endif /*GTPV2DATATYPES_MANUAL_H_*/
