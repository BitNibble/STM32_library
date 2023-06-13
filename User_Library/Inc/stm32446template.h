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

/*** File Library ***/
#include <inttypes.h>

/*** TEMPLATE1 TypeDef ***/
typedef struct{
	void (*inic)( uint8_t parameter );
}STM32446TEMPLATE1;

STM32446TEMPLATE1 STM32446TEMPLATE1enable(void);

/*** Template1 Procedure & Function Header ***/
void STM32446Template1Inic( uint8_t parameter );
/*** Template1 Bit Mapping Header ***/

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


