/*
* Copyright (c) 2019 Infosys Limited
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

#ifndef GTPV2DATATYPES_H_
#define GTPV2DATATYPES_H_
#include <basicTypes.h>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
typedef struct
{
    Uint16 count;
    Uint8 values[16];

}Uint8Array16;
    
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
    Uint16 values[16];

}Uint16Array16;
                    
            
                                        
typedef struct
{
    Uint16 count;
    Uint8 values[32];

}Uint8Array32;
                            
typedef struct
{
    Uint16 count;
    Uint8 values[5];

}Uint8Array5;
                            
typedef struct
{
    Uint16 count;
    Uint8 values[4];

}Uint8Array4;
                            
typedef struct
{
    Uint16 count;
    Uint8 values[512];

}Uint8Array512;
                            
typedef struct
{
    Uint16 count;
    CgiField values[64];

}CgiFieldArray64;
                            
typedef struct
{
    Uint16 count;
    SaiField values[64];

}SaiFieldArray64;
                            
typedef struct
{
    Uint16 count;
    EcgiField values[64];

}EcgiFieldArray64;
                            
typedef struct
{
    Uint16 count;
    TaiField values[15];

}TaiFieldArray15;
                            
typedef struct
{
    Uint16 count;
    RaiField values[15];

}RaiFieldArray15;
    
#endif 