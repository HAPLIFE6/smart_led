#include "bsp_oled.h"
#include "oledfont.h"
#include "bsp_w25q64.h"
void IIC_Wait_Ask(void)
{
	/*
	uint8_t count;
	uint8_t READ_SDA;
	SDA_IN();
	I2C_SCL_SET();
	delay_us(2);
	READ_SDA=GPIO_ReadInputDataBit(I2Cx_GPIO_SDA_PORT, I2Cx_GPIO_SDA_PIN);
	while(READ_SDA)
	{
		READ_SDA=GPIO_ReadInputDataBit(I2Cx_GPIO_SDA_PORT, I2Cx_GPIO_SDA_PIN);
		count++;
		if(count>=250)
		{
			IIC_Stop();
			return 1;
		}
	}
	I2C_SCL_SET();
	delay_us(2);
	return 0;
	*/
	//I2C_SCL_SET();
	//I2C_SCL_RES();
	
}
void Write_IIC_Byte(uint8_t data)
{
	//模拟iic需要使用。
    //这里使用的是硬件iic所以这部分删除掉了
}
//дcmd
void Write_IIC_Command(uint8_t command)
{
  uint8_t *pData;
  pData=&command;
  HAL_I2C_Mem_Write(&hi2c1,OLED_ADDR,0x00, I2C_MEMADD_SIZE_8BIT,pData,1,100);
}
//дdata
void Write_IIC_Data(uint8_t data)
{
  uint8_t *pData;
  pData=&data;
  HAL_I2C_Mem_Write(&hi2c1,OLED_ADDR,0x40, I2C_MEMADD_SIZE_8BIT,pData,1,100);
}
void OLED_Init(void)
{
	Write_IIC_Command(0xAE);
	Write_IIC_Command(0x20);
	Write_IIC_Command(0x10);
	Write_IIC_Command(0xb0);
	Write_IIC_Command(0xc8);
	Write_IIC_Command(0x00);
	Write_IIC_Command(0x10);
	Write_IIC_Command(0x40);
	Write_IIC_Command(0xff);
	Write_IIC_Command(0xa1);
	Write_IIC_Command(0xa6);
	Write_IIC_Command(0xa8);
	Write_IIC_Command(0x3F);
	Write_IIC_Command(0xa4);
	Write_IIC_Command(0xd3);
	Write_IIC_Command(0x00);
	Write_IIC_Command(0xd5);
	Write_IIC_Command(0xf0);
	Write_IIC_Command(0xd9);
	Write_IIC_Command(0x22);
	Write_IIC_Command(0xda);
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb);
	Write_IIC_Command(0x20);
	Write_IIC_Command(0x8d);
	Write_IIC_Command(0x14);
	Write_IIC_Command(0xaf);
}	
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		Write_IIC_Command(0xb0+i);  
		Write_IIC_Command(0x00);
		Write_IIC_Command(0x10);   
		for(n=0;n<128;n++)Write_IIC_Data(0); 
	}
}	
//x的取值范围0-127
//y的取值范围0-7
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ Write_IIC_Command(0xb0+y);
	Write_IIC_Command(((x&0xf0)>>4)|0x10);
	Write_IIC_Command(x&0x0f); 
} 
//x,y,chr,size==6|16
void OLED_ShowNum(uint8_t x,uint8_t y,uint8_t chr,uint8_t size)
{
	//uint8_t zhengshu;
    //uint8_t xiaoshu;
	//xiaoshu=chr%10;
    //zhengshu=(chr-xiaoshu)/10;
	OLED_Set_Pos(x,y);
	if(size==6)
	{
		for(uint8_t i=0;i<6;i++)
		{
			Write_IIC_Data(F6x8[chr-32][i]);
		}
	}
	if(size==16)
	{
		uint8_t t;
		OLED_Set_Pos(x,y);	
    for(t=0;t<8;t++)
		{
			Write_IIC_Data(F8X16[chr-32][t]);
        }	
		OLED_Set_Pos(x,y+1);	
    for(t=8;t<16;t++)
		{
			Write_IIC_Data(F8X16[chr-32][t]);
        }				
	}
}
//x,y,chr,size==6|16
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *OLED_String,uint8_t size)
{
	uint8_t i,c;
	uint8_t num=0;
	uint8_t a=0;
	OLED_Set_Pos(x,y);
	while(OLED_String[a]!='\0')
	{
		c=OLED_String[a]-32;
			if(size==6)
		{
			for(i=0;i<6;i++)
			{
				Write_IIC_Data(F6x8[c][i]);
			}
			a++;
		}
		if(size==16)
		{
			for(i=0;i<8;i++)
			{
				Write_IIC_Data(F8X16[c][i]);
			}
		OLED_Set_Pos(x+num,y+1);
			for(i=8;i<16;i++)
			{
				Write_IIC_Data(F8X16[c][i]);
			}
			a++;
			num=num+8;
			OLED_Set_Pos(x+num,y);
		}
	}
}
void oled_Config(void)
{
	//
	OLED_Init();
	OLED_Clear();
}
//没啥用，原来的hz库操作，但是我都删掉了
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t hanziku[32])
{    			    
	uint8_t t;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
	{
		Write_IIC_Data(hanziku[t]);
    }	
	OLED_Set_Pos(x,y+1);	
    for(t=16;t<32;t++)
	{
		Write_IIC_Data(hanziku[t]);
    }				
}
////user

