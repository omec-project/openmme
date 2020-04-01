 /*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
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
