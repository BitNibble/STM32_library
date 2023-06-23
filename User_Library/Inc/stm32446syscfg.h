/******************************************************************************
	STM32 446 SYSCFG
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446SYSCFG_H_
	#define _STM32446SYSCFG_H_

/*** File Library ***/
#include <inttypes.h>
/***************************************/
/***** SYSCFG Bit Mapping TypeDef ****/
/***************************************/
typedef struct
{
	uint8_t a;
}SYSCFG_A, SYSCFG_B;
typedef struct
{
	uint16_t a;
}SYSCFG_C, SYSCFG_D;

/***************************************/
/********** SYSCFG TypeDef **********/
/***************************************/
typedef struct
{
	SYSCFG_TypeDef* reg;
	/*** Bit Mapping ***/

	/*** Other ***/
	void (*group1)( uint8_t parameter );
	void (*enable)(void);
}STM32446SYSCFGobj;


/*************************************/
/*********** INIC TEMPLATE ***********/
/*************************************/
STM32446SYSCFGobj STM32446SYSCFG_inic(void);



/***********************************************/
/********* Procedure & Function Header *********/
/***********************************************/
void syscfg_link(void);



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


