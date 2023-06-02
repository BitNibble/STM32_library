/******************************************************************************
	STM32 446 RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446RTC_H_
	#define _STM32446RTC_H_

/*** File Library ***/
#include <inttypes.h>

/*** RTC ***/
typedef struct{
	RTC_TypeDef* reg;
	void (*clock)(void);
	uint8_t (*inic)(uint8_t clock);
	void (*Day)(uint8_t day);
	void (*Month)(uint8_t month);
	void (*WeekDay)(uint8_t weekday);
	void (*Year)(uint8_t year);
	void (*Hour)(uint8_t hour);
	void (*Minute)(uint8_t minute);
	void (*Second)(uint8_t second);
	void (*dr2vec)(char* rtc_vect);
	void (*tr2vec)(char* rtc_vect);
	void (*RegWrite)(volatile uint32_t* reg, uint32_t data);
}STM32446RTC;

STM32446RTC STM32446RTCenable(void);
void STM32446RtcClock(void);
uint8_t STM32446RtcInic(uint8_t clock);
void STM32446RtcDay(uint8_t day);
void STM32446RtcMonth(uint8_t month);
void STM32446RtcWeekDay(uint8_t weekday);
void STM32446RtcYear(uint8_t year);
void STM32446RtcHour(uint8_t hour);
void STM32446RtcMinute(uint8_t minute);
void STM32446RtcSecond(uint8_t second);
void STM32446Rtcdr2vec(char* rtc_vect);
void STM32446Rtctr2vec(char* rtc_vect);
void STM32446RtcRegWrite(volatile uint32_t* reg, uint32_t data);

#endif

/*** EOF ***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/


