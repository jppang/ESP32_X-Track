#include "DataProc.h"
#include "../HAL/HAL.h"

DATA_PROC_INIT_DEF(GY91)
{
    HAL::GY91_SetCommitCallback([](void* info, void* userData){
        Account* account = (Account*)userData;
        return account->Commit(info, sizeof(HAL::GY91_Info_t));
    }, account);
}
