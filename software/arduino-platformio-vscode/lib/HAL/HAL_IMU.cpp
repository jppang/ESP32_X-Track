#include "HAL.h"
#include "MPU6500_WE.h"

static MPU6500_WE imu = MPU6500_WE(0x68);
static HAL::CommitFunc_t CommitFunc = nullptr;
static void* UserData = nullptr;

bool HAL::IMU_Init()
{
    Serial.print("IMU: init...");

    bool success = imu.init();

    Serial.println(success ? "success" : "failed");

    return success;
}

void HAL::IMU_SetCommitCallback(CommitFunc_t func, void* userData)
{
    CommitFunc = func;
    UserData = userData;
}

void HAL::IMU_Update()
{
    IMU_Info_t imuInfo;
    imuInfo.ax = imu.getGValues().x;
    imuInfo.ay = imu.getGValues().y;
    imuInfo.az = imu.getGValues().z;
    imuInfo.gx = imu.getGyrValues().x;
    imuInfo.gy = imu.getGyrValues().y;
    imuInfo.gz = imu.getGyrValues().z;
    
    imuInfo.steps = 0;

    if(CommitFunc)
    {
        CommitFunc(&imuInfo, UserData);
    }
}
