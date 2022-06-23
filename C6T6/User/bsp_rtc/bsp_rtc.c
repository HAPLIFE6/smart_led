#include "bsp_rtc.h"
RTC_TimeTypeDef RTC_TIME;
RTC_DateTypeDef RTC_DATA;
void Get_Time()
{
HAL_RTC_GetTime(&hrtc,&RTC_TIME,RTC_FORMAT_BIN);
HAL_RTC_GetDate(&hrtc,&RTC_DATA,RTC_FORMAT_BIN);
//printf("%02d :%02d :%02d\n",RTC_TIME.Hours,RTC_TIME.Minutes,RTC_TIME.Seconds);
//printf("%02d /%02d /%02d\n",RTC_DATA.Year+2000,RTC_DATA.Month,RTC_DATA.Date);
}

/*
//开启RTC的秒中断：
__HAL_RTC_SECOND_ENABLE_IT(&hrtc,RTC_IT_SEC);  //RTC的秒中断


*/
