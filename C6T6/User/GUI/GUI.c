#include "GUI.h"
#include "bsp_oled.h"
#include "bsp_w25q64.h"
#include "spi.h"
void GUI_Init(GUI_InitTypedef *GUI_InitStructure)
{
    if(GUI_InitStructure->bk_mode==0)
    {
        OLED_Clear();
        SPI_Draw_ChineseString("灯开关",0,0,3);
        SPI_Draw_ChineseString("白调光",0,2,3);
        SPI_Draw_ChineseString("黄调光",0,4,3);
        SPI_Draw_ChineseString("自动调节",0,6,4);
        OLED_ShowString(100,(GUI_InitStructure->bk1_point)*2,"**",16);
    }
}
//这个文件暂时保留，当时想着为了做OLED的显示界面的，发现显示界面不是那么必要而且稍显复杂。
//建议选择其他的GUI库或者选择freertos移植ST官方的TOUCHGFX
//故这个文件在这里没什么实质性的作用，给用户保留
