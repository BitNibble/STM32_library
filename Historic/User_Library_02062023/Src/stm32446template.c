/******************************************************************************
	STM32 446 TEMPLATE
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446template.h"

uint32_t template_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void template_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);

/*** TEMPLATE ***/
STM32446TEMPLATE1 STM32446TEMPLATE1enable(void)
{
	STM32446TEMPLATE1 template1;

	template1.inic = STM32446Template1Inic;

	return template1;
}

void STM32446Template1Inic( uint8_t parameter )
{
	
}

uint32_t template_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void template_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

/*** EOF ***/


