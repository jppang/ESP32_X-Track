#include "Arduino.h"
#include "App.h"
#include "HAL.h"
#include "lvgl.h"
#include "lv_port.h"

void demo(){
      /*Create an Arc*/
    lv_obj_t * arc = lv_arc_create(lv_scr_act());
    lv_obj_set_size(arc, 150, 150);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_value(arc, 10);
    lv_obj_center(arc);
    lv_scr_load(lv_scr_act());
}

void setup() {
  // put your setup code here, to run once:
    lv_init();

    HAL::HAL_Init();
    lv_port_init();

    App_Init();
  //  demo();
    HAL::Power_SetEventCallback(App_Uninit);
    HAL::Memory_DumpInfo();
}

void loop() {
  // put your main code here, to run repeatedly:
    HAL::HAL_Update();
    vTaskDelay( 5 / portTICK_PERIOD_MS);
    lv_timer_handler();
    lv_tick_inc(5);
//    __wfi();
}

