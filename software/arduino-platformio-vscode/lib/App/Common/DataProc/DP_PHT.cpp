#include "DataProc.h"
#include "../HAL/HAL.h"

DATA_PROC_INIT_DEF(PHT)
{
    HAL::PHT_SetCommitCallback([](void* info, void* userData){
        Account* account = (Account*)userData;
        return account->Commit(info, sizeof(HAL::PHT_Info_t));
    }, account);
}
