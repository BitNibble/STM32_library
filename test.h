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

/*** Global Library ***/
#include <inttypes.h>

/*** Gloabl Constant & Macro ***/

/*** Global Variable ***/
typedef struct
{
	uint32_t testa;
}TEST;

/*** Global Header ***/
TEST TESTenable(void);

#endif
/***EOF***/


