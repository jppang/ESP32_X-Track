#include "Arduino.h"
#include "App.h"
#include "HAL.h"
#include "lvgl.h"
#include "lv_port.h"

static void set_angle(void * obj, int32_t v)
{
    lv_arc_set_value((lv_obj_t*)obj, v);
}

void demo(){
    /*Create an Arc*/
    lv_obj_t * arc = lv_arc_create(lv_scr_act());
    lv_arc_set_rotation(arc, 270);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_center(arc);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);
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

