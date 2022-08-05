#include "HAL.h"

#define BUZZ_CHANNEL    1
static bool IsEnable = true;

void HAL::Buzz_init()
{
    pinMode(CONFIG_BUZZ_PIN, OUTPUT);
    ledcSetup(BUZZ_CHANNEL, 5000, 10);
    ledcAttachPin(CONFIG_BUZZ_PIN, BUZZ_CHANNEL);
}

void HAL::Buzz_SetEnable(bool en)
{
    if(!en)
    {
        Buzz_Tone(0);
    }

    IsEnable = en;
}

void HAL::Buzz_Tone(uint32_t freq, int32_t duration)
{
    if(!IsEnable)
    {
        return;
    }

    if(duration >= 0)
    {
        //tone(CONFIG_BUZZ_PIN, freq, duration);
        ledcWriteTone(BUZZ_CHANNEL, freq);
        vTaskDelay(duration / portTICK_PERIOD_MS);
    }
    else
    {
        //tone(CONFIG_BUZZ_PIN, freq);
        ledcWriteTone(BUZZ_CHANNEL, freq);
    }
}
