#include "HAL.h"
#include "TFT_eSPI.h"

#define DISP_USE_DMA         1
#define DISP_USE_FPS_TEST    0

static TFT_eSPI screen = TFT_eSPI(CONFIG_SCREEN_HOR_RES, CONFIG_SCREEN_VER_RES);

static HAL::Display_CallbackFunc_t Disp_Callback = nullptr;

#if (DISP_USE_FPS_TEST == 1)
static float Display_GetFPS(uint32_t loopNum)
{
    uint32_t startTime = millis();
    for(uint32_t f = 0; f < loopNum; f++)
    {
        screen.fillScreen(TFT_RED);
        screen.fillScreen(TFT_GREEN);
        screen.fillScreen(TFT_BLUE);
    }
    uint32_t costTime = millis() - startTime;
    float fps = loopNum * 3 / (costTime / 1000.0f);

    screen.fillScreen(TFT_BLUE);
    screen.setTextSize(1);
    screen.setTextColor(TFT_WHITE);
    screen.setCursor(0, screen.height() / 2);

    screen.print("Frame:");
    screen.println(loopNum * 3);

    screen.print("Time:");
    screen.print(costTime);
    screen.println("ms");

    screen.print("FPS:");
    screen.println(fps);
    Serial.printf("FPS is: %.2f\n", fps);
    return fps;
}
#endif

static void Display_SPI_Send(const uint16_t* buf, uint32_t size)
{
    screen.startWrite();
    screen.setSwapBytes(false);
    if(DISP_USE_DMA) {
        screen.dmaWait();
        screen.pushPixelsDMA((uint16_t*)buf, size);
    } else {
        screen.pushPixels(buf, size);
    }
    screen.endWrite();
}

static void Display_SPI_DMA_Init()
{
    screen.initDMA();
}

void HAL::Display_Init()
{
    Serial.print("Display: init...");
    screen.init();
    screen.setRotation(0);
    screen.fillScreen(TFT_BLACK);

    screen.setTextWrap(true);
    screen.setTextSize(1);
    screen.setCursor(0, 0);
    screen.setTextFont(0);
    screen.setTextColor(TFT_WHITE, TFT_BLUE);

    if(DISP_USE_DMA) Display_SPI_DMA_Init();

#if(DISP_USE_FPS_TEST == 1) 
    Display_GetFPS(50);
#endif

 //   HAL::Backlight_SetGradual(1000, 1000);
    Serial.println("success");
}

void HAL::Display_DumpCrashInfo(const char* info)
{
#   define TEXT_HEIGHT_1   8
#   define TEXT_WIDTH_1    6
    HAL::Backlight_ForceLit(true);
    Serial.println("Display Crashed.");
    screen.fillScreen(TFT_BLUE);
    screen.setTextColor(TFT_WHITE);
    screen.setFreeFont(&FreeMono12pt7b);
    screen.setTextSize(2);
    screen.setCursor(0, 34);
    screen.print(":(");

    screen.setTextFont(0);

    screen.setTextSize(1);
    screen.setCursor(0, screen.height() / 2 - TEXT_HEIGHT_1 - 5);
    screen.println(info);
    screen.print("Press KEY to reboot..");
}

void HAL::Display_SetAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    screen.setAddrWindow(x0, y0, x1, y1);
}

void HAL::Display_SendPixels(const uint16_t* pixels, uint32_t len)
{
    Display_SPI_Send(pixels, len);
}

void HAL::Display_SetSendFinishCallback(Display_CallbackFunc_t func)
{
    Disp_Callback = func;
}
