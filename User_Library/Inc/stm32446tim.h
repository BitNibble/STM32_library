/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM_H_
	#define _STM32446TIM_H_

/*** Library ***/
#include <inttypes.h>

/*** TIM 9 ***/
typedef struct{
	TIM_TypeDef* reg;
	void (*inic)(void);
}STM32446TIM9;

/*** TIM 9 ***/
STM32446TIM9 STM32446TIM9enable(void);
void STM32446Tim9Inic(void);

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


