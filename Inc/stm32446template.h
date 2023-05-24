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

/*** Constant & Macros ***/

/*** Variable ***/
typedef struct{
	void (*inic)(void);
}STM32446TEMPLATE;

/*** Global Header ***/
STM32446TEMPLATE STM32446TEMPLATEenable(void);

#endif
/*** EOF ***/

