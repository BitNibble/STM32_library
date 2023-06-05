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
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446nvic.h"

void STM32446NVIC_set_enable( uint8_t IRQn )
{
	volatile uint32_t* reg = NVIC->ISER;
	uint32_t n = 0;
	if(IRQn > 31){ n = IRQn/32; IRQn = IRQn - (n * 32); }
	*(reg + n ) &= ~(1 << IRQn);
	*(reg + n ) |= (1 << IRQn);
}

void STM32446NVIC_clear_enable( uint8_t IRQn )
{
	volatile uint32_t* reg = NVIC->ICER;
	uint32_t n = 0;
	if(IRQn > 31){ n = IRQn/32; IRQn = IRQn - (n * 32); }
	*(reg + n ) &= ~(1 << IRQn);
	*(reg + n ) |= (1 << IRQn);
}

void STM32446NVIC_set_pending( uint8_t IRQn )
{
	volatile uint32_t* reg = NVIC->ISPR;
	uint32_t n = 0;
	if(IRQn > 31){ n = IRQn/32; IRQn = IRQn - (n * 32); }
	*(reg + n ) &= ~(1 << IRQn);
	*(reg + n ) |= (1 << IRQn);
}

void STM32446NVIC_clear_pending( uint8_t IRQn )
{
	volatile uint32_t* reg = NVIC->ICPR;
	uint32_t n = 0;
	if(IRQn > 31){ n = IRQn/32; IRQn = IRQn - (n * 32); }
	*(reg + n ) &= ~(1 << IRQn);
	*(reg + n ) |= (1 << IRQn);
}

uint8_t STM32446NVIC_active( uint8_t IRQn ) // Query
{
	volatile uint32_t* reg = NVIC->IABR;
	uint8_t bool; uint32_t n = 0;
	if(IRQn > 31){ n = IRQn/32; IRQn = IRQn - (n * 32); }
	if( *(reg + n ) & (1 << IRQn) ) bool = 1; else bool = 0 ;
	return bool;
}

void STM32446NVIC_priority(uint32_t IRQn, uint32_t priority)
{
	volatile uint8_t* reg = (uint8_t*) NVIC->IP;
	*(reg + IRQn ) = 0;
	*(reg + IRQn ) |= priority;
}

void STM32446NVIC_trigger(uint32_t IRQn)
{
	volatile uint32_t* reg = &NVIC->STIR;
	uint32_t size_block = 9; uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = IRQn & mask;
	*reg = value;
}

/*** EOF ***/


