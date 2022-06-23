#ifndef __BSP_OLED_H
#define __BSP_OLED_H

#include "main.h"
#include "i2c.h"

#define OLED_ADDR                           0x78           

void IIC_Wait_Ask(void);
void Write_IIC_Byte(uint8_t data);
void Write_IIC_Command(uint8_t command);
void Write_IIC_Data(uint8_t data);
void OLED_Init(void);
void OLED_Clear(void) ;
void oled_Config(void);

void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_ShowNum(uint8_t x,uint8_t y,uint8_t chr,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *OLED_String,uint8_t size);

void SPI_Draw_ChineseString(uint8_t *str,uint8_t x,uint8_t y,uint8_t length);
void SPI_Draw_Chinese(uint16_t x,uint16_t y,uint8_t *ch);  //ch为传入的32位数组数据
/*
此产品为IIC驱动的0.96寸OLED模块，主控采用SSD1306
寻址方式为先进行竖排寻址，每次每页每竖排有8个bit；
竖排每一页为8位，写满就自动进入到下一个竖列
x最多的是127，y最多的是7.
注意几个点：写cmd三次。第一次写小x，第二次写y，第三次写大x
*/
#endif  //BSP_OLED_H
