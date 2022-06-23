#ifndef __BSP_RGB_H
#define __BSP_RGB_H

#include "main.h"
#include "tim.h"

#define LED_OFF  0
#define LED_ON   1
typedef struct {
    bool White;
    bool Yellow;
    bool Red;
    bool Green;
    bool Blue;
    uint16_t White_Pulse;
    uint16_t Yellow_Pulse;
    uint16_t Red_Pulse;
    uint16_t Green_Pulse;
    uint16_t Blue_Pulse;

}RGB_Control_Init;

extern RGB_Control_Init  RGB_InitStructure;
void RGB_Init(void);
void RGB_Control(RGB_Control_Init *Fiveled );
void RGB_Turnoff(void);
#endif
