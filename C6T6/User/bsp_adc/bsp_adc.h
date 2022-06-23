#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "main.h"
#include "adc.h"

void  ADC_ReadValue(void);
void ADC_StopReadValue(void);
//extern uint16_t ADC_Value[3];
extern uint16_t ADC_Value;
extern uint16_t ADC_Value_buffer[3];
#endif
