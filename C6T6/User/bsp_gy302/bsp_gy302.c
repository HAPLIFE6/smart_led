#include "bsp_gy302.h"  
#include "bsp_oled.h"	
unsigned char lux_buffer[5];
void conversion(double lux)  //  数据转换出 万,千,百,个,十,
{   uint32_t temp_data=(uint32_t)lux;
    unsigned char   ge,shi,bai,qian,wan;            //显示变量
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 	
    lux_buffer[0]=wan;lux_buffer[1]=qian;lux_buffer[2]=bai;lux_buffer[3]=shi;lux_buffer[4]=ge;
}
void Write_BH1750(uint8_t command)  //写命令 ,命令在.h文件中
{
    uint8_t temp[1]={command};//mode2 0x11
    HAL_I2C_Master_Transmit(&hi2c1,GY302_Write_addr,temp,1,0xff);
    HAL_Delay(100);
}
float Read_BH1750(void)             //读数据，返回值为（float） lux
{
    float lux;
    uint8_t ReadData[2]={0};
    HAL_I2C_Master_Receive(&hi2c1,GY302_Read_addr,ReadData,2,0xff);
    lux=(float)(ReadData[0]<<8|ReadData[1]);
    lux=(double)lux/1.2;
    return lux;
}
float BH1750_Start_OneTimeMode(void)   //用于再次启动单次读取模式
{   float read_buffer;
    Write_BH1750(Power_On);
    Write_BH1750(One_Time_Read_Mode2);
    read_buffer=Read_BH1750();
    conversion(read_buffer);
    return read_buffer;
}
void GY302_display_test(void)  //在OLED上面显示，观测LUX的变化；
{
    conversion(Read_BH1750());
    OLED_ShowString(0,0,"LUX:",16);
    OLED_ShowString(60,0,(uint8_t *)lux_buffer,16);
}
/* main.c examples

  Write_BH1750(0x11);  //先写指令，指令含义详细看数据手册
  Read_BH1750();        //读数据，返回float值
  GY302_display_test();  //测试显示，将其显示在oled上

*/
