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

/***Library***/
#include <inttypes.h>
/***Constant & Macro***/
/***Global Variable***/
typedef struct
{
	/******/
	void (*bit)(uint8_t bool);
	void (*ibyte)(uint8_t byte);
	void (*byte)(uint8_t byte);
	void (*out)(void);
}HC595;
/***Header***/
HC595 HC595enable(volatile uint32_t *ddr, volatile uint32_t *port, uint8_t datapin, uint8_t clkpin, uint8_t outpin);

#endif
/***EOF***/

