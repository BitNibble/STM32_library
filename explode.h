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

/*** GloablConstant & Macro ***/

/*** Global Variable ***/
struct expldparam{
	uint32_t XI;
	uint32_t XF;
};

typedef struct expld{
	/***Variable***/
	struct expldparam par;
	uint32_t HH;
	uint32_t LL;
	uint32_t LH;
	uint32_t HL;
	// PROTOTYPES VTABLE
	void (*update)(struct expld* self, uint32_t x);
}EXPLODE;

/*** Global Header ***/
EXPLODE EXPLODEenable(void);

#endif
/***EOF***/

