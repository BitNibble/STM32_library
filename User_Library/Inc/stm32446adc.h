/******************************************************************************
	STM32 446 ADC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446ADC_H_
	#define _STM32446ADC_H_

/*** Library ***/
#include <inttypes.h>

/*** ADC_Common ***/
typedef struct
{
	ADC_Common_TypeDef* reg;
}STM32446ADCCOMMONobj;

typedef struct
{
	void (*inic)(void);
	void (*vbat)(void);
	void (*temp)(void);
	void (*start)(void);
	double (*read)(void);
	void (*restart)(void);
	void (*stop)(void);
}STM32446ADC1single;

// ADC -> ADC1
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		STM32446ADC1single single;
		void (*clock)(void);
	#endif
}STM32446ADC1obj;

// ADC -> ADC2
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		void (*enable)(void);
	#endif
}STM32446ADC2obj;

// ADC -> ADC3
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		void (*enable)(void);
	#endif
}STM32446ADC3obj;

/*** ADC1 ***/
void STM32446Adc1Clock(void);
void STM32446Adc1Inic(void);
void STM32446Adc1VBAT(void);
void STM32446Adc1TEMP(void);
void STM32446Adc1Start(void);
double STM32446Adc1Read(void);
void STM32446Adc1Restart(void);
void STM32446Adc1Stop(void);

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


