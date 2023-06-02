/******************************************************************************
	STM32 446 RCC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446RCC_H_
	#define _STM32446RCC_H_

/*** Library ***/
#include <inttypes.h>

/*** RCC_Common ***/
// RCC -> PLL
typedef struct
{
	void (*division)(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr);
	void (*enable)(void);
}STM32446RCCPLL;

// RCC -> PLLI2S
typedef struct
{
	void (*enable)(void);
}STM32446RCCPLLI2S;

// RCC -> PLLSAI
typedef struct
{
	void (*enable)(void);
}STM32446RCCPLLSAI;

/*** RCC ***/
typedef struct
{
	RCC_TypeDef* reg;
	#if defined(_STM32446RCC_H_)
		uint8_t (*inic)(void);
		void (*henable)(unsigned int hclock);
		uint8_t (*hselect)(uint8_t sysclk);
		void (*lenable)(unsigned int lclock);
		void (*lselect)(uint8_t lclock);
		void (*prescaler)(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre);
		STM32446RCCPLL pll;
		STM32446RCCPLLI2S plli2s;
		STM32446RCCPLLSAI pllsai;
	#endif
}STM32446RCCobj;

// PLL
void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr);
void STM32446RccPLLCLKEnable(void);
void STM32446RccPLLI2SEnable(void);
void STM32446RccPLLSAIEnable(void);
// RCC
uint8_t STM32446RccInic(void);
void STM32446RccHEnable(unsigned int hclock);
uint8_t STM32446RccHSelect(uint8_t hclock);
void STM32446RccLEnable(unsigned int lclock);
void STM32446RccLSelect(uint8_t lclock);
void STM32446Prescaler(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre);
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


