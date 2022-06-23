#include "uart_callback.h"
#include "usart.h"
#include "bsp_rgb.h"
#include "math.h"
extern RGB_Control_Init  RGB_InitStructure;
uint8_t UART2_length;  //给传输次数做计数的
//函数定义
static uint16_t PWM_calculate(char a,char b,char c,uint8_t num);
static void UART2_Cmd_Handle(uint8_t *cmd);
///////////////////////////////////////////////////////////////////////////////////
void __UART_CALLBack(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance==USART2)
    {
        HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *) RxBuf_2, RxBuf_2_SIZE);
		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
        UART2_Cmd_Handle((uint8_t *)RxBuf_2);
        memset(RxBuf_2,0,RxBuf_2_SIZE);
        RGB_Control(&RGB_InitStructure);
    }
}
static void UART2_Cmd_Handle(uint8_t *cmd)
{
    uint8_t temp_cmd_buffer[RxBuf_2_SIZE]={0};
    memcpy(temp_cmd_buffer,cmd,RxBuf_2_SIZE);
		UART2_length=strlen((char *)temp_cmd_buffer)-2;
    if(temp_cmd_buffer[1]=='1')
    {
        switch (temp_cmd_buffer[2])
        {
            case '0':if(temp_cmd_buffer[4]=='0'){RGB_InitStructure.White=0;}else{RGB_InitStructure.White=1;}break;
            case '1':if(temp_cmd_buffer[4]=='0'){RGB_InitStructure.Yellow=0;}else{RGB_InitStructure.Yellow=1;}break;
            case '2':if(temp_cmd_buffer[4]=='0'){RGB_InitStructure.Red=0;RGB_InitStructure.Green=0;RGB_InitStructure.Blue=0;}
                    else{RGB_InitStructure.Red=1;RGB_InitStructure.Green=1;RGB_InitStructure.Blue=1;}break;

            case '3':if(temp_cmd_buffer[4]=='1'){RGB_InitStructure.White=0;RGB_InitStructure.Yellow=0;RGB_InitStructure.Red=0;RGB_InitStructure.Green=0;RGB_InitStructure.Blue=0;}break;

        }
    }
    if(temp_cmd_buffer[1]=='2')
    {
        switch (temp_cmd_buffer[2])
        { 
            case '0': RGB_InitStructure.White_Pulse=PWM_calculate(temp_cmd_buffer[4],temp_cmd_buffer[5],temp_cmd_buffer[6],UART2_length)*16;break;
            case '1': RGB_InitStructure.Yellow_Pulse=PWM_calculate(temp_cmd_buffer[4],temp_cmd_buffer[5],temp_cmd_buffer[6],UART2_length)*16;break;
            case '2': RGB_InitStructure.Red_Pulse=PWM_calculate(temp_cmd_buffer[4],temp_cmd_buffer[5],temp_cmd_buffer[6],UART2_length)*16;break;
            case '3': RGB_InitStructure.Green_Pulse=PWM_calculate(temp_cmd_buffer[4],temp_cmd_buffer[5],temp_cmd_buffer[6],UART2_length)*16;break;
            case '4': RGB_InitStructure.Blue_Pulse=PWM_calculate(temp_cmd_buffer[4],temp_cmd_buffer[5],temp_cmd_buffer[6],UART2_length)*16;break;
        }
    }
    if(temp_cmd_buffer[1]=='3')
    {
        switch (temp_cmd_buffer[2])
        {
            case '0':            break;//添加场景处理函数  
            case '1':            break;//添加场景处理函数  
            case '2':            break;//添加场景处理函数  
            case '3':            break;//添加场景处理函数  
        }
    }
}   
static uint16_t PWM_calculate(char a,char b,char c,uint8_t num)   //example: '1' +'2' +'3' =123;
{
    uint16_t result;
    if(num==5) result=(a-0x30);
			if(num==6) result=(a-0x30)*10+(b-0x30);
				if(num==7) result=(a-0x30)*100+(b-0x30)*10+(c-0x30);
					return result;
}
