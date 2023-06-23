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
void SYSCFGgroup1_inic( uint8_t parameter );



/***********************************************/
/******* Procedure & Function Definition *******/
/***********************************************/
void syscfg_link(void){}



/***********************************************/
/**** LINK Procedure & Function Definition *****/
/***********************************************/
void SYSCFGgroup1_inic( uint8_t parameter )
{
	syscfg_link();

}


/************************************************/
/*** SYSCFG Procedure & Function Definition ***/
/************************************************/
STM32446SYSCFGobj STM32446SYSCFG_inic(void)
{
	STM32446SYSCFGobj syscfg;

	syscfg.group1 = SYSCFGgroup1_inic;

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

/*** EOF ***/


