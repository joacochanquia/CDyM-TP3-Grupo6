#ifndef RTC_H
#define RTC_H

#include "i2c.h"

#define C_Ds1307ReadMode_U8   0xD1u
#define C_Ds1307WriteMode_U8  0xD0u
#define C_Ds1307ControlRegAddress_U8 0x07u
#define C_Ds1307SecondRegAddress_U8 0x00u

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_t;

void RTC_Init(void);

void RTC_SetDateTime(rtc_t *rtc);

void RTC_GetDateTime(rtc_t *rtc);

#endif