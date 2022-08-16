#include "HAL.h"
#include "AK8975.h"

static AK8975 mag = AK8975(0x0C);
static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

bool HAL::MAG_Init()
{
    Serial.print("MAG: init...");
    mag.initialize();
    bool success = true;

    Serial.println(success ? "success" : "failed");

    return success;
}

void HAL::MAG_SetCommitCallback(CommitFunc_t func, void* userData)
{
    CommitFunc = func;
    UserData = userData;
}

void HAL::MAG_Update()
{
    MAG_Info_t magInfo;
    magInfo.x = mag.getHeadingX();
    magInfo.y = mag.getHeadingY();
    magInfo.z = mag.getHeadingZ();
    magInfo.dir = 0;

    if(CommitFunc)
    {
        CommitFunc(&magInfo, UserData);
    }
}
