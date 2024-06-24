#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include "i2c.h"

#define DS3231ReadMode   0xD1
#define DS3231WriteMode  0xD0
#define DS3231ControlReg 0x68
#define DS3231SecReg 0x00

typedef struct {
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_data;

void RTC_Init();

void RTC_SetDateTime(rtc_data *data);

void RTC_GetDateTime(rtc_data *data);

#endif