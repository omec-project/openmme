#include "s1apContextWrapper.h"
#include "s1apDataGroupManager.h"
#include "dataBlocks.h"
#include "log.h"
#include "err_codes.h"

using namespace mme;
using namespace SM;
    
uint32_t createControlBlock_cpp()
{
    SM::ControlBlock *cb = NULL;
    EnbContext* enbCtxt_p = NULL;
    cb = mme::S1apDataGroupManager::Instance()->allocateCB();
    enbCtxt_p = static_cast <EnbContext *>(cb->getPermDataBlock());
    if (enbCtxt_p != NULL)
    {
        log_msg(LOG_ERROR, "Enb Context exists in newly allocated CB. Should release and allocate again. : TBD.\n");
        return INVALID_ENTRY;
    }

    log_msg(LOG_DEBUG, "Allocate Enb context for CB.\n");
    enbCtxt_p = mme::S1apDataGroupManager::Instance()->getEnbContext();
    if(NULL == enbCtxt_p)
    {
        log_msg(LOG_ERROR, "Enb Context alloc failed.\n");
        return INVALID_ENTRY;
    }

    enbCtxt_p->setContextID(cb->getCBIndex());
    cb->setPermDataBlock(enbCtxt_p);
    cb->setFastAccessBlock(enbCtxt_p, 1);
    return cb->getCBIndex();
}

uint32_t findControlBlockWithEnbId_cpp(uint32_t enbId)
{
    int cbIndex = mme::S1apDataGroupManager::Instance()->findCBWithenbId(enbId);

    if (cbIndex <= 0)
    {
        log_msg(LOG_ERROR, "Failed to find control block with enbid :%d.\n",enbId);
        return INVALID_CB_INDEX;
    }

    return cbIndex;

}

uint32_t findControlBlockWithEnbFd_cpp(uint32_t enbFd)
{
    int cbIndex = mme::S1apDataGroupManager::Instance()->findCBWithenbFd(enbFd);

    if (cbIndex <= 0)
    {
        log_msg(LOG_ERROR, "Failed to find control block with enbFd :%d.\n",enbFd);
        return INVALID_CB_INDEX;
    }

    return cbIndex;

}

uint32_t getEnbFdWithCbIndex_cpp(uint32_t cbIndex)
{
    SM::ControlBlock *cb = NULL;
    if (cbIndex > 0)
    {
        cb = mme::S1apDataGroupManager::Instance()->findControlBlock(cbIndex);
        if(NULL == cb)
        {
            log_msg(LOG_ERROR,"Control block not found for cb Index %d.\n", cbIndex);
            return INVALID_CB_INDEX;
        }

        EnbContext* enbCtxt_p = static_cast <EnbContext *>(cb->getPermDataBlock());
        log_msg(LOG_DEBUG,"Enb Fd : %d",
                enbCtxt_p->getEnbFd());
        return enbCtxt_p->getEnbFd();
    }
    else
    {
        log_msg(LOG_ERROR, "Failed to find control block with cbIndex :%d.\n",cbIndex);
        return INVALID_CB_INDEX;
    }

}

uint32_t setValuesForEnbCtx_cpp(uint32_t cbIndex, EnbStruct* enbCtx)
{
    SM::ControlBlock *cb = NULL;
    if (cbIndex > 0)
    {
        cb = mme::S1apDataGroupManager::Instance()->findControlBlock(cbIndex);
        if(NULL == cb)
        {
            log_msg(LOG_ERROR,"Control block not found for cb Index %d.\n", cbIndex);
            return INVALID_CB_INDEX;
        }

        EnbContext* enbCbCtx = static_cast <EnbContext *>(cb->getPermDataBlock());
        mme::S1apDataGroupManager::Instance()->deleteenbIdkey(
                                                    enbCbCtx->getEnbId());
        mme::S1apDataGroupManager::Instance()->deleteenbFdkey(
                                                    enbCbCtx->getEnbFd());
        enbCbCtx->setEnbFd(enbCtx->enbFd_m);
        enbCbCtx->setEnbId(enbCtx->enbId_m);
        enbCbCtx->setS1apEnbUeId(enbCtx->s1apEnbUeId_m);
        mme::S1apDataGroupManager::Instance()->addenbIdkey(
                                        enbCtx->enbId_m, cbIndex);
        mme::S1apDataGroupManager::Instance()->addenbFdkey(
                                        enbCtx->enbFd_m, cbIndex);
    }
    else
    {
        log_msg(LOG_ERROR, "Failed to find control block with cbIndex :%d.\n",cbIndex);
        return INVALID_CB_INDEX;
    }

    return SUCCESS;
}

//}
