#include "bsp_rgb.h"
RGB_Control_Init  RGB_InitStructure;
void RGB_Init(void)
{
    RGB_InitStructure.White=LED_ON;
    RGB_InitStructure.Yellow=LED_ON;
    RGB_InitStructure.Red=LED_ON;
    RGB_InitStructure.Green=LED_ON;
    RGB_InitStructure.Blue=LED_ON;
    RGB_InitStructure.White_Pulse=0;
    RGB_InitStructure.Yellow_Pulse=0;
    RGB_InitStructure.Red_Pulse=0;
    RGB_InitStructure.Green_Pulse=0;
    RGB_InitStructure.Blue_Pulse=0;
}
void RGB_Control(RGB_Control_Init *Fiveled )
{
    TIM1->CCR1=(Fiveled->White_Pulse)*(uint8_t)Fiveled->White;
    TIM1->CCR4=(Fiveled->Yellow_Pulse)*(uint8_t)Fiveled->Yellow;
    TIM3->CCR1=(Fiveled->Red_Pulse)*(uint8_t)Fiveled->Red;
    TIM3->CCR3=(Fiveled->Green_Pulse)*(uint8_t)Fiveled->Green;
    TIM3->CCR4=(Fiveled->Blue_Pulse)*(uint8_t)Fiveled->Blue;
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
}
void RGB_Turnoff(void)
{
    HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_4);
    HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
}
/*  test 测试
  RGB_Control_Init rgb;
  rgb.White=0;rgb.White_Pulse=30000;
  RGB_Control(&rgb);
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
*/
