/******************************************************************************
	STM32 446 PWR
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446pwr.h"

/*** File Procedure & Function Header ***/
uint32_t pwr_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void pwr_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t pwr_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** PWR Bit Mapping ***/
// CR
void STM32446PWR_cr_fissr(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 21, bool);
}
void STM32446PWR_cr_fmssr(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 20, bool);
}
void STM32446PWR_cr_uden(uint8_t value)
{
	pwr_setbit(&PWR->CR, 2, 18, value);
}
void STM32446PWR_cr_odswen(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 17, bool);
}
void STM32446PWR_cr_oden(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 16, bool);
}
void STM32446PWR_cr_vos(uint8_t value)
{
	pwr_setbit(&PWR->CR, 2, 14, value);
}
void STM32446PWR_cr_adcdc1(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 13, bool);
}
void STM32446PWR_cr_mruds(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 11, bool);
}
void STM32446PWR_cr_lpuds(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 10, bool);
}
void STM32446PWR_cr_fpds(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 9, bool);
}
void STM32446PWR_cr_dbp(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 8, bool);
}
void STM32446PWR_cr_pls(uint8_t value)
{
	pwr_setbit(&PWR->CR, 3, 5, value);
}
void STM32446PWR_cr_pvde(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 4, bool);
}
void STM32446PWR_cr_clear_csbf(void)
{
	pwr_setbit(&PWR->CR, 1, 3, 1);
}
void STM32446PWR_cr_clear_cwuf(void)
{
	pwr_setbit(&PWR->CR, 1, 2, 1);
}
void STM32446PWR_cr_pdds(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 1, bool);
}
void STM32446PWR_cr_lpds(uint8_t bool)
{
	pwr_setbit(&PWR->CR, 1, 0, bool);
}

// CSR
uint8_t STM32446PWR_udrdy(void)
{
	return pwr_getbit(PWR->CSR, 2, 18);
}
void STM32446PWR_csr_clear_udrdy(void)
{
	pwr_setbit(&PWR->CSR, 2, 18, 3);
}
uint8_t STM32446PWR_csr_odswrdy(void)
{
	return pwr_getbit(PWR->CSR, 1, 17);
}
uint8_t STM32446PWR_csr_odrdy(void)
{
	return pwr_getbit(PWR->CSR, 1, 16);
}
uint8_t STM32446PWR_csr_vosrdy(void)
{
	return pwr_getbit(PWR->CSR, 1, 14);
}
void STM32446PWR_csr_bre(uint8_t bool)
{
	pwr_setbit(&PWR->CSR, 1, 9, bool);
}
void STM32446PWR_csr_ewup1(uint8_t bool)
{
	pwr_setbit(&PWR->CSR, 1, 8, bool);
}
void STM32446PWR_csr_ewup2(uint8_t bool)
{
	pwr_setbit(&PWR->CSR, 1, 7, bool);
}
uint8_t STM32446PWR_csr_brr(void)
{
	return pwr_getbit(PWR->CSR, 1, 3);
}
uint8_t STM32446PWR_csr_pvdo(void)
{
	return pwr_getbit(PWR->CSR, 1, 2);
}
uint8_t STM32446PWR_csr_sbf(void)
{
	return pwr_getbit(PWR->CSR, 1, 1);
}
uint8_t STM32446PWR_csr_wuf(void)
{
	return pwr_getbit(PWR->CSR, 1, 0);
}

/*** PWR Procedure & Function Definition ***/
uint32_t pwr_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void pwr_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t pwr_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = *(reg + n ) & ~(mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/



