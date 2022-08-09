#include "HAL.h"
#include "time.h"
#include "sys/time.h"

void HAL::Clock_Init()
{
    Clock_Info_t info;
    Clock_GetInfo(&info);
    time_t now = time(NULL);
    struct tm* calendar = localtime(&now);
    setenv("TZ", "CST-8", 1);
    Serial.print(calendar, "%Y/%m/%d %H:%M:%S ");
    Serial.println(Clock_GetWeekString(calendar->tm_wday));
}

void HAL::Clock_GetInfo(Clock_Info_t* info)
{
    time_t now = time(NULL);
    struct tm* calendar = localtime(&now);
    info->year = calendar->tm_year;
    info->month = calendar->tm_mon;
    info->day = calendar->tm_mday;
    info->week = calendar->tm_wday;
    info->hour = calendar->tm_hour;
    info->minute = calendar->tm_min;
    info->second = calendar->tm_sec;
    info->millisecond = millis();
}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{
    time_t now = time(NULL);
    struct tm today = {info->second, info->minute, info->hour, info->day, info->month, (info->year - 1900)};
    now = mktime(&today);
    struct timeval tv = { .tv_sec = now };
    struct timezone tz = { .tz_minuteswest = 8*60 };
    settimeofday(&tv, &tz);
}

const char* HAL::Clock_GetWeekString(uint8_t week)
{
    const char* week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
