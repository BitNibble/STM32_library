/******************************************************************************
	STM32 446 TEMPLATE
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TEMPLATE_H_
	#define _STM32446TEMPLATE_H_

/*** Library ***/
#include <inttypes.h>

/*** TEMPLATE1 ***/
typedef struct{
	void (*inic)( uint8_t parameter );
	
}STM32446TEMPLATE1;

/*** TEMPLATE1 ***/
STM32446TEMPLATE1 STM32446TEMPLATE1enable(void);
void STM32446Template1Inic( uint8_t parameter );

#endif

/*** EOF ***/


