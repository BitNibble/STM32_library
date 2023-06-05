/******************************************************************************
	STM32446 NVIC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 04062023
Comment:
	Interrupt Vector
*******************************************************************************/
#ifndef _STM32446NVIC_H_
	#define _STM32446NVIC_H_

#include <inttypes.h>

// NVIC
typedef struct
{
	NVIC_Type* reg;
	void (*set_enable)( uint8_t IRQn );
	void (*clear_enable)( uint8_t IRQn );
	void (*set_pending)( uint8_t IRQn );
	void (*clear_pending)( uint8_t IRQn );
	uint8_t (*active)( uint8_t IRQn );
	void (*priority)(uint32_t IRQn, uint32_t priority);
	void (*trigger)(uint32_t IRQn);
}STM32446NVICobj;

// NVIC
void STM32446NVIC_set_enable( uint8_t IRQn );
void STM32446NVIC_clear_enable( uint8_t IRQn );
void STM32446NVIC_set_pending( uint8_t IRQn );
void STM32446NVIC_clear_pending( uint8_t IRQn );
uint8_t STM32446NVIC_active( uint8_t IRQn );
void STM32446NVIC_priority(uint32_t IRQn, uint32_t priority);
void STM32446NVIC_trigger(uint32_t IRQn);

#endif

/*** EOF ***/


