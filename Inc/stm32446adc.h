/******************************************************************************
	STM32 446 ADC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446ADC_H_
	#define _STM32446ADC_H_

/*** ADC_Common ***/
typedef struct
{
	ADC_Common_TypeDef* reg;
}STM32446ADCCOMMONobj;

/*** ADC 1 ***/
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

typedef struct{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	STM32446ADC1single single;
}STM32446ADC1;

/*** ADC 1 ***/
STM32446ADC1 STM32446ADC1enable(void);
void STM32446Adc1Inic(void);
void STM32446Adc1VBAT(void);
void STM32446Adc1TEMP(void);
void STM32446Adc1Start(void);
double STM32446Adc1Read(void);
void STM32446Adc1Restart(void);
void STM32446Adc1Stop(void);

#endif

/*** EOF ***/


