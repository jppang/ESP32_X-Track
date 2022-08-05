#include "HAL.h"
#include "lvgl.h"

/**
  * @brief  �������Ƚ��䣬��lv_anim����
  * @param  obj:����
  * @param  brightness:����ֵ
  * @retval None
  */
static void Backlight_AnimCallback(void * obj, int32_t brightness)
{
    HAL::Backlight_SetValue(brightness);
}

/**
  * @brief  �����ʼ��
  * @param  ��
  * @retval ��
  */
void HAL::Backlight_Init()
{
    /*PWM��ʼ����1000����20KHzƵ��*/
    //PWM_Init(CONFIG_SCREEN_BLK_PIN, 1000, 20000);
    ledcSetup(0, 5000, 10);
    ledcAttachPin(CONFIG_SCREEN_BLK_PIN, 0);
    Backlight_SetValue(0);
}

/**
  * @brief  �������ã�����Ч��
  * @param  target:Ŀ������(0~1000 -> 0~100%)
  * @retval ��
  */
void HAL::Backlight_SetGradual(uint16_t target, uint16_t time)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)Backlight_AnimCallback);
    lv_anim_set_values(&a, Backlight_GetValue(), target);
    lv_anim_set_time(&a, time);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);

    lv_anim_start(&a);
}

/**
  * @brief  ��ȡ��������
  * @param  ��
  * @retval ��ǰ����(0~1000 -> 0~100%)
  */
uint16_t HAL::Backlight_GetValue()
{
/*    return Timer_GetCompare(
               PIN_MAP[CONFIG_SCREEN_BLK_PIN].TIMx,
               PIN_MAP[CONFIG_SCREEN_BLK_PIN].TimerChannel
           ); */
      return ledcRead(0);
}

/**
  * @brief  ���ñ�������
  * @param  val: ����(0~1000 -> 0~100%)
  * @retval ��
  */
void HAL::Backlight_SetValue(int16_t val)
{
    CM_VALUE_LIMIT(val, 0, 1000);
    //analogWrite(CONFIG_SCREEN_BLK_PIN, val);
    ledcWrite(0, val);
}

/**
  * @brief  ����ǿ�Ƶ���
  * @param  en: ����ʹ��
  * @retval ��
  */
void HAL::Backlight_ForceLit(bool en)
{
    pinMode(CONFIG_SCREEN_BLK_PIN, OUTPUT);
    digitalWrite(CONFIG_SCREEN_BLK_PIN, en);
}
