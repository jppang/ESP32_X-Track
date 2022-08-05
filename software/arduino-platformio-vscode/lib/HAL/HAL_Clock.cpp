#include "HAL.h"
#include "rtc.h"
#include "time.h"

void HAL::Clock_Init()
{
    Clock_Info_t info;
    Clock_GetInfo(&info);
    time_t now = time(NULL);
    struct tm* calendar = localtime(&now);
    Serial.print(calendar, "%Y/%m/%d %H:%M:%S ");
    Serial.println(Clock_GetWeekString(calendar->tm_wday));
}

void HAL::Clock_GetInfo(Clock_Info_t* info)
{
    time_t now = time(NULL);
    struct tm* calendar = localtime(&now);
//    Serial.print(calendar, "%Y/%m/%d %H:%M:%S ");
//    Serial.println(Clock_GetWeekString(calendar->tm_wday));
    info->year = calendar->tm_year;
    info->month = calendar->tm_mon;
    info->day = calendar->tm_mday;
    info->week = calendar->tm_wday;
    info->hour = calendar->tm_hour;
    info->minute = calendar->tm_min;
    info->second = calendar->tm_sec;
    info->millisecond = 0;
}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{
    struct tm now = {info->second, info->minute, info->hour, info->day, info->month, info->year};
    mktime(&now);
}

const char* HAL::Clock_GetWeekString(uint8_t week)
{
    const char* week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
