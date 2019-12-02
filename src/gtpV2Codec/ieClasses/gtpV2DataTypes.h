/*
 * gtpV2DataTypes.h
 *
 * Revisit header later
 *      Author: hariharanb
 */

#ifndef GTPV2DATATYPES_H_
#define GTPV2DATATYPES_H_

#include "../../cmn/basicTypes.h"

typedef struct
{
  Uint16 count;
  Uint16 values [16];
}Uint16Array16;

typedef struct
{
  Uint16 count;
  Uint8 values [16];
}Uint8Array16;

typedef struct
{
  Uint16 count;
  Uint8 values [32];
}Uint8Array32;

typedef struct
{
  Uint16 count;
  Uint8 values [5];
}Uint8Array5;

typedef struct
{
  Uint16 count;
  Uint8 values [4];
}Uint8Array4;

typedef struct
{
  Uint16 count;
  Uint8 values [512];
}Uint8Array512;

typedef struct
{
  Uint8 mccDigit2;
  Uint8 mccDigit1;
  Uint8 mncDigit3;
  Uint8 mccDigit3;
  Uint8 mncDigit2;
  Uint8 mncDigit1;
  Uint16 locationAreaCode;
  Uint16 cellIdentity;

}CgiField;

typedef struct
{
  Uint8 typeOfOffendingIe;
  Uint16 lengthOfOffendingIe;
  Uint8 instanceOfOffendingIe;

}OffendingIeData;

typedef struct
{
  Uint8 mccDigit2;
  Uint8 mccDigit1;
  Uint8 mncDigit3;
  Uint8 mccDigit3;
  Uint8 mncDigit2;
  Uint8 mncDigit1;
  Uint16 locationAreaCode;
  Uint16 serviceAreaCode;

}SaiField;

typedef struct
{
  Uint8 mccDigit2;
  Uint8 mccDigit1;
  Uint8 mncDigit3;
  Uint8 mccDigit3;
  Uint8 mncDigit2;
  Uint8 mncDigit1;
  Uint16 locationAreaCode;
  Uint16 routintAreaCode;

}RaiField;

typedef struct
{
  Uint8 mccDigit2;
  Uint8 mccDigit1;
  Uint8 mncDigit3;
  Uint8 mccDigit3;
  Uint8 mncDigit2;
  Uint8 mncDigit1;
  Uint16 trackingAreaCode;

}TaiField;

typedef struct
{
  Uint8 mccDigit2;
  Uint8 mccDigit1;
  Uint8 mncDigit3;
  Uint8 mccDigit3;
  Uint8 mncDigit2;
  Uint8 mncDigit1;
  Uint32 eUtranCellId;

}EcgiField;

typedef struct
{
  Uint8 mccDigit2;
  Uint8 mccDigit1;
  Uint8 mncDigit3;
  Uint8 mccDigit3;
  Uint8 mncDigit2;
  Uint8 mncDigit1;
  Uint16 locationAreaCode;

}LaiField;

typedef struct
{
  Uint32 ipValue;

}IpAddressV4;

typedef struct
{
  Uint8Array16 ipValue;

}IpAddressV6;


typedef struct
{
  Uint16 count;
  CgiField values [64];
}CgiFieldArray64;

typedef struct
{
  Uint16 count;
  SaiField values [64];
}SaiFieldArray64;

typedef struct
{
  Uint16 count;
  EcgiField values [64];
}EcgiFieldArray64;

typedef struct
{
  Uint16 count;
  TaiField values [15];
}TaiFieldArray15;

typedef struct
{
  Uint16 count;
  RaiField values [15];
}RaiFieldArray15;

#endif
