/******************************************************************************
	STM32 446 SRAM
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 13062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446SRAM_H_
	#define _STM32446SRAM_H_

/*** Library ***/
#include <inttypes.h>

/*** SRAM TypeDef ***/
typedef struct
{
	#if defined(_STM32446SRAM_H_)
		/*** Bit Mapping ***/
		/*** Other ***/
		void (*access)(void);
	#endif
}STM32446SRAMobj;

/***** SRAM Procedure & Function Header ******/
void STM32446SramAccess(void);
/*** SRAM Bit Mapping Header ***/

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


