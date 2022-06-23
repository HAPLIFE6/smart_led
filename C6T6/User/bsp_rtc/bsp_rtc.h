#ifndef __BSP_RTC_H
#define __BSP_RTC_H

#include "main.h"
#include "rtc.h"

extern RTC_TimeTypeDef RTC_TIME;
extern RTC_DateTypeDef RTC_DATA;

void Get_Time(void); //获取时间和日期信息，保存在上面两个结构体里面
#endif
