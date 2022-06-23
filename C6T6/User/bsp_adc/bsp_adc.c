#include "bsp_adc.h"
//uint16_t ADC_Value[3];
uint16_t ADC_Value;
void  ADC_ReadValue(void)
{
		//HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_Value, 20);
	
    HAL_ADC_Start_IT(&hadc1);
    ADC_Value=HAL_ADC_GetValue(&hadc1);
}
void ADC_StopReadValue(void)
{
    HAL_ADC_Stop_IT(&hadc1);
}
/*示例程序
    char bbc[10];
    ADC_ReadValue();
    sprintf(bbc,"ADC1:%d  ",ADC_Buffer);
    OLED_ShowString(0,0,(uint8_t *)bbc,16);

    HAL_Delay(100);
*/
