/************************************************************************
	74HC595
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: 74HC595
Date: 25102020
Comment:
	tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RET
************************************************************************/
#ifndef _74HC595_H_
	#define _74HC595_H_

/*** File Library ***/
#include <inttypes.h>

/*** File TypeDef ***/
typedef struct{
	uint8_t HC595_datapin;
	uint8_t HC595_clkpin;
	uint8_t HC595_outpin;
	volatile uint32_t *hc595_DDR;
	volatile uint32_t *hc595_PORT;
}hc595parameter;

/*** 74HC595 ***/
typedef struct
{
	hc595parameter par;
	/******/
	void (*bit)(hc595parameter* par, uint8_t bool);
	void (*ibyte)(hc595parameter* par, uint8_t byte);
	void (*byte)(hc595parameter* par, uint8_t byte);
	void (*out)(hc595parameter* par);
}HC595;

HC595 HC595enable(volatile uint32_t *ddr, volatile uint32_t *port, uint8_t datapin, uint8_t clkpin, uint8_t outpin);

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


