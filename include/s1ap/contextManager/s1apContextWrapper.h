#ifndef __S1apContextWrappers_H
#define __S1apContextWrappers_H


#include "stdint.h"
#include "structs.h"


	uint32_t createControlBlock_cpp();
    uint32_t findControlBlockWithEnbId_cpp(uint32_t enbId);
    uint32_t findControlBlockWithEnbFd_cpp(uint32_t enbFd);
    uint32_t getEnbFdWithCbIndex_cpp(uint32_t cbIndex);
    uint32_t setValuesForEnbCtx_cpp(uint32_t cbIndex, 
                                struct EnbStruct* enbCtx);

#endif
