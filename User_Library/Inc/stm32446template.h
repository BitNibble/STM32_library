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
/***************************************/
/***** Template Bit Mapping TypeDef ****/
/***************************************/
typedef struct
{
	uint8_t a;
}TEMPLATE_A, TEMPLATE_B;
typedef struct
{
	uint16_t a;
}TEMPLATE_C, TEMPLATE_D;

/***************************************/
/********** TEMPLATE1 TypeDef **********/
/***************************************/
typedef struct{
	/*** Bit Mapping ***/

	/*** Other ***/
	void (*group1)( uint8_t parameter );
}STM32446TEMPLATE1;

/*************************************/
/*********** INIC TEMPLATE ***********/
/*************************************/
STM32446TEMPLATE1 STM32446TEMPLATE1_inic(void);



/***********************************************/
/********* Procedure & Function Header *********/
/***********************************************/
void link(void);



/***********************************************/
/*** INTERRUPT HEADER ***/

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


