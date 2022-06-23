#ifndef __UART_CALLBACK_H
#define  __UART_CALLBACK_H

#include "main.h"

#define RxBuf_2_SIZE   50
#define MainBuf_2_SIZE 50

#define RxBuf_3_SIZE   50
#define MainBuf_3_SIZE 50


extern uint8_t RxBuf_2[RxBuf_2_SIZE];
extern uint8_t MainBuf_2[MainBuf_2_SIZE];
extern uint8_t RxBuf_3[RxBuf_3_SIZE];
extern uint8_t MainBuf_3[MainBuf_3_SIZE];

void __UART_CALLBack(UART_HandleTypeDef *huart, uint16_t Size);

#endif 
