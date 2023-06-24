/******************************************************************************
	STM32 446 CRC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446crc.h"
/*** File Procedure & Function Header ***/
uint32_t crc_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void crc_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void crc_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void crc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t crc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
/*** CRC Bit Mapping ***/
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
void STM32446CRC_clock(uint8_t bool)
{
	if(bool){ RCC->AHB1ENR |= (1 << 12); }
	else{ RCC->AHB1ENR &= ~(1 << 12); }
}
/*** INIC Procedure & Function Definition ***/
STM32446CRCobj crc_inic(void)
{
	STM32446CRCobj stm32446_crc;
	stm32446_crc.reg = CRC;
	/***CRC Bit Mapping Link***/
	stm32446_crc.dr = STM32446CRC_dr;
	stm32446_crc.get_dr = STM32446CRC_get_dr;
	stm32446_crc.idr = STM32446CRC_idr;
	stm32446_crc.get_idr = STM32446CRC_get_idr;
	stm32446_crc.reset = STM32446CRC_reset;
	return stm32446_crc;
}
/*** File Procedure & Function Definition ***/
uint32_t crc_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void crc_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void crc_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void crc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t crc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
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

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/


