#ifndef __HAL_DEF_H
#define __HAL_DEF_H

#include <stdint.h>

namespace HAL
{

/* Clock */
typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t millisecond;
} Clock_Info_t;

/* GPS */
typedef struct
{
    double longitude;
    double latitude;
    float altitude;
    float course;
    float speed;
    int16_t satellites;
    bool isVaild;
    Clock_Info_t clock;
} GPS_Info_t;

/* PHT(Pressure-Humidity-Temperature) */
typedef struct
{
    float pressure;
    float humidity;
    float temperature;
} PHT_Info_t;

/* MAG */
typedef struct
{
    int dir;
    int x;
    int y;
    int z;
} MAG_Info_t;

/* IMU */
typedef struct
{
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float steps;
} IMU_Info_t;

typedef struct
{
    IMU_Info_t imu;
    MAG_Info_t mag;
    PHT_Info_t pht;
} GY91_Info_t;

/* SportStatus */
typedef struct
{
    uint32_t lastTick;

    float weight;

    float speedKph;
    float speedMaxKph;
    float speedAvgKph;

    union
    {
        uint32_t totalTimeUINT32[2];
        uint64_t totalTime;
    };

    float totalDistance;

    union
    {
        uint32_t singleTimeUINT32[2];
        uint64_t singleTime;
    };

    float singleDistance;
    float singleCalorie;
    
} SportStatus_Info_t;

/* Power */
typedef struct
{
    uint16_t voltage;
    uint8_t usage;
    bool isCharging;
} Power_Info_t;

}

#endif
