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
// memrmp
void SYSCFG_memrmp_swp_fmc(uint8_t value)
{
	syscfg_setreg(&SYSCFG->MEMRMP, 2, 10, value);
}
void SYSCFG_memrmp_mem_mode(uint8_t value)
{
	syscfg_setreg(&SYSCFG->MEMRMP, 3, 0, value);
}
// pmc
void SYSCFG_pmc_adcxdc2(uint8_t value)
{
	syscfg_setreg(&SYSCFG->PMC, 3, 16, value);
}
// exticr1
void SYSCFG_exticr1_exti3(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[0], 4, 12, value);
}
void SYSCFG_exticr1_exti2(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[0], 4, 8, value);
}
void SYSCFG_exticr1_exti1(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[0], 4, 4, value);
}
void SYSCFG_exticr1_exti0(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[0], 4, 0, value);
}
// exticr2
void SYSCFG_exticr2_exti7(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[1], 4, 12, value);
}
void SYSCFG_exticr2_exti6(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[1], 4, 8, value);
}
void SYSCFG_exticr2_exti5(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[1], 4, 4, value);
}
void SYSCFG_exticr2_exti4(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[1], 4, 0, value);
}
// exticr3
void SYSCFG_exticr3_exti11(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[2], 4, 12, value);
}
void SYSCFG_exticr3_exti10(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[2], 4, 8, value);
}
void SYSCFG_exticr3_exti9(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[2], 4, 4, value);
}
void SYSCFG_exticr3_exti8(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[2], 4, 0, value);
}
// exticr4
void SYSCFG_exticr4_exti15(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[3], 4, 12, value);
}
void SYSCFG_exticr4_exti14(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[3], 4, 8, value);
}
void SYSCFG_exticr4_exti13(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[3], 4, 4, value);
}
void SYSCFG_exticr4_exti12(uint8_t value)
{
	syscfg_setreg(&SYSCFG->EXTICR[3], 4, 0, value);
}
// cmpcr
uint8_t SYSCFG_cmpcr_ready(void)
{
	return syscfg_readreg(SYSCFG->CMPCR, 1, 8);
}
void SYSCFG_cmpcr_cmp_pd(uint8_t bool)
{
	syscfg_setreg(&SYSCFG->CMPCR, 1, 0, bool);
}
// cfgr
void SYSCFG_cfgr_fmpi2c1_sda(uint8_t bool)
{
	syscfg_setreg(&SYSCFG->CFGR, 1, 1, bool);
}
void SYSCFG_cfgr_fmpi2c1_scl(uint8_t bool)
{
	syscfg_setreg(&SYSCFG->CFGR, 1, 0, bool);
}
/***********************************************/
/**** LINK Procedure & Function Definition *****/
/***********************************************/
SYSCFG_memrmp SYSCFG_memrmp_inic(void)
{
	SYSCFG_memrmp memrmp;
	memrmp.swp_fmc = SYSCFG_memrmp_swp_fmc;
	memrmp.mem_mode = SYSCFG_memrmp_mem_mode;
	return memrmp;
}
SYSCFG_pmc SYSCFG_pmc_inic(void)
{
	SYSCFG_pmc pmc;
	pmc.adcxdc2 = SYSCFG_pmc_adcxdc2;
	return pmc;
}
SYSCFG_exticr1 SYSCFG_exticr1_inic(void)
{
	SYSCFG_exticr1 exticr1;
	exticr1.exti3 = SYSCFG_exticr1_exti3;
	exticr1.exti2 = SYSCFG_exticr1_exti2;
	exticr1.exti1 = SYSCFG_exticr1_exti1;
	exticr1.exti0 = SYSCFG_exticr1_exti0;
	return exticr1;
}
SYSCFG_exticr2 SYSCFG_exticr2_inic(void)
{
	SYSCFG_exticr2 exticr2;
	exticr2.exti7 = SYSCFG_exticr2_exti7;
	exticr2.exti7 = SYSCFG_exticr2_exti6;
	exticr2.exti5 = SYSCFG_exticr2_exti5;
	exticr2.exti4 = SYSCFG_exticr2_exti4;
	return exticr2;
}
SYSCFG_exticr3 SYSCFG_exticr3_inic(void)
{
	SYSCFG_exticr3 exticr3;
	exticr3.exti11 = SYSCFG_exticr3_exti11;
	exticr3.exti10 = SYSCFG_exticr3_exti10;
	exticr3.exti9 = SYSCFG_exticr3_exti9;
	exticr3.exti8 = SYSCFG_exticr3_exti8;
	return exticr3;
}
SYSCFG_exticr4 SYSCFG_exticr4_inic(void)
{
	SYSCFG_exticr4 exticr4;
	exticr4.exti15 = SYSCFG_exticr4_exti15;
	exticr4.exti14 = SYSCFG_exticr4_exti14;
	exticr4.exti13 = SYSCFG_exticr4_exti13;
	exticr4.exti12 = SYSCFG_exticr4_exti12;
	return exticr4;
}
SYSCFG_cmpcr SYSCFG_cmpcr_inic(void)
{
	SYSCFG_cmpcr cmpcr;
	cmpcr.ready = SYSCFG_cmpcr_ready;
	cmpcr.cmp_pd = SYSCFG_cmpcr_cmp_pd;
	return cmpcr;
}
SYSCFG_cfgr SYSCFG_cfgr_inic(void)
{
	SYSCFG_cfgr cfgr;
	cfgr.fmpi2c1_sda = SYSCFG_cfgr_fmpi2c1_sda;
	cfgr.fmpi2c1_scl = SYSCFG_cfgr_fmpi2c1_scl;
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


