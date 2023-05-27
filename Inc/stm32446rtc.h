/******************************************************************************
	STM32 446 RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446RTC_H_
	#define _STM32446RTC_H_

/*** Library ***/
#include <inttypes.h>

typedef struct{
	RTC_TypeDef* reg;

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

/*** Global Header ***/
STM32446RTC STM32446RTCenable(void);

// RTC
typedef struct
{
	RTC_TypeDef* reg;
	STM32446RTC (*enable)(void);
}STM32446RTCobj;

#endif
/*** EOF ***/


