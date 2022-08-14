#include "HAL.h"
#include "Seeed_BMP280.h"
#include "DFRobot_AHT20.h"

static BMP280 bmp;
static DFRobot_AHT20 aht;
static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

bool HAL::PHT_Init()
{
    Serial.print("PHT(AHT20+BMP280): init...");

    bool success = bmp.init();
    aht.begin();

    Serial.println(success ? "success" : "failed");

    return success;
}

void HAL::PHT_SetCommitCallback(CommitFunc_t func, void* userData)
{
    CommitFunc = func;
    UserData = userData;
}

void HAL::PHT_Update()
{
    PHT_Info_t phtInfo;

    phtInfo.pressure = bmp.getPressure();
    phtInfo.humidity = aht.getHumidity_RH();
    phtInfo.temperature = aht.getTemperature_C();
//    Serial.printf(
//        "ax = %d, ay = %d, az = %d, gx = %d, gy = %d, gz = %d\r\n",
//        imuInfo.ax, imuInfo.ay, imuInfo.az, imuInfo.gx, imuInfo.gy, imuInfo.gz
//    );

    if(CommitFunc)
    {
        CommitFunc(&phtInfo, UserData);
    }
}
