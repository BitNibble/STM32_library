/******************************************************************************
	STM32 446 ADC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446ADC_H_
	#define _STM32446ADC_H_

// ADC_Common
typedef struct
{
	ADC_Common_TypeDef* reg;
}STM32446ADCCOMMONobj;

/*** ADC 1 ***/
// ADC1
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

// ADC1
typedef struct{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;

	STM32446ADC1single single;
}STM32446ADC1;

STM32446ADC1 STM32446ADC1enable(void);

// ADC -> ADC1
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	STM32446ADC1 (*enable)(void);
}STM32446ADC1obj;

/*** ADC 2 ***/
// ADC -> ADC2
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	void (*enable)(void);
}STM32446ADC2obj;

/*** ADC 3 ***/
// ADC -> ADC3
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	void (*enable)(void);
}STM32446ADC3obj;

#endif
/*** EOF ***/


