#ifndef __BSP_GY302_H
#define __BSP_GY302_H

#include "main.h"
#include "i2c.h"
/*
    需要的参数： @unsigned char lux_buffer[5];  数组内保存了转换后的 万,千,百,个,十 位，用于OLED显示
                @Read_BH1750()  或  BH1750_Start_OneTimeMode()  返回的(float )lux值，实际的lux值
*/
#define GY302_Write_addr   0x46
#define GY302_Read_addr   0x47

//Command sum
#define Power_On              1    //记得开POWER ON
#define Power_Down            0
#define  Continue_Read_Mode1  0x10
#define Continue_Read_Mode2   0x11
#define One_Time_Read_Mode1   0x20
#define One_Time_Read_Mode2   0x21

void conversion(double lux);
void Write_BH1750(uint8_t command);
float Read_BH1750(void);
float BH1750_Start_OneTimeMode(void);
void GY302_display_test(void);
#endif //__BSP_GY302_H
