/************************************************************************
	TEST
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 09082022
Comment:
    Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
************************************************************************/
#ifndef _TEST_H_
	#define _TEST_H_

/*** File Library ***/
#include <inttypes.h>

/*** TEST ***/
typedef struct
{
	uint32_t testa;
}TEST;

TEST TESTenable(void);

#endif
/***EOF***/

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


