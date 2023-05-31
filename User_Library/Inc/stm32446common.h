/******************************************************************************
	STM32 446 COMMON
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	Common Code
*******************************************************************************/
#ifndef _STM32446COMMON_H_
	#define _STM32446COMMON_H_

/********** Global TypeDef ***********/
typedef struct
{
	uint8_t L;
	uint8_t H;
} STM32HighLowByte;

// Low Word High Word
//typedef struct
//{
//	uint16_t H;
//	uint16_t L;
//}STM32446HighLowWord;

typedef struct
{
	uint32_t (*AHB)(void);
	uint32_t (*APB1)(void);
	uint32_t (*APB2)(void);
	uint32_t (*RTCclk)(void);
	uint32_t (*MCO1)(void);
	uint32_t (*MCO2)(void);
}STM32446CLOCK_prescaler;

typedef struct
{
	uint32_t (*M)(void);
	uint32_t (*N)(void);
	uint32_t (*P)(void);
	uint32_t (*Q)(void);
	uint32_t (*R)(void);
}STM32446PLL_parameter;

/************** QUERY TypeDef ****************/
typedef struct
{
	STM32446CLOCK_prescaler CLOCK_prescaler;
	STM32446PLL_parameter PLL_parameter;
	uint32_t (*ClockSource)(void);
	uint32_t (*SystemClock)(void);
	uint32_t (*PllSource)(void);
}STM32446Query;

/***** Peripheral COMMON TypeDef *****/
/*** ADC_Common ***/
typedef struct
{
	ADC_Common_TypeDef* reg;
}STM32446ADCCOMMONobj;

typedef struct
{
	void (*inic)(void);
	void (*vbat)(void);
	void (*temp)(void);
	void (*start)(void);
	double (*read)(void);
	void (*restart)(void);
	void (*stop)(void);
}STM32446ADC1single;

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

#endif

/*** EOF ***/


