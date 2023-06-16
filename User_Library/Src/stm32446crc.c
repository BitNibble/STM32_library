/******************************************************************************
	STM32 446 CRC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 13062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446crc.h"

/*** File Procedure & Function Header ***/
uint32_t crc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void crc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t crc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** FLASH Bit Mapping ***/
void STM32446CRC_dr(uint32_t value)
{
	CRC->DR = value;
}
uint32_t STM32446CRC_get_dr(void)
{
	return CRC->DR;
}
void STM32446CRC_idr(uint8_t value)
{
	CRC->IDR = value;
}
uint8_t STM32446CRC_get_idr(void)
{
	return CRC->IDR;
}
void STM32446CRC_reset(void)
{
	CRC->CR = 1;
}

/*** CRC Procedure & Function Definition ***/
uint32_t crc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void crc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t crc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = *(reg + n ) & (mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/


