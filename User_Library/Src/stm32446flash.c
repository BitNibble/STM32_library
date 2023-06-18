/******************************************************************************
	STM32 446 FLASH
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 13062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446flash.h"

/*** File Procedure & Function Header ***/
uint32_t flash_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void flash_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void flash_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void flash_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t flash_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** FLASH Bit Mapping ***/
// ACR
void STM32446FLASH_acr_dcrst(uint8_t bool)
{
	flash_setreg(&FLASH->ACR, 1, 12, bool);
}
void STM32446FLASH_acr_icrst(uint8_t bool)
{
	flash_setreg(&FLASH->ACR, 1, 11, bool);
}
void STM32446FLASH_acr_dcen(uint8_t bool)
{
	flash_setreg(&FLASH->ACR, 1, 10, bool);
}
void STM32446FLASH_acr_icen(uint8_t bool)
{
	flash_setreg(&FLASH->ACR, 1, 9, bool);
}
void STM32446FLASH_acr_prften(uint8_t bool)
{
	flash_setreg(&FLASH->ACR, 1, 8, bool);
}
void STM32446FLASH_acr_latency(uint8_t value)
{
	flash_setreg(&FLASH->ACR, 4, 0, value);
}
// KEYR
void STM32446FLASH_keyr_key(uint32_t value)
{
	FLASH->KEYR = value;
}
// OPTKEYR
void STM32446FLASH_optkeyr_optkey(uint32_t value)
{
	FLASH->OPTKEYR = value;
}
// SR
uint8_t STM32446FLASH_sr_bsy(void)
{
	return flash_readreg(FLASH->SR, 1, 16);
}
uint8_t STM32446FLASH_sr_rderr(void)
{
	return flash_readreg(FLASH->SR, 1, 8);
}
void STM32446FLASH_sr_clear_rderr(void)
{
	flash_setreg(&FLASH->SR, 1, 8, 1);
}
uint8_t STM32446FLASH_sr_pgserr(void)
{
	return flash_readreg(FLASH->SR, 1, 7);
}
void STM32446FLASH_sr_clear_pgserr(void)
{
	flash_setreg(&FLASH->SR, 1, 7, 1);
}
uint8_t STM32446FLASH_sr_pgperr(void)
{
	return flash_readreg(FLASH->SR, 1, 6);
}
void STM32446FLASH_sr_clear_pgperr(void)
{
	flash_setreg(&FLASH->SR, 1, 6, 1);
}
uint8_t STM32446FLASH_sr_pgaerr(void)
{
	return flash_readreg(FLASH->SR, 1, 5);
}
void STM32446FLASH_sr_clear_pgaerr(void)
{
	flash_setreg(&FLASH->SR, 1, 5, 1);
}
uint8_t STM32446FLASH_sr_wrperr(void)
{
	return flash_readreg(FLASH->SR, 1, 4);
}
void STM32446FLASH_sr_clear_wrperr(void)
{
	flash_setreg(&FLASH->SR, 1, 4, 1);
}
uint8_t STM32446FLASH_sr_operr(void)
{
	return flash_readreg(FLASH->SR, 1, 1);
}
void STM32446FLASH_sr_clear_operr(void)
{
	flash_setreg(&FLASH->SR, 1, 1, 1);
}
uint8_t STM32446FLASH_sr_eop(void)
{
	return flash_readreg(FLASH->SR, 1, 0);
}
void STM32446FLASH_sr_clear_eop(void)
{
	flash_setreg(&FLASH->SR, 1, 0, 1);
}
// CR
void STM32446FLASH_cr_lock(void)
{
	flash_setreg(&FLASH->CR, 1, 31, 1);
}
void STM32446FLASH_cr_errie(uint8_t bool)
{
	flash_setreg(&FLASH->CR, 1, 25, bool);
}
void STM32446FLASH_cr_eopie(uint8_t bool)
{
	flash_setreg(&FLASH->CR, 1, 24, bool);
}
void STM32446FLASH_cr_strt(void)
{
	flash_setreg(&FLASH->CR, 1, 16, 1);
}
void STM32446FLASH_cr_psize(uint8_t value)
{
	flash_setreg(&FLASH->CR, 2, 8, value);
}
void STM32446FLASH_cr_snb(uint8_t value)
{
	flash_setreg(&FLASH->CR, 4, 3, value);
}
void STM32446FLASH_cr_mer(uint8_t bool)
{
	flash_setreg(&FLASH->CR, 1, 2, bool);
}
void STM32446FLASH_cr_ser(uint8_t bool)
{
	flash_setreg(&FLASH->CR, 1, 1, bool);
}
void STM32446FLASH_cr_pg(uint8_t bool)
{
	flash_setreg(&FLASH->CR, 1, 0, bool);
}
// OPTCR
void STM32446FLASH_optcr_sprmod(uint8_t bool)
{
	flash_setreg(&FLASH->OPTCR, 1, 31, bool);
}
void STM32446FLASH_optcr_n_wrp(uint8_t value)
{
	flash_setreg(&FLASH->OPTCR, 8, 16, value);
}
uint8_t STM32446FLASH_optcr_get_n_wrp(void)
{
	return flash_readreg(FLASH->OPTCR, 8, 16);
}
void STM32446FLASH_optcr_rdp(uint8_t value)
{
	flash_setreg(&FLASH->OPTCR, 8, 8, value);
}
uint8_t STM32446FLASH_optcr_get_rdp(void)
{
	return flash_readreg(FLASH->OPTCR, 8, 8);
}
void STM32446FLASH_optcr_nrst_stdby(uint8_t bool)
{
	flash_setreg(&FLASH->OPTCR, 1, 7, bool);
}
void STM32446FLASH_optcr_nrst_stop(uint8_t bool)
{
	flash_setreg(&FLASH->OPTCR, 1, 6, bool);
}
void STM32446FLASH_optcr_wdg_sw(uint8_t bool)
{
	flash_setreg(&FLASH->OPTCR, 1, 5, bool);
}
void STM32446FLASH_optcr_bor_lev(uint8_t value)
{
	flash_setreg(&FLASH->OPTCR, 2, 2, value);
}
void STM32446FLASH_optcr_optstrt(uint8_t bool)
{
	flash_setreg(&FLASH->OPTCR, 1, 1, bool);
}
void STM32446FLASH_optcr_optlock(uint8_t bool)
{
	flash_setreg(&FLASH->OPTCR, 1, 0, bool);
}

