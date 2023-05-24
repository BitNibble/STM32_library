/******************************************************************************
	STM32 446 USART1
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446USART_H_
	#define _STM32446USART_H_

/*** Library ***/
#include <inttypes.h>

/*** Constant & Macros ***/

/*** Variable ***/
typedef struct{
	void (*inic)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
	void (*transmit)(void);
	void (*receive)(void);
	void (*stop)(void);
}STM32446USART1;

/*** Global Header ***/
STM32446USART1 STM32446USART1enable(void);

#endif
/*** EOF ***/

