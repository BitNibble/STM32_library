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

/*** File Procedure & Function Header ***/
uint32_t template_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void template_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t template_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void template_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t template_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** TEMPLATE Procedure & Function Definition ***/
STM32446TEMPLATE1 STM32446TEMPLATE1enable(void)
{
	STM32446TEMPLATE1 template1;

	template1.inic = STM32446Template1Inic;

	return template1;
}

void STM32446Template1Inic( uint8_t parameter )
{
	
}

/*** File Procedure & Function Definition ***/
uint32_t template_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0;
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t tmp = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp &= mask;
	value = (tmp >> bit);
	return value;
}

void template_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}

void template_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

uint32_t template_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	 uint32_t value = 0;
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t tmp = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp &= mask;
	value = (tmp >> bit);
	return value;
}

void template_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t template_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/


