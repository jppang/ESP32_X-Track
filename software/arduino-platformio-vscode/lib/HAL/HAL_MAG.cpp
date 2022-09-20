#include "HAL.h"
#include <QMC5883LCompass.h>

static QMC5883LCompass mag;
static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

bool HAL::MAG_Init()
{
    Serial.print("MAG: init...");
    mag.init();
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
    mag.read();
    magInfo.x = mag.getX();
    magInfo.y = mag.getY();
    magInfo.z = mag.getZ();
    magInfo.dir = mag.getAzimuth();

    if(CommitFunc)
    {
        CommitFunc(&magInfo, UserData);
    }
}
