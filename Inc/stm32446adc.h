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

/*** Library ***/

/*** Constant & Macros ***/

/*** Variable ***/

/*** Header ***/
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

typedef struct{
	STM32446ADC1single single;
}STM32446ADC1;

STM32446ADC1 STM32446ADC1enable(void);

#endif
/*** EOF ***/

