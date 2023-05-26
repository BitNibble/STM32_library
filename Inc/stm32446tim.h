/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM_H_
	#define _STM32446TIM_H_

/*** Library ***/
#include <inttypes.h>

/*** Constant & Macros ***/

/*** Variable ***/
typedef struct{
	void (*inic)(void);
	
}STM32446TIM9;

/*** Global Header ***/
STM32446TIM9 STM32446TIM9enable(void);

#endif
/*** EOF ***/

