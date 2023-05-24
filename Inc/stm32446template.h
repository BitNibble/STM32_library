/******************************************************************************
	STM32 446 TEMPLATE
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TEMPLATE_H_
	#define _STM32446TEMPLATE_H_

/*** Library ***/
#include <inttypes.h>

/*** Constant & Macros ***/

/*** Variable ***/
typedef struct{
	void (*inic)( uint8_t parameter );
	
}STM32446TEMPLATE1;

/*** Global Header ***/
STM32446TEMPLATE1 STM32446TEMPLATE1enable(void);

#endif
/*** EOF ***/

