/******************************************************************************
	STM32 446 FLASH
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
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
STM32446FLASH_acr stm32446_flash_acr_inic(void);
STM32446FLASH_sr stm32446_flash_sr_inic(void);
STM32446FLASH_cr stm32446_flash_cr_inic(void);
STM32446FLASH_optcr stm32446_flash_optcr_inic(void);
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
{ // Do not permit Blocking Chip !!
	if(value != 0xCC){ flash_setreg(&FLASH->OPTCR, 8, 8, value);}
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
/*** Other ***/
void STM32446FLASH_nvic(uint8_t bool)
{
	if(bool){ flash_setbit(NVIC->ISER, 1, 4, 1); }
	else{ flash_setbit(NVIC->ICER, 1, 4, 1); }
}
/*** FLASH Auxiliar ***/
STM32446FLASH_acr stm32446_flash_acr_inic(void)
{
	STM32446FLASH_acr stm32446_flash_acr;
	// ACR
	stm32446_flash_acr.dcrst = STM32446FLASH_acr_dcrst;
	stm32446_flash_acr.icrst = STM32446FLASH_acr_icrst;
	stm32446_flash_acr.dcen = STM32446FLASH_acr_dcen;
	stm32446_flash_acr.icen = STM32446FLASH_acr_icen;
	stm32446_flash_acr.prften = STM32446FLASH_acr_prften;
	stm32446_flash_acr.latency = STM32446FLASH_acr_latency;
	return stm32446_flash_acr;
}
STM32446FLASH_sr stm32446_flash_sr_inic(void)
{
	STM32446FLASH_sr stm32446_flash_sr;
	// SR
	stm32446_flash_sr.bsy = STM32446FLASH_sr_bsy;
	stm32446_flash_sr.rderr = STM32446FLASH_sr_rderr;
	stm32446_flash_sr.clear_rderr = STM32446FLASH_sr_clear_rderr;
	stm32446_flash_sr.pgserr = STM32446FLASH_sr_pgserr;
	stm32446_flash_sr.clear_pgserr = STM32446FLASH_sr_clear_pgserr;
	stm32446_flash_sr.pgperr = STM32446FLASH_sr_pgperr;
	stm32446_flash_sr.clear_pgperr = STM32446FLASH_sr_clear_pgperr;
	stm32446_flash_sr.pgaerr = STM32446FLASH_sr_pgaerr;
	stm32446_flash_sr.clear_pgaerr = STM32446FLASH_sr_clear_pgaerr;
	stm32446_flash_sr.wrperr = STM32446FLASH_sr_wrperr;
	stm32446_flash_sr.clear_wrperr = STM32446FLASH_sr_clear_wrperr;
	stm32446_flash_sr.operr = STM32446FLASH_sr_operr;
	stm32446_flash_sr.clear_operr = STM32446FLASH_sr_clear_operr;
	stm32446_flash_sr.eop = STM32446FLASH_sr_eop;
	stm32446_flash_sr.clear_eop = STM32446FLASH_sr_clear_eop;
	return stm32446_flash_sr;
}
STM32446FLASH_cr stm32446_flash_cr_inic(void)
{
	STM32446FLASH_cr stm32446_flash_cr;
	// CR
	stm32446_flash_cr.lock = STM32446FLASH_cr_lock;
	stm32446_flash_cr.errie = STM32446FLASH_cr_errie;
	stm32446_flash_cr.eopie = STM32446FLASH_cr_eopie;
	stm32446_flash_cr.strt = STM32446FLASH_cr_strt;
	stm32446_flash_cr.psize = STM32446FLASH_cr_psize;
	stm32446_flash_cr.snb = STM32446FLASH_cr_snb;
	stm32446_flash_cr.mer = STM32446FLASH_cr_mer;
	stm32446_flash_cr.ser = STM32446FLASH_cr_ser;
	stm32446_flash_cr.pg = STM32446FLASH_cr_pg;
	return stm32446_flash_cr;
}
STM32446FLASH_optcr stm32446_flash_optcr_inic(void)
{
	STM32446FLASH_optcr stm32446_flash_optcr;
	// OPTCR
	stm32446_flash_optcr.sprmod = STM32446FLASH_optcr_sprmod;
	stm32446_flash_optcr.n_wrp = STM32446FLASH_optcr_n_wrp;
	stm32446_flash_optcr.get_n_wrp = STM32446FLASH_optcr_get_n_wrp;
	stm32446_flash_optcr.rdp = STM32446FLASH_optcr_rdp;
	stm32446_flash_optcr.get_rdp = STM32446FLASH_optcr_get_rdp;
	stm32446_flash_optcr.nrst_stdby = STM32446FLASH_optcr_nrst_stdby;
	stm32446_flash_optcr.nrst_stop = STM32446FLASH_optcr_nrst_stop;
	stm32446_flash_optcr.wdg_sw = STM32446FLASH_optcr_wdg_sw;
	stm32446_flash_optcr.bor_lev = STM32446FLASH_optcr_bor_lev;
	stm32446_flash_optcr.optstrt = STM32446FLASH_optcr_optstrt;
	stm32446_flash_optcr.optlock = STM32446FLASH_optcr_optlock;
	return stm32446_flash_optcr;
}
/*** INIC Procedure & Function Definition ***/
STM32446FLASHobj flash_inic(void)
{
	STM32446FLASHobj stm32446_flash;

	stm32446_flash.reg = FLASH;
	/*** FLASH Bit Mapping Link ***/
	stm32446_flash.acr = stm32446_flash_acr_inic();
	stm32446_flash.sr = stm32446_flash_sr_inic();
	stm32446_flash.cr = stm32446_flash_cr_inic();
	stm32446_flash.optcr = stm32446_flash_optcr_inic();
	stm32446_flash.keyr = STM32446FLASH_keyr_key;
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


