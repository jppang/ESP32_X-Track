#include "HAL.h"
#include "MPU9250.h"
#include "Seeed_BMP280.h"

static MPU9250 imu;
static BMP280 bmp;

static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

bool HAL::GY91_Init()
{
    Serial.print("GY91(MPU9250+BMP280): init...");

    bool success = imu.setup(0x68);
    bmp.init();

    Serial.println(success ? "success" : "failed");

    return success;
}

void HAL::GY91_SetCommitCallback(CommitFunc_t func, void* userData)
{
    CommitFunc = func;
    UserData = userData;
}

void HAL::GY91_Update()
{
    GY91_Info_t gy91Info;

    imu.update();
    gy91Info.imu.ax = imu.getAccX();
    gy91Info.imu.ay = imu.getAccY();
    gy91Info.imu.az = imu.getAccZ();
    gy91Info.imu.gx = imu.getGyroX();
    gy91Info.imu.gy = imu.getGyroY();
    gy91Info.imu.gz = imu.getGyroZ();
    gy91Info.mag.x  = imu.getMagX();
    gy91Info.mag.y  = imu.getMagY();
    gy91Info.mag.z  = imu.getMagZ();

    gy91Info.pht.pressure = bmp.getPressure();
    gy91Info.pht.humidity = 0;
    gy91Info.pht.temperature = bmp.getTemperature();
//    Serial.printf(
//        "ax = %d, ay = %d, az = %d, gx = %d, gy = %d, gz = %d\r\n",
//        imuInfo.ax, imuInfo.ay, imuInfo.az, imuInfo.gx, imuInfo.gy, imuInfo.gz
//    );

    gy91Info.imu.steps = 0;

    if(CommitFunc)
    {
        CommitFunc(&gy91Info, UserData);
    }
}
