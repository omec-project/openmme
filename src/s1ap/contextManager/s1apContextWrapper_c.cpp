#include "s1apContextWrapper_c.h"
#include "s1apContextWrapper.h"

extern "C" 
{
    uint32_t createControlBlock()
    {
        return createControlBlock_cpp();
    }

    uint32_t findControlBlockWithEnbId(
                                        uint32_t enbId)
    {
        return findControlBlockWithEnbId_cpp(enbId);
    }

    uint32_t findControlBlockWithEnbFd(
                                        uint32_t enbFd)
    {
        return findControlBlockWithEnbFd_cpp(enbFd);
    }

    uint32_t getEnbFdWithCbIndex(uint32_t cbIndex)
    {
        return getEnbFdWithCbIndex_cpp(cbIndex);
    }

    uint32_t setValuesForEnbCtx(uint32_t cbIndex, EnbStruct* enbCtx)
    {
        return setValuesForEnbCtx_cpp(cbIndex, enbCtx);
    }

}
