/******************************************************************************
	STM32 446 SRAM
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446sram.h"

static uint32_t sram_time_out;

/*** File Procedure & Function Header ***/
uint32_t sram_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void sram_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void sram_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void sram_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t sram_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** SRAM Procedure & Function Definition ***/
void STM32446SramAccess(void)
{
	// RM0390 pg 94
	// SRAM access
	// 0 - Power Up SRAM
	PWR->CSR |= (1 << 9); // BRE: Backup regulator enable
	// Check ready flag Bit 3 BRR: Backup regulator ready
	for( sram_time_out = 100; !(PWR->CSR & (1 << 3)) && sram_time_out; sram_time_out-- ); // BRR: Backup regulator ready

	// 1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	RCC->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	// 2 - Set the DBP bit in the PWR power control register (PWR_CR)
	PWR->CR |= (1 << 8); // Disable backup domain write protection

	// 3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	RCC->AHB1ENR |= (1 << 18); // BKPSRAMEN: Backup SRAM interface clock enable
}

/*** SRAM Bit Mapping Definition ***/

/*** INIC Procedure & Function Definition ***/
STM32446SRAMobj sram_inic(void)
{
	STM32446SRAMobj stm32446_sram;
	stm32446_sram.access = STM32446SramAccess;
	return stm32446_sram;
}

/*** File Procedure & Function Definition ***/
uint32_t sram_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void sram_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void sram_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void sram_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t sram_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
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