/*** INIC Procedure & Function Definition ***/
STM32446FLASHobj flash_inic(void)
{
	STM32446FLASHobj stm32446_flash;

	stm32446_flash.reg = FLASH;
	/*** FLASH Bit Mapping Link ***/
	// ACR
	stm32446_flash.acr.dcrst = STM32446FLASH_acr_dcrst;
	stm32446_flash.acr.icrst = STM32446FLASH_acr_icrst;
	stm32446_flash.acr.dcen = STM32446FLASH_acr_dcen;
	stm32446_flash.acr.icen = STM32446FLASH_acr_icen;
	stm32446_flash.acr.prften = STM32446FLASH_acr_prften;
	stm32446_flash.acr.latency = STM32446FLASH_acr_latency;
	// SR
	stm32446_flash.sr.bsy = STM32446FLASH_sr_bsy;
	stm32446_flash.sr.rderr = STM32446FLASH_sr_rderr;
	stm32446_flash.sr.clear_rderr = STM32446FLASH_sr_clear_rderr;
	stm32446_flash.sr.pgserr = STM32446FLASH_sr_pgserr;
	stm32446_flash.sr.clear_pgserr = STM32446FLASH_sr_clear_pgserr;
	stm32446_flash.sr.pgperr = STM32446FLASH_sr_pgperr;
	stm32446_flash.sr.clear_pgperr = STM32446FLASH_sr_clear_pgperr;
	stm32446_flash.sr.pgaerr = STM32446FLASH_sr_pgaerr;
	stm32446_flash.sr.clear_pgaerr = STM32446FLASH_sr_clear_pgaerr;
	stm32446_flash.sr.wrperr = STM32446FLASH_sr_wrperr;
	stm32446_flash.sr.clear_wrperr = STM32446FLASH_sr_clear_wrperr;
	stm32446_flash.sr.operr = STM32446FLASH_sr_operr;
	stm32446_flash.sr.clear_operr = STM32446FLASH_sr_clear_operr;
	stm32446_flash.sr.eop = STM32446FLASH_sr_eop;
	stm32446_flash.sr.clear_eop = STM32446FLASH_sr_clear_eop;
	// CR
	stm32446_flash.cr.lock = STM32446FLASH_cr_lock;
	stm32446_flash.cr.errie = STM32446FLASH_cr_errie;
	stm32446_flash.cr.eopie = STM32446FLASH_cr_eopie;
	stm32446_flash.cr.strt = STM32446FLASH_cr_strt;
	stm32446_flash.cr.psize = STM32446FLASH_cr_psize;
	stm32446_flash.cr.snb = STM32446FLASH_cr_snb;
	stm32446_flash.cr.mer = STM32446FLASH_cr_mer;
	stm32446_flash.cr.ser = STM32446FLASH_cr_ser;
	stm32446_flash.cr.pg = STM32446FLASH_cr_pg;
	// OPTCR
	stm32446_flash.optcr.sprmod = STM32446FLASH_optcr_sprmod;
	stm32446_flash.optcr.n_wrp = STM32446FLASH_optcr_n_wrp;
	stm32446_flash.optcr.get_n_wrp = STM32446FLASH_optcr_get_n_wrp;
	stm32446_flash.optcr.rdp = STM32446FLASH_optcr_rdp;
	stm32446_flash.optcr.get_rdp = STM32446FLASH_optcr_get_rdp;
	stm32446_flash.optcr.nrst_stdby = STM32446FLASH_optcr_nrst_stdby;
	stm32446_flash.optcr.nrst_stop = STM32446FLASH_optcr_nrst_stop;
	stm32446_flash.optcr.wdg_sw = STM32446FLASH_optcr_wdg_sw;
	stm32446_flash.optcr.bor_lev = STM32446FLASH_optcr_bor_lev;
	stm32446_flash.optcr.optstrt = STM32446FLASH_optcr_optstrt;
	stm32446_flash.optcr.optlock = STM32446FLASH_optcr_optlock;
	// KEYR
	stm32446_flash.keyr = STM32446FLASH_keyr_key;
	// OPTKEYR
	stm32446_flash.optkeyr = STM32446FLASH_optkeyr_optkey;

	return stm32446_flash;
}

/*** File Procedure & Function Definition ***/
uint32_t flash_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

void flash_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}

void flash_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

void flash_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t flash_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
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