//******************************************************************
//函数名：  SPI_Draw_Chinese
//作者：    ZSY
//日期：    2022-03-20
//功能：    显示一个汉字
//输入参数：x,y :起点坐标
// 			*ch :汉字数组（这里采用列行式，逆向输出）
//*ch为一个【32】位的汉字取模数组指针，例如传入uint8_t hanzi[32]={0x00,0x00...};
//******************************************************************  
void SPI_Draw_Chinese(uint16_t x,uint16_t y,uint8_t *ch)
{
	uint16_t x_buffer=x;
	uint16_t y_buffer=y;
	for(int t=0;t<16;t++)
	{
		for(int i=0;i<8;i++)
		{
			if((*ch&0x01)==0x01)
			{
				//LCD_DrawPoint(x,y+i);//画一个点
			}
			*ch=*ch>>1;
		}
		ch++;
		x=x+1;
	}

	x=x_buffer;
	y=y_buffer;

	for(int t=0;t<16;t++)
	{
		for(int i=0;i<8;i++)
		{
			if((*ch&0x01)==0x01)
			{
				//LCD_DrawPoint(x,y+i+7);//画一个点
			}
			*ch=*ch>>1;
		}
		ch++;
		x=x+1;
	}
}
static uint32_t SPI_ChineseWrite(uint8_t d,uint8_t b)
{
uint8_t a[2]={d,b};
uint32_t addr;
uint32_t pianyi;
//strcpy(a,chinese);
addr=((a[0]<<8)+a[1]);
pianyi=(a[0]-0xb0);
addr=0xc80*pianyi+(a[1]-0xa0)*32;
return addr;
}
/*
str为你想要展示的汉字.
x,y为设置的坐标
length为汉字的长度
*/
void SPI_Draw_ChineseString(uint8_t *str,uint8_t x,uint8_t y,uint8_t length)
{
	uint8_t chr[100];
	uint8_t Chinese_RX_Buffer[32]={0};
	strcpy(chr,str);
	W25QXX_Read(Chinese_RX_Buffer,0x000000,32); //预读取一次，否则有解决不了的BUG。。。。。（外挂法）
	memset(Chinese_RX_Buffer,0,32);
	for(int i=0;i<length*2;i=i+2)
	{
		W25QXX_Read(Chinese_RX_Buffer,0x00000+SPI_ChineseWrite(chr[i],chr[i+1]),32);
		OLED_ShowCHinese(x+(16*i)/2,y,Chinese_RX_Buffer);  //debug
	}
}

