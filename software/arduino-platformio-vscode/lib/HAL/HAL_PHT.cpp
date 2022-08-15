#include "HAL.h"
#include "Seeed_BMP280.h"
#include "AHT10.h"

#define BMP280_ADDR 0x77
#define AHT20_ADDR  0x38

static BMP280 bmp;
static AHT10 aht = AHT10(AHT10_ADDRESS_0X38, AHT20_SENSOR);
static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

bool HAL::PHT_Init()
{
    Serial.print("PHT(AHT20+BMP280): init...");

    bool success = (bmp.init() && aht.begin());

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
    phtInfo.humidity = aht.readHumidity();
    phtInfo.temperature = aht.readTemperature();

    if(CommitFunc)
    {
        CommitFunc(&phtInfo, UserData);
    }
}
