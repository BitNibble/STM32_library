/******************************************************************************
	STM32 446 SYSCFG
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446SYSCFG_H_
	#define _STM32446SYSCFG_H_

/*** File Library ***/
#include <inttypes.h>
/***************************************/
/***** SYSCFG Bit Mapping TypeDef ****/
/***************************************/
typedef struct
{
	void (*swp_fmc)(uint8_t value);
	void (*mem_mode)(uint8_t value);
}SYSCFG_memrmp;
typedef struct
{
	void (*adcxdc2)(uint8_t value);
}SYSCFG_pmc;
typedef struct
{
	void (*exti3)(uint8_t value);
	void (*exti2)(uint8_t value);
	void (*exti1)(uint8_t value);
	void (*exti0)(uint8_t value);
}SYSCFG_exticr1;
typedef struct
{
	void (*exti7)(uint8_t value);
	void (*exti6)(uint8_t value);
	void (*exti5)(uint8_t value);
	void (*exti4)(uint8_t value);
}SYSCFG_exticr2;
typedef struct
{
	void (*exti11)(uint8_t value);
	void (*exti10)(uint8_t value);
	void (*exti9)(uint8_t value);
	void (*exti8)(uint8_t value);
}SYSCFG_exticr3;
typedef struct
{
	void (*exti15)(uint8_t value);
	void (*exti14)(uint8_t value);
	void (*exti13)(uint8_t value);
	void (*exti12)(uint8_t value);
}SYSCFG_exticr4;
typedef struct
{
	uint8_t (*ready)(void);
	void (*cmp_pd)(uint8_t bool);
}SYSCFG_cmpcr;
typedef struct
{
	void (*fmpi2c1_sda)(uint8_t value);
	void (*fmpi2c1_scl)(uint8_t value);
}SYSCFG_cfgr;
/***************************************/
/********** SYSCFG TypeDef **********/
/***************************************/
typedef struct
{
	SYSCFG_TypeDef* reg;
	/*** Bit Mapping ***/
	SYSCFG_memrmp memrmp;
	SYSCFG_pmc pmc;
	SYSCFG_exticr1 exticr1;
	SYSCFG_exticr2 exticr2;
	SYSCFG_exticr3 exticr3;
	SYSCFG_exticr4 exticr4;
	SYSCFG_cmpcr cmpcr;
	SYSCFG_cfgr cfgr;
	/*** Other ***/
	void (*clock)(uint8_t bool);
}STM32446SYSCFGobj;


/*************************************/
/************ INIC SYSCFG ************/
/*************************************/
STM32446SYSCFGobj STM32446SYSCFG_inic(void);


/***********************************************/
/********* Procedure & Function Header *********/
/***********************************************/
void SYSCFG_Clock(uint8_t bool);


/***********************************************/
/*** INTERRUPT HEADER ***/

#endif

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


