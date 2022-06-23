/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
//user include .h files
#include "bsp_adc.h"
#include "bsp_oled.h"
#include "bsp_rgb.h"
#include "uart_callback.h"
#include "GUI.h"
#include "bsp_rtc.h"
#include "bsp_gy302.h"
//数据定义
//////////////////////////////////ADC数据定义相关///////////////////////////
#define ADC_ERROR    50
uint16_t ADC_Buffer;  //核心值，这里判断之后稳定的值是这个
uint16_t ADC_Last_Buffer;
////////////////////////////////串口全局变量定义////////////////////////////
uint8_t RxBuf_2[RxBuf_2_SIZE];
uint8_t MainBuf_2[MainBuf_2_SIZE];
///////////////////////////////OLED模块模式变量定义////////////////////////////
GUI_InitTypedef GUI_InitStructure;
///////////////////////////////rtc变量////////////////////////////////////////
extern RTC_TimeTypeDef RTC_TIME;
extern RTC_DateTypeDef RTC_DATA;
///////////////////////////RGB结构体全局变量////////////////////////////////
extern RGB_Control_Init  RGB_InitStructure;
/////////////////////////////按键状态，采用上升沿触发///////////////////////////////
uint8_t k1_num=0;
uint8_t k2_num=0;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  //MX_I2C1_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
	MX_TIM1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
	MX_I2C1_Init();	
  //User_Init (necessary) 
  oled_Config();  //oled初始化
  RGB_Init();
  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, RxBuf_2, RxBuf_2_SIZE);  //开启USART2的DMA带_idle终端判断标志位的接收函数
  __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);   //关闭DMA半传输中断
  //USART3预留坑位 。那个语音模块就是个垃圾。直接删掉。。。。。。

  //test
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  { 
    ////////////////GY302初始化及读取值
    float cc;
    Write_BH1750(0x11);
    cc=Read_BH1750();
    GY302_display_test();   
    ////////////adc读取值，下面中断采取滤波算法，先进的稳值
    char bbc[10];
    ADC_ReadValue();
    sprintf(bbc,"ADC1:   %d  ",ADC_Buffer);
    OLED_ShowString(0,3,(uint8_t *)bbc,16);

    if(k1_num==1)
    {
      TIM1->CCR1=(uint32_t)cc*10;
      HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
      SPI_Draw_ChineseString("自动开",0,6,3);
    }
    else {SPI_Draw_ChineseString("自动关",0,6,3);}

    /////
    if(k2_num==1)
    {
      TIM1->CCR4=ADC_Buffer;
      HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
      SPI_Draw_ChineseString("调节开",60,6,3);
    }
    else{SPI_Draw_ChineseString("调节关",60,6,3);}

    HAL_Delay(100);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}
//callback
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC1)
	{
		ADC_Buffer=ADC_Last_Buffer;
		if(ADC_Buffer-ADC_Value>=ADC_ERROR||ADC_Value-ADC_Buffer>=ADC_ERROR)
		{
			//有变化
			ADC_Last_Buffer=ADC_Value;
		}
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==GPIO_PIN_3)  //人体触发上升沿中断
  {
		//人体热红外释电模块的坑
  }
  if(GPIO_Pin==GPIO_PIN_12)  //K1
  {   if(k1_num==1){k1_num=0;}else {k1_num=1;}
  }
  if(GPIO_Pin==GPIO_PIN_13)  //K2
  {
    if(k2_num==1){k2_num=0;}else {k2_num=1;}
  }
}
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
	//RTC中断，建议放些定时类的操作
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  //esp8266的串口回调函数
  //采用先进的IDLE中断结束判断标志位，同时采用DMA，也不会出现数据没有传输完成的情况
  __UART_CALLBack(huart,Size);
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

