/************************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 16032021
Comment:
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
************************************************************************/
#ifndef _EXPLODE_H_
	#define _EXPLODE_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global TypeDef ***/
typedef struct {
	uint32_t XI;
	uint32_t XF;
	uint32_t HH;
	uint32_t LL;
	uint32_t LH;
	uint32_t HL;
}explodeparameter;

/*** EXPLODE ***/
typedef struct {
	/***Variable***/
	explodeparameter par;
	// PROTOTYPES VTABLE
	void (*update)(explodeparameter* par, uint32_t x);
}EXPLODE;

EXPLODE EXPLODEenable(void);

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


