/******************************************************************************
	STM32 446 SYSCFG
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446syscfg.h"
/****************************************/
/*** File Procedure & Function Header ***/
/****************************************/
uint32_t syscfg_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void syscfg_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void syscfg_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void syscfg_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t syscfg_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
/***********************************************/
/****** LINK Procedure & Function Header *******/
/***********************************************/
SYSCFG_memrmp SYSCFG_memrmp_inic(void);
SYSCFG_pmc SYSCFG_pmc_inic(void);
SYSCFG_exticr1 SYSCFG_exticr1_inic(void);
SYSCFG_exticr2 SYSCFG_exticr2_inic(void);
SYSCFG_exticr3 SYSCFG_exticr3_inic(void);
SYSCFG_exticr4 SYSCFG_exticr4_inic(void);
SYSCFG_cmpcr SYSCFG_cmpcr_inic(void);
SYSCFG_cfgr SYSCFG_cfgr_inic(void);
/***********************************************/
/******* Procedure & Function Definition *******/
/***********************************************/
void SYSCFG_memrmp_swp_fmc(uint8_t value)
{

}





/***********************************************/
/**** LINK Procedure & Function Definition *****/
/***********************************************/
SYSCFG_memrmp SYSCFG_memrmp_inic(void)
{
	SYSCFG_memrmp memrmp;

	return memrmp;
}
SYSCFG_pmc SYSCFG_pmc_inic(void)
{
	SYSCFG_pmc pmc;

	return pmc;
}
SYSCFG_exticr1 SYSCFG_exticr1_inic(void)
{
	SYSCFG_exticr1 exticr1;

	return exticr1;
}
SYSCFG_exticr2 SYSCFG_exticr2_inic(void)
{
	SYSCFG_exticr2 exticr2;

	return exticr2;
}
SYSCFG_exticr3 SYSCFG_exticr3_inic(void)
{
	SYSCFG_exticr3 exticr3;

	return exticr3;
}
SYSCFG_exticr4 SYSCFG_exticr4_inic(void)
{
	SYSCFG_exticr4 exticr4;

	return exticr4;
}
SYSCFG_cmpcr SYSCFG_cmpcr_inic(void)
{
	SYSCFG_cmpcr cmpcr;

	return cmpcr;
}
SYSCFG_cfgr SYSCFG_cfgr_inic(void)
{
	SYSCFG_cfgr cfgr;

	return cfgr;
}
/************************************************/
/**** SYSCFG Procedure & Function Definition ****/
/************************************************/
STM32446SYSCFGobj STM32446SYSCFG_inic(void)
{
	STM32446SYSCFGobj syscfg;
	syscfg.reg = SYSCFG;
	/*** LINK ***/
	syscfg.memrmp = SYSCFG_memrmp_inic();
	syscfg.pmc = SYSCFG_pmc_inic();
	syscfg.exticr1 = SYSCFG_exticr1_inic();
	syscfg.exticr2 = SYSCFG_exticr2_inic();
	syscfg.exticr3 = SYSCFG_exticr3_inic();
	syscfg.exticr4 = SYSCFG_exticr4_inic();
	syscfg.cmpcr = SYSCFG_cmpcr_inic();
	syscfg.cfgr = SYSCFG_cfgr_inic();
	/*** Oyher ***/
	syscfg.clock = SYSCFG_Clock;
	return syscfg;
}
/************************************************/
/***** File Procedure & Function Definition *****/
/************************************************/
uint32_t syscfg_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void syscfg_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void syscfg_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void syscfg_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t syscfg_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
/************************************************/

/*** EOF ***/


