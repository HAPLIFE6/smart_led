#include "GUI.h"
#include "bsp_oled.h"
#include "bsp_w25q64.h"
#include "spi.h"
void GUI_Init(GUI_InitTypedef *GUI_InitStructure)
{
    if(GUI_InitStructure->bk_mode==0)
    {
        OLED_Clear();
        SPI_Draw_ChineseString("�ƿ���",0,0,3);
        SPI_Draw_ChineseString("�׵���",0,2,3);
        SPI_Draw_ChineseString("�Ƶ���",0,4,3);
        SPI_Draw_ChineseString("�Զ�����",0,6,4);
        OLED_ShowString(100,(GUI_InitStructure->bk1_point)*2,"**",16);
    }
}
//����ļ���ʱ��������ʱ����Ϊ����OLED����ʾ����ģ�������ʾ���治����ô��Ҫ�������Ը��ӡ�
//����ѡ��������GUI�����ѡ��freertos��ֲST�ٷ���TOUCHGFX
//������ļ�������ûʲôʵ���Ե����ã����û�����
