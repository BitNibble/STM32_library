/******************************************************************************
	STM32 446 USART
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

typedef struct{
	USART_TypeDef* reg;

	void (*inic)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
	void (*transmit)(void);
	void (*receive)(void);
	void (*stop)(void);
}STM32446USART1;

STM32446USART1 STM32446USART1enable(void);

// USART -> USART1
typedef struct
{
	USART_TypeDef* reg;
	STM32446USART1 (*enable)(void);
}STM32446USART1obj;

// USART -> USART2
typedef struct
{
	USART_TypeDef* reg;
	void (*enable)(void);
}STM32446USART2obj;

// USART -> USART3
typedef struct
{
	USART_TypeDef* reg;
	void (*enable)(void);
}STM32446USART3obj;

// USART -> USART4
typedef struct
{
	USART_TypeDef* reg;
	void (*enable)(void);
}STM32446USART4obj;

// USART -> USART5
typedef struct
{
	USART_TypeDef* reg;
	void (*enable)(void);
}STM32446USART5obj;

// USART -> USART6
typedef struct
{
	USART_TypeDef* reg;
	void (*enable)(void);
}STM32446USART6obj;

#endif

/*** EOF ***/


