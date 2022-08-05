#include "lv_port.h"
#include "lvgl.h"
#include "HAL.h"

#define SCREEN_BUFFER_SIZE          (CONFIG_SCREEN_HOR_RES *  20)
#define SCREEN_USE_DOUBLE_BUFFER     1

static lv_disp_drv_t* disp_drv_p = NULL;

static void disp_flush_cb(lv_disp_drv_t* disp, const lv_area_t *area, lv_color_t* color_p)
{
    disp_drv_p = disp;

    const lv_coord_t w = (area->x2 - area->x1 + 1);
    const lv_coord_t h = (area->y2 - area->y1 + 1);
    const uint32_t len = w * h;

    HAL::Display_SetAddrWindow(area->x1, area->y1, area->x2, area->y2);
    HAL::Display_SendPixels((const uint16_t*)color_p, len);

    lv_disp_flush_ready(disp_drv_p);
}

void lv_port_disp_init()
{
    static lv_color_t lv_disp_buf[SCREEN_BUFFER_SIZE];
#if SCREEN_USE_DOUBLE_BUFFER
    static lv_color_t lv_disp_buf2[SCREEN_BUFFER_SIZE];
#endif
    static lv_disp_draw_buf_t disp_buf;
    
#if SCREEN_USE_DOUBLE_BUFFER
    lv_disp_draw_buf_init(&disp_buf, lv_disp_buf, lv_disp_buf2, SCREEN_BUFFER_SIZE);
#else
    lv_disp_draw_buf_init(&disp_buf, lv_disp_buf, NULL, SCREEN_BUFFER_SIZE);
#endif

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = CONFIG_SCREEN_HOR_RES;
    disp_drv.ver_res = CONFIG_SCREEN_VER_RES;
    disp_drv.physical_ver_res = 280;
    disp_drv.offset_y = 20;
    disp_drv.flush_cb = disp_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);
}
